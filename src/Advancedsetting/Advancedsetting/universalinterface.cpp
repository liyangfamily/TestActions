#include "universalinterface.h"
#include <QFile>
#include <qfile.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "advancedsetting.h"
#include <LAPIControl>
#include <fstream>
#include <iostream>


UniversalInterface::UniversalInterface(QObject *parent)
{
    Q_UNUSED(parent);
}


//UniversalInterface& UniversalInterface::GetInstance(void)
//{
//    static UniversalInterface instance;
//    return instance;
//}


//void UniversalInterface::SetModulepara(QByteArray para)
//{
//    ModulePara = para;
//}
//QByteArray UniversalInterface::GetModulepara()
//{
//    return ModulePara;
//}






QByteArray UniversalInterface::Readbin(QString path)
{
    QByteArray ba;
    QFile f(path);      //定义一个文件
    if (f.open(QIODevice::ReadOnly))       //打开文件
    {
        ba = f.readAll();
        f.close();
        //qDebug() << ba;
    }
    else
    {
        //qDebug() << "Failed";
    }
    return ba;
}

bool UniversalInterface::Writebin(QString path, QByteArray bytes)
{
    QFile f(path);      //定义一个文件
    if (f.open(QIODevice::WriteOnly))       //打开文件
    {
        QDataStream qs(&f);             //定义一个数据流
        int i = 0;
        for(i=0;i<bytes.length();i++)
        {
            qs << (uint8_t)bytes[i];      //把数组中的数据写到数据流，即写入文件中
        }
        f.close();
        return true;
    }
    else
    {
        //qDebug() << "Failed";
        return false;
    }
}
void UniversalInterface::MessageBoxShow(QString title,QString str)
{
    QMessageBox msg(NULL);//对话框设置父组件
    msg.setWindowTitle(title);//对话框标题
    msg.setText(str);//对话框提示文本
    msg.setIcon(QMessageBox::NoIcon);//设置图标类型
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox:: Cancel);//对话框上包含的按钮

    if(msg.exec() == QMessageBox::Ok)//模态调用
    {
        msg.close();
    }
}

bool UniversalInterface::SendALLPara()
{
    LAPI::EResult ret1 = LAPI::WriteModuleParam(0xFF,0xFF,ModulePara);
    LAPI::EResult ret2 = LAPI::WriteDriveICParam(0xFF,0xFF,ICPara);
    LAPI::EResult ret3 = LAPI::WriteDecodingICParam(0xFF,0xFF,DataPara);


//    qDebug() << "ret1:" <<ret1<<"---ret2:"<<ret2<<"---ret3:"<<ret3;
    if ((ret1 == LAPI::EResult::ER_INTECTRL_Success) && (ret2 == LAPI::EResult::ER_INTECTRL_Success) && (ret3 == LAPI::EResult::ER_INTECTRL_Success))
    {
        UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//ModulePara.bin",ModulePara);
        UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//DataPara.bin",DataPara);
        UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//ICPara.bin",ICPara);
        return true;
    }
    else
    {
        return false;
    }
}

bool UniversalInterface::ReadALLPara()
{
    ModulePara = LAPI::ReadModuleParam(0,0);
    ICPara = LAPI::ReadDriveICParam(0,0);
    DataPara = LAPI::ReadDecodingICParam(0,0);

    //     qDebug() << "-----ModulePara.length:" << ModulePara.length();
    //     qDebug() << "-----ICPara.length:" << ICPara.length();
    //     qDebug() << "-----DataPara.length:" << DataPara.length();

    if ((ModulePara.length() == 1024) && (ICPara.length() == 1024) && DataPara.length() == 1024)
    {
        UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//ModulePara.bin",ModulePara);
        UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//DataPara.bin",DataPara);
        UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//ICPara.bin",ICPara);
        return true;
    }
    else
    {
        return false;
    }
}




QByteArray UniversalInterface::ReadcsvContent(std::string ICorMOS,QString Filename)
{
    std::string csvDir = LBLUIHelper::appParamDataLocation().toStdString() + "//Default" + ICorMOS + "//" + Filename.toStdString();
    std::ifstream csvFile(csvDir,std::ifstream::in);
    if (!csvFile)
    {
        std::cout<<"Could NOT find " << ICorMOS << " file!"<<std::endl;
        return nullptr;
    }
    else
    {
        std::string content;
        std::vector<uchar> ReadValue;
        while(getline(csvFile,content))
        {
            QString str = content.data();
            uchar value = ConvertHexChar(str[2].toLatin1()) * 16 + ConvertHexChar(str[3].toLatin1());
            ReadValue.push_back(value);
        }
        QByteArray retValue;retValue.resize(ReadValue.size());
        for (int i=0;i<retValue.length();i++)
        {
            retValue[i] = ReadValue[i];
        }
        return retValue;
    }
}
char UniversalInterface::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}
QString UniversalInterface::GetICFilename(quint16 ICNumber)
{
    QString dirpath = LBLUIHelper::appParamDataLocation() + "//DefaultDriverIC";
    //dirpath 设置要遍历的目录
    QDir dir(dirpath);
    //设置文件过滤器
    QStringList nameFilters;
    //设置文件过滤格式
    nameFilters << "*.csv";
    //将过滤后的文件名称存入到files列表中
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    for(int i=0;i<files.count();i++)
    {
        if ("DriverIC" == files[i].split('-')[0])
        {
            QString strfileNumber = files[i].split('-')[1];
            if (strfileNumber.length() == 4)
            {
                quint16 Filenumber = (ConvertHexChar(strfileNumber[0].toLatin1()) * 4096) + (ConvertHexChar(strfileNumber[1].toLatin1()) * 256) + (ConvertHexChar(strfileNumber[2].toLatin1()) * 16) + ConvertHexChar(strfileNumber[3].toLatin1());
                if (Filenumber == ICNumber)
                {
                    return files[i];
                }
            }
        }
    }
    return "";
}
QString UniversalInterface::GetMOSFilename(uchar ICNumber)
{
    QString dirpath = LBLUIHelper::appParamDataLocation() + "//DefaultMOS";
    //dirpath 设置要遍历的目录
    QDir dir(dirpath);
    //设置文件过滤器
    QStringList nameFilters;
    //设置文件过滤格式
    nameFilters << "*.csv";
    //将过滤后的文件名称存入到files列表中
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    for(int i=0;i<files.count();i++)
    {
        if ("MOS" == files[i].split('-')[0])
        {
            QString strfileNumber = files[i].split('-')[1];
            if (strfileNumber.length() == 2)
            {
                uchar Filenumber = (ConvertHexChar(strfileNumber[0].toLatin1()) * 16) + ConvertHexChar(strfileNumber[1].toLatin1());
                if (Filenumber == ICNumber)
                {
                    return files[i];
                }
            }
        }
    }
    return "";
}








