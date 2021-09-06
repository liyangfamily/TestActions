#pragma once
#include "LBL_CommunicatEngine/LBLInteCtrlPackage.h"

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_SCReadBrightness : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_SCReadBrightness, LBLInteCtrlPackage)
public:

	quint8 getBrightness() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_SCBrightness);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_SCWriteBrightness : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_SCWriteBrightness, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_SCWriteBrightness(quint8 brightness);
	quint16 getOperationResult() const;
	void  setBrightness(quint8 brightness) {
		m_brightness = brightness;
	}
	
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_SCBrightness);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_brightness, 1);
	}
private:
	quint8 m_brightness = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteSCFPGARegister : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteSCFPGARegister, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteSCFPGARegister(quint32 addr, const QByteArray& data);
	quint16 getOperationResult() const;

	void  setAddress(quint32 addr) {
		m_addr = addr;
	}
	void setData(const QByteArray& data) {
		m_dataLength = data.size();
		m_writeData = data;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_SCFPGARegister);
	}
	QByteArray CmdContent() const override;
private:
	quint32 m_addr = 0;
	quint16 m_dataLength = 0;
	QByteArray m_writeData;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadSCFPGARegister : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadSCFPGARegister, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_ReadSCFPGARegister(quint32 addr, quint16 dataLength);
	quint16 getOperationResult() const;
	quint32 getAddress()const;
	quint16 getDataLength()const;
	QByteArray getReplyData()const;

	void  setAddress(quint32 addr) {
		m_addr = addr;
	}
	void setDataLength(quint16 length) {
		m_dataLength = length;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_SCFPGARegister);
	}
	QByteArray CmdContent() const override;
private:
	quint32 m_addr = 0;
	quint16 m_dataLength = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_SendConnection : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_SendConnection, LBLInteCtrlPackage)
public:
	quint16 getOperationResult() const;
	quint8 getOperatFailReason() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_Connection);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadConnection : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadConnection, LBLInteCtrlPackage)
public:
	quint16 getOperationResult() const;
	QByteArray getReplyData()const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_Connection);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};


class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadMCUAppVersion : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadMCUAppVersion, LBLInteCtrlPackage)
public:
	QString getVersion() const;
	 
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_MCUAppVersion);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadMCUBootVersion : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadMCUBootVersion, LBLInteCtrlPackage)
public:
	QString getVersion() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_MCUBootVersion);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteSaveSCParam : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteSaveSCParam, LBLInteCtrlPackage)
public:
	quint16 getOperationResult() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_SaveSCParam);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

/*********************************************************************************************************
**添加发送卡寄存器一些常规固定搭配操作的数据解析类，比如说FPGA版本等                                                                     
*********************************************************************************************************/
