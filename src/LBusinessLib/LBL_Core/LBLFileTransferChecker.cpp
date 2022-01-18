#include "LBL_Core/LBLFileTransferChecker.h"
#include "LBL_Core/LBLUIHelper.h"
#include <QCryptographicHash>

LBLFileTransferChecker::LBLFileTransferChecker(const QString& filePath)
{
    m_file.setFileName(filePath);
}

bool LBLFileTransferChecker::open()
{
    if (!m_file.open(QIODevice::ReadOnly)) {
        m_lastErrorString = tr("File Open Faild.");
        return false;
    }
    m_fileInfo.setFile(m_file);
    return true;
}

void LBLFileTransferChecker::close()
{
    m_file.close();
}

bool LBLFileTransferChecker::isValid()
{
    return m_valid;
}

const QFileInfo &LBLFileTransferChecker::fileInfo() const
{
    return m_fileInfo;
}

QByteArray LBLFileTransferChecker::fileHead()
{
    return m_fileHead;
}

QByteArray LBLFileTransferChecker::hardwarHead()
{
    if(m_fileHead.size()<m_hardwarHeadLength){
        m_lastErrorString = tr("Head Length < %1.").arg(m_hardwarHeadLength);
        return QByteArray();
    }
    return m_fileHead.mid(0,8);
}

QString LBLFileTransferChecker::pcbCategory(const QByteArray &hardwarHead)
{
    if(hardwarHead.size()!=m_hardwarHeadLength){
        return QString();
    }
    quint16 pcb=0;
    memcpy(&pcb,hardwarHead.constData()+2,2);
    QString str=enmToStr(EPCBCategory(pcb));
    str=str.split("_").last();
    return str;
}

QByteArray LBLFileTransferChecker::versionNumber()
{
    if(m_fileHead.size()!=m_fileHeadLength){
        m_lastErrorString = tr("Head Length != %1.").arg(m_fileHeadLength);
        return QByteArray();
    }
    return m_fileHead.mid(0xC0,32);
}

QString LBLFileTransferChecker::creatTime()
{
    if(m_fileHead.size()!=m_fileHeadLength){
        m_lastErrorString = tr("Head Length != %1.").arg(m_fileHeadLength);
        return QString();
    }
    QByteArray time=m_fileHead.mid(0xE8,6);
    quint16 year = 0;
    memcpy(&year,time.constData(),2);
    return QString("%1/%2/%3 %4:%5")\
            .arg(year)\
            .arg(m_fileHead.at(2))\
            .arg(m_fileHead.at(3))\
            .arg(m_fileHead.at(4))\
            .arg(m_fileHead.at(5));
}

QByteArray LBLFileTransferChecker::fileMD5()
{
    if(m_fileHead.size()!=m_fileHeadLength){
        m_lastErrorString = tr("Head Length != %1.").arg(m_fileHeadLength);
        return QByteArray();
    }
    return m_fileHead.mid(0xEE,16);
}

quint16 LBLFileTransferChecker::checkSum()
{
    quint16 sum=0;
    if(m_fileHead.size()==m_fileHeadLength){
        memcpy(&sum,m_fileHead.constBegin()+0xFE,2);
    }
    return sum;
}

quint16 LBLFileTransferChecker::fileType()
{
    //此函数返回的quint16值为文件传输定义的文件类型，该类型在此函数中根据8字节硬件版本做粗略推测
    QByteArray hardwar = hardwarHead();
    quint16 proCategroy=0;
    memcpy(&proCategroy,hardwar.constBegin(),2);
    quint16 programCategroy=0;
    memcpy(&programCategroy,hardwar.constBegin()+4,2);
    if(EProductCategory(proCategroy)==EProductCategory::EPC_SenderCard){
        switch(EProgramCategory(programCategroy)){
        case EProgramCategory::EPC_MCU:
         return 0xF011;		//发送卡MCU升级文件
        case EProgramCategory::EPC_FPGA:
            return 0xF012;	//发送卡FPGA升级文件
        case EProgramCategory::EPC_HDMIChip:
            return 0xF001;	//发送卡Monitor升级文件
        default:
            return 0x0000;
        }
    }
    if(EProductCategory(proCategroy)==EProductCategory::EPC_ReceiveCard){
        switch(EProgramCategory(programCategroy)){
        case EProgramCategory::EPC_MCU:
         return 0xF021;	//接收卡MCU升级文件
        case EProgramCategory::EPC_FPGA:
            return 0xF022;	//接收卡FPGA升级文件
        default:
            return 0x0000;
        }
    }
    if(EProductCategory(proCategroy)==EProductCategory::EPC_VideoProcessor){
        if(EProgramCategory(programCategroy)==EProgramCategory::EPC_HDMIChip){
            return 0xF001;	//发送卡Monitor升级文件
        }
    }
    return 0x0000;
}

QByteArray LBLFileTransferChecker::data()
{
    open();
    QByteArray data;
    if(m_file.isOpen()&&m_file.isReadable()){
        if(m_file.size()>m_fileHeadLength){
            quint64 len=m_file.size()-m_fileHeadLength;
            data.resize(len);
            m_file.seek(m_fileHeadLength);
            m_file.read(data.data(),len);
        }
    }
    close();
    return data;
}

QByteArray LBLFileTransferChecker::rawData()
{
    open();
    QByteArray data;
    if(m_file.isOpen()&&m_file.isReadable()){
        m_file.seek(0);
        data = m_file.readAll();
    }
    close();
    return data;
}

QString LBLFileTransferChecker::lastErrorString()
{
    return QString(tr("FileTransferChecker-lastError: "))+m_lastErrorString;
}

bool LBLFileTransferChecker::check()
{
    if(!open()){
       m_valid=false;
       return m_valid;
    }
    if(m_fileInfo.size()<=0){
        m_lastErrorString = tr("File Length: %1.").arg(m_fileInfo.size());
        m_valid=false;
        return m_valid;
    }
    QString suffix = m_fileInfo.suffix();
    if(suffix==QStringLiteral("qst")){
        m_valid = checkHead();
        if(m_valid){
            m_valid = checkData();
        }
        close();
        return m_valid;
    }
    else{
        m_valid=false;
        close();
        m_lastErrorString = tr("File suffix name does not match.");
        return true;//如果不是qtc，valid会置为false，但是该check函数返回true，因为目前bin还是开放升级
    }
}

bool LBLFileTransferChecker::checkHead()
{
    if(!m_file.isReadable()){
        m_lastErrorString = tr("File is not readable.");
        return false;
    }
    if(m_file.size()<m_fileHeadLength){
        m_lastErrorString = tr("File Length < 256Byte.");
        return false;
    }
    m_fileHead.resize(m_fileHeadLength);
    m_file.read(m_fileHead.data(),m_fileHeadLength);
    quint16 sum=checkSum();
    quint16 calculateSum=getCheckSum_16Bit(m_fileHead.constBegin(),m_fileHeadLength-2);
    bool bRet = sum==calculateSum;
    if(!bRet){
        m_lastErrorString = tr("checkHead Faild.");
    }
    return bRet;
}

bool LBLFileTransferChecker::checkData()
{
    if(!m_file.isReadable()){
        m_lastErrorString = tr("File is not readable.");
        return false;
    }
    if(m_file.size()<m_fileHeadLength){
        m_lastErrorString = tr("File Length < 256Byte.");
        return false;
    }
    if(m_file.size()<=m_fileHeadLength){
        return false;
    }
    //读取文件数据
    quint64 len=m_file.size()-m_fileHeadLength;
    m_fileData.resize(len);
    m_file.seek(m_fileHeadLength);
    m_file.read(m_fileData.data(),len);
    //计算MD5
    QByteArray result;
    QCryptographicHash md(QCryptographicHash::Md5);
    md.addData(m_fileData);
    result=md.result();
    bool bRet = result==fileMD5();
    if(!bRet){
        m_lastErrorString = tr("checkData Faild.");
    }
    return bRet;
}

quint16 LBLFileTransferChecker::getCheckSum_16Bit(const char *pData, int dataLen)
{
    quint32 checkSum = 0;
    quint16 *pData16 = nullptr;
    int iPos = 0;
    while(dataLen >=2)
    {
        pData16 = (quint16*)(pData + iPos);
        checkSum += (*pData16);

        dataLen -= 2;
        iPos += 2;
    }
    if (dataLen == 1)
    {
        Q_ASSERT(0);	//适应len为奇数情况，本程序中不会出现
        checkSum += *(quint8*)(pData + iPos);
    }
    //高位有进位，进位到低位，下面两行代码保证了高16位为0。
    while (checkSum >> 16)
    {
        checkSum = (checkSum >> 16) + (checkSum & 0xffff);
    }
    return (quint16)(~checkSum);
}
