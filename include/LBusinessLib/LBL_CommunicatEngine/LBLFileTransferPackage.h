/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLFILETRANSFERPACKAGE
#define CVTE_H_LBLFILETRANSFERPACKAGE
#pragma once

#include <LBL_CommunicatEngine/LBLPackage>

class LBL_COMMUNICATENGINE_EXPORT LBLFileTransferPackage : public LBLPackage
{
    friend class LBLPackageManager;
    friend class LBLPackageDispatcher;
public:
    enum ECommand {
        //通用文件传输
        EC_Common_RequestFile = 0xF001,
        EC_Common_StartSendFile = 0xF003,
        EC_Common_StartSendFile_New = 0xF011,
        EC_Common_SendFileData = 0xF005,
        EC_Common_RequestUpgrade = 0xF00C,
        EC_Common_QueryUpgradeStatus = 0xF00E,
        EC_Common_RequestUpgrade_New = 0xF013,

        //广州发送卡MCU支持的升级功能
        EC_ForMCU_RequestUpgrad = 0xC601,
        EC_ForMCU_SendUpgradData = 0xC603,
        EC_ForMCU_RequestFile = 0xC605,
        EC_ForMCU_ReceiveFileData= 0xC607,
        //
        EC_NULL = 0xFFFF,
    };

    //文件类型
    enum EFileType {
        EFT_SenderMonitor = 0xF001,	//发送卡Monitor升级文件
        EFT_SenderMCU = 0xF011,		//发送卡MCU升级文件
        EFT_SenderFPGA = 0xF012,	//发送卡FPGA升级文件
        EFT_SenderParam = 0xF013,	//发送卡参数文件
        EFT_ReciverMCU = 0xF021,	//接收卡MCU升级文件
        EFT_ReciverFPGA = 0xF022,	//接收卡FPGA升级文件
        EFT_ReciverParam = 0xF023,	//接收卡参数文件
        EFT_ConnectionFile = 0xF024,//连接关系文件
        EFT_GammaFile = 0xF025,		//Gamma文件16K
        EFT_GammaFile_512B = 0xF026,		//Gamma文件512B
        EFT_GammaFile_16Bit = 0xF027,		//Gamma文件,8Bit-16Bit
        EFT_GammaFile_24Bit = 0xF028,		//Gamma文件,8Bit-24Bit
        EFT_LinearTableFile = 0xF029,   //描点表2k
        EFT_GammaFile_10Bit_24Bit = 0xF02A,		//Gamma文件,10Bit-24Bit
        EFT_SelectFile = 0xFFFF,		//选择文件
    };

    //快速传输--文件接收方接收状态
    enum EFileReciverStatus {
        EFRS_ReadFaild = 0x0000,				//读取失败
        EFRS_NormalReturn = 0x0001,				//正常返回
        EFRS_FileIDNotMatch = 0x0002,			//文件识别码不匹配
        EFRS_FileLengthNotMatch = 0x0003,		//文件长度不匹配
        EFRS_SinglePackLengthNotMatch = 0x0004,	//单包长度不匹配
        EFRS_AllPackLengthNotMatch = 0x0005,	//总包数不匹配
        EFRS_TransferComplete = 0x0010,			//已经完成传输
    };

    //通用传输--开始发送卡文件
    enum EStartSendStatus {
        ESSS_Success = 0x0001,			//成功
        ESSS_VerifyFailed = 0x0002,		//验证失败
        ESSS_NotSupportSave = 0x0003,	//不支持保存
    };

    //通用传输--发送文件内容
    enum ESendFileStatus {
        ESFS_Success = 0x0001,				//接收成功
        ESFS_FileTransferComplete = 0x0002,	//文件传输完成
        ESFS_VerifyFaild = 0x0003,			//验证失败
        ESFS_UnknowCauseFaild = 0x0004,		//未知原因失败
    };

    //升级状态
    enum EUpgradeStatus {
        EUS_NULL = 0x00,
        EUS_Erase = 0x01,
        EUS_Upgaradeing = 0x02,
        EUS_Rebooting = 0x03,
        EUS_UpgaradeSucess = 0x04,
        EUS_UpgaradeFaild = 0x05,
        //库定义
        EUS_ConnectionBeingEstablished = 0xF0,
        EUS_TransferringData = 0xF1,
        EUS_Waitting = 0xF2,
    };

public:
    LBLFileTransferPackage();
    LBLFileTransferPackage(const QByteArray& data);
    virtual ~LBLFileTransferPackage();

protected:
    /*********************build时需要获取**************************/
    //集控协议，总定义协议类型和版本
    quint8 CmdProtocolNum() const override;
    quint8 CmdProtocolVersion() const override;
    quint16 CmdRetNum() const override {
        return quint16(CmdNum() + 1);
    }

private:
    void defalutInit();
};

/*********************************************************************************************************
**文件传输协议
*********************************************************************************************************/
class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_CommonRequestFile : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_CommonRequestFile, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_CommonRequestFile(quint16 type, QString name);
    quint16 getOperationResult() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }
    void  setFileName(QString value) {
        m_fileName = value.toUtf8();
        m_fileNameLength = m_fileName.size();
    }
protected:
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_Common_RequestFile);
    }
    QByteArray CmdContent() const override;
private:
    quint16 m_fileType = 0;
    QByteArray m_fileName = 0;
    quint16 m_fileNameLength = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_CommonStartSendFile : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_CommonStartSendFile, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_CommonStartSendFile(quint16 type, quint32 fileLength, QString name);
    quint16 getOperationResult() const;
    quint16 getMaxLengthOfSinglePackage() const;
    quint32 getSendFileID() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }
    void  setFileLength(quint16 value) {
        m_fileLenght = value;
    }
    void  setFileName(QString value) {
        m_fileName = value.toUtf8();
        m_fileNameLength = m_fileName.size();
    }
protected:
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_Common_StartSendFile);
    }
    QByteArray CmdContent() const override;
private:
    quint16 m_fileType = 0;
    quint32 m_fileLenght = 0;
    QByteArray m_fileName = 0;
    quint16 m_fileNameLength = 0;
};


class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_CommonStartSendFile_New : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_CommonStartSendFile_New, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_CommonStartSendFile_New(quint16 fileType, quint32 fileLength, QString fileName, QByteArray fileIdentifyContent,\
                                                   quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
    quint16 getOperationResult() const;
    quint8 getPortIndex() const;
    quint16 getModuleIndex() const;
    quint16 getFileType() const;
    quint16 getMaxLengthOfSinglePackage() const;
    quint32 getSendFileID() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }
    void  setFileLength(quint32 value) {
        m_fileLength = value;
    }
    void  setPortIndex(quint8 value) {
        m_portIndex = value;
    }
    void  setModuleIndex(quint16 value) {
        m_moduleIndex = value;
    }

    void setFileName(QString value){
        m_fileName=value.toUtf8();
        m_fileNameLength=m_fileName.size();
    }

    void setFileIdentifyContent(const QByteArray& value){
        m_fileIdentifyContent=value;
        m_fileIdentifyContentLength=m_fileIdentifyContent.size();
    }

protected:
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_Common_StartSendFile_New);
    }
    QByteArray CmdContent() const override;
private:
    quint8 m_portIndex = 0;
    quint16 m_moduleIndex = 0;
    quint16 m_fileType = 0;
    quint32 m_fileLength = 0;
    quint16 m_fileNameLength = 0;
    QByteArray m_fileName = 0;
    quint16 m_fileIdentifyContentLength = 0;
    QByteArray m_fileIdentifyContent = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_CommonSendFileData : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_CommonSendFileData, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_CommonSendFileData(quint32 sendFileID, quint16 packageIndex, QByteArray package);
    quint16 getOperationResult() const;

    void  setSendFileID(quint32 value) {
        m_sendFileID = value;
    }
    void  setPackageIndex(quint16 value) {
        m_packageIndex = value;
    }
    void  setPackage(QByteArray value) {
        m_package = value;
        m_packageLength = m_package.size();
    }
protected:
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_Common_SendFileData);
    }
    QByteArray CmdContent() const override;
private:
    quint32 m_sendFileID = 0;
    quint16 m_packageIndex = 0;
    QByteArray m_package = 0;
    quint16 m_packageLength = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_CommonRequestUpgrade : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_CommonRequestUpgrade, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_CommonRequestUpgrade(quint16 fileType);
    quint16 getOperationResult() const;
    quint8 getOperatFailReason() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }

protected:
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_Common_RequestUpgrade);
    }
    QByteArray CmdContent() const override;
private:
    quint16 m_fileType = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_CommonRequestUpgrade_New : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_CommonRequestUpgrade_New, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_CommonRequestUpgrade_New(quint16 fileType ,quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
    quint16 getOperationResult() const;
    quint8 getOperatFailReason() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }

    void  setPortIndex(quint8 value) {
        m_portIndex = value;
    }
    void  setModuleIndex(quint16 value) {
        m_moduleIndex = value;
    }

protected:
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_Common_RequestUpgrade_New);
    }
    QByteArray CmdContent() const override;
private:
    quint16 m_fileType = 0;
    quint8 m_portIndex = 0;
    quint16 m_moduleIndex = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_CommonQueryUpgradeStatus : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_CommonQueryUpgradeStatus, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_CommonQueryUpgradeStatus(quint16 fileType);
    quint16 getOperationResult() const;
    quint8 getOperatSteps() const;
    quint8 getOperatProgress() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }

protected:
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_Common_QueryUpgradeStatus);
    }
    QByteArray CmdContent() const override;
private:
    quint16 m_fileType = 0;
};

/*********************************************************************************************************
**广州MCU专用
*********************************************************************************************************/

class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_RequestUpgradeForMCU : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_RequestUpgradeForMCU, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_RequestUpgradeForMCU(quint16 fileType, quint32 fileLength, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
    quint16 getOperationResult() const;
    quint8 getPortIndex() const;
    quint16 getModuleIndex() const;
    quint16 getFileType() const;
    quint16 getMaxLengthOfSinglePackage() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }
    void  setFileLength(quint32 value) {
        m_fileLength = value;
    }
    void  setPortIndex(quint8 value) {
        m_portIndex = value;
    }
    void  setModuleIndex(quint16 value) {
        m_moduleIndex = value;
    }

protected:
    quint8 CmdProtocolNum() const override {
        return quint8(EPackageClass::EPC_IntegratedCtrl);
    }
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_ForMCU_RequestUpgrad);
    }
    QByteArray CmdContent() const override;
private:
    quint16 m_fileType = 0;
    quint32 m_fileLength = 0;
    quint8 m_portIndex = 0;
    quint16 m_moduleIndex = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_SendFileDataForMCU : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_SendFileDataForMCU, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_SendFileDataForMCU(quint16 fileType, quint32 packageIndex, QByteArray package, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
    quint16 getOperationResult() const;
    quint8 getPortIndex() const;
    quint16 getModuleIndex() const;
    quint16 getFileType() const;
    quint32 getPackageIndex() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }
    void  setPackageIndex(quint32 value) {
        m_packageIndex = value;
    }
    void  setPackage(QByteArray value) {
        m_package = value;
    }
    void  setPortIndex(quint8 value) {
        m_portIndex = value;
    }
    void  setModuleIndex(quint16 value) {
        m_moduleIndex = value;
    }
protected:
    quint8 CmdProtocolNum() const override {
        return quint8(EPackageClass::EPC_IntegratedCtrl);
    }
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_ForMCU_SendUpgradData);
    }
    QByteArray CmdContent() const override;
private:
    quint8 m_portIndex = 0;
    quint16 m_moduleIndex = 0;
    quint16 m_fileType = 0;
    quint32 m_packageIndex = 0;
    QByteArray m_package;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_RequestFileForMCU : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_RequestFileForMCU, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_RequestFileForMCU(quint16 fileType);
    quint16 getOperationResult() const;
    quint16 getFileType() const;
    quint32 getTotalFileLength() const;
    quint16 getSinglePackageLenth() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }
protected:
    quint8 CmdProtocolNum() const override {
        return quint8(EPackageClass::EPC_IntegratedCtrl);
    }
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_ForMCU_RequestFile);
    }
    QByteArray CmdContent() const override;
private:
    quint16 m_fileType = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageFileTransfer_ReceiveFileDataForMCU : public LBLFileTransferPackage
{
    LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageFileTransfer_ReceiveFileDataForMCU, LBLFileTransferPackage)
public:
    LBLPackageFileTransfer_ReceiveFileDataForMCU(quint16 fileType, quint32 packageIndex);
    quint16 getOperationResult() const;
    quint16 getFileType() const;
    quint32 getPackageIndex() const;
    QByteArray getPackageData() const;

    void  setFileType(quint16 value) {
        m_fileType = value;
    }
    void  setPackageIndex(quint32 value) {
        m_packageIndex = value;
    }
protected:
    quint8 CmdProtocolNum() const override {
        return quint8(EPackageClass::EPC_IntegratedCtrl);
    }
    quint16 CmdNum() const override {
        return quint16(ECommand::EC_ForMCU_ReceiveFileData);
    }
    QByteArray CmdContent() const override;
private:
    quint16 m_fileType = 0;
    quint32 m_packageIndex = 0;
};
#endif
