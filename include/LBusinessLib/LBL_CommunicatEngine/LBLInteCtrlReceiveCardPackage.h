#pragma once
#include "LBL_CommunicatEngine/LBLInteCtrlPackage.h"

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteRCFPGARegister : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteRCFPGARegister, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteRCFPGARegister(quint8 port, quint8 module, quint32 addr, const QByteArray& data);
	quint16 getOperationResult() const;

	void setPortIndex(quint8 port) {
		m_portIndex = port;
	}
	void setModuleIndex(quint8 module) {
		m_moduleIndex = module;
	}
	void  setAddress(quint32 addr) {
		m_addr = addr;
	}
	void setData(const QByteArray& data) {
		m_dataLength = data.size();
		m_writeData = data;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_RCFPGARegister);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_portIndex = 0;
	quint8 m_moduleIndex = 0;
	quint32 m_addr = 0;
	quint16 m_dataLength = 0;
	QByteArray m_writeData;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadRCFPGARegister : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadRCFPGARegister, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_ReadRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 length);

	quint16 getOperationResult() const;
	quint8 getPortIndex()const;
	quint8 getModuleIndex()const;
	quint32 getAddress()const;
	quint16 getDataLength()const;
	QByteArray getReplyData()const;

	void setPortIndex(quint8 port) {
		m_portIndex = port;
	}
	void setModuleIndex(quint8 module) {
		m_moduleIndex = module;
	}
	void  setAddress(quint32 addr) {
		m_addr = addr;
	}
	void setDataLength(quint16 length) {
		m_dataLength = length;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_RCFPGARegister);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_portIndex = 0;
	quint8 m_moduleIndex = 0;
	quint32 m_addr = 0;
	quint16 m_dataLength = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteSaveRCParam : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteSaveRCParam, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteSaveRCParam(quint8 port, quint16 module);
	void setPortIndex(quint8 port) {
		m_portIndex = port;
	}
	void setModuleIndex(quint16 module) {
		m_moduleIndex = module;
	}
	quint16 getOperationResult() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_SaveRCParam);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_portIndex = 0;
	quint16 m_moduleIndex = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadRCStatusInfo : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadRCStatusInfo, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_ReadRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag);

	quint16 getOperationResult() const;
	quint8 getPortIndex()const; //西安协议解析用
	quint8 getModuleIndex()const; //西安协议解析用
	quint32 getModuleCount()const; //西安协议解析用
	quint32 getModuleEndIndex()const; //西安协议解析用
	QByteArray getOldReplyData()const; //西安协议解析用
	QByteArray getReplyData()const;

	void setPortStart(quint8 portStart) {
		m_portStart = portStart;
	}
	void setPortCount(quint8 portCount) {
		m_portCount = portCount;
	}
	void  setModuleStart(quint32 moduleStart) {
		m_moduleStart = moduleStart;
	}
	void setModuleCount(quint16 moduleCount) {
		m_moduleCount = moduleCount;
	}
	void setLengthFlag(quint16 lengthFlag) {
		m_lengthFlag = lengthFlag;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_RCStatusInfo);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_portStart = 0;
	quint8 m_portCount = 0;
	quint8 m_moduleStart = 0;
	quint8 m_moduleCount = 0;
	quint8 m_lengthFlag = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadRCMonitorInfo : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadRCMonitorInfo, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_ReadRCMonitorInfo(quint32 addr, quint16 length);

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
		return quint16(ECommand::EC_Read_RCMonitorInfo);
	}
	QByteArray CmdContent() const override;
private:
	quint32 m_addr = 0;
	quint16 m_dataLength = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteModuleParam : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteModuleParam, LBLInteCtrlPackage)
public:
	quint16 getOperationResult() const;

	void setData(const QByteArray& data) {
		m_writeData = data;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_ModuleParam);
	}
	QByteArray CmdContent() const override {
		return m_writeData;
	}
private:
	QByteArray m_writeData;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadModuleParam : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadModuleParam, LBLInteCtrlPackage)
public:
	quint16 getOperationResult() const;
	QByteArray getReplyData()const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_ModuleParam);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};
