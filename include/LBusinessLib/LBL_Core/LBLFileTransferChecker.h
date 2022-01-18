#ifndef LBLFILETRANSFERCHECKER_H
#define LBLFILETRANSFERCHECKER_H

#include <LBL_Core/LBLCoreGlobal>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QMetaEnum>

class LBL_CORE_EXPORT LBLFileTransferChecker : public QObject
{
    Q_OBJECT
public:
    enum class EProductCategory{
        EPC_SenderCard = 0x0100,
        EPC_ReceiveCard = 0x0200,
        EPC_VideoProcessor = 0x0300,
    };
    Q_ENUM(EProductCategory);

    enum class EPCBCategory{
        EPC_2ndPCON500 = 0x0101,
        EPC_2ndPCON100 = 0x0201,
        EPC_2ndPlus = 0x0103,
        EPC_PCON600 = 0x0203,
        EPC_3In1_1252 = 0x0102,
        EPC_3In1_H27 = 0x0202,
        EPC_Core_1254 = 0x0302,
        EPC_3In1_1255 = 0x0402,
        EPC_3In1_1256 = 0x0502,
        EPC_3In1_1257 = 0x0602,
        EPC_3In1_V27C27 = 0x0702,
        EPC_3In1_H31 = 0x0802,
    };
    Q_ENUM(EPCBCategory);

    enum class EProgramCategory{
        EPC_FPGA = 0x0100,
        EPC_MCU = 0x0200,
        EPC_HDMIChip = 0x0300,
    };
    Q_ENUM(EProgramCategory);

    template <typename EnmType>
    static EnmType strToEnm(QString strText)
    {
        QMetaEnum metaEnm = QMetaEnum::fromType<EnmType>();
        return (EnmType)metaEnm.keyToValue(strText.toStdString().data());
    }
    template <typename EnmType>
    static QString enmToStr(EnmType enmVal)
    {
        QMetaEnum metaEnm = QMetaEnum::fromType<EnmType>();
        return metaEnm.valueToKey((int)enmVal);
    }

    LBLFileTransferChecker(const QString& filePath);
    bool open();
    bool check();
    void close();

    bool isValid();
    //获取文件信息
    const QFileInfo& fileInfo() const;
    //获取文件头
    QByteArray fileHead();
    //获取硬件识别头
    QByteArray hardwarHead();
    //获取PCB类型
    static QString pcbCategory(const QByteArray& hardwarHead);
    //获取版本号
    QByteArray versionNumber();
    //创建时间
    QString creatTime();
    //获取附加内容的MD5
    QByteArray fileMD5();
    //头校验和
    quint16 checkSum();

    //获取计算的升级文件类型
    quint16 fileType();

    //获取文件内容
    QByteArray data();
    QByteArray rawData();

    //获取失败内容
    QString lastErrorString();

    const static int m_fileHeadLength=256;
    const static int m_hardwarHeadLength=8;
protected:
    bool checkHead();
    bool checkData();
    quint16 getCheckSum_16Bit(const char *pData, int dataLen);
private:
    bool m_valid=false; //用来标志是否可用，如果是qtc则进行解析检查，如果是bin就放行（目前放行）
    QFile m_file;
    QFileInfo m_fileInfo;
    QByteArray m_fileHead;
    QByteArray m_fileData;
    QString m_lastErrorString;
};

#endif // LBLFILETRANSFERCHECKER_H
