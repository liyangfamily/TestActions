#include "LBL_CommunicatEngine/LBLInteCtrlReceiveCardPackage.h"

/*********************************************************************************************************
** LBLPackageInteCtrl_WriteRCFPGARegister                                                                    
*********************************************************************************************************/
LBLPackageInteCtrl_WriteRCFPGARegister::LBLPackageInteCtrl_WriteRCFPGARegister(quint8 port, quint8 module, quint32 addr, const QByteArray& data) :
	m_portIndex(port), m_moduleIndex(module), m_addr(addr), m_writeData(data)
{
	m_dataLength = m_writeData.size();
}

quint16 LBLPackageInteCtrl_WriteRCFPGARegister::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_WriteRCFPGARegister::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_portIndex, 1);
	temp.append((char *)&m_moduleIndex, 1); 
	temp.append((char *)&m_addr, 4);
	temp.append((char *)&m_dataLength, 2);
	temp.append(m_writeData);
	return temp;
}

/*********************************************************************************************************
** LBLPackageInteCtrl_ReadRCFPGARegister
*********************************************************************************************************/
LBLPackageInteCtrl_ReadRCFPGARegister::LBLPackageInteCtrl_ReadRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 length) :
	m_portIndex(port), m_moduleIndex(module), m_addr(addr), m_dataLength(length)
{

}

quint16 LBLPackageInteCtrl_ReadRCFPGARegister::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadRCFPGARegister::getPortIndex() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
    memcpy(&value, buffer.constData() + 2, 1);
	return value;
}

quint8 LBLPackageInteCtrl_ReadRCFPGARegister::getModuleIndex() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 4) {
		return value;
	}
    memcpy(&value, buffer.constData() + 3, 1);
	return value;
}

quint32 LBLPackageInteCtrl_ReadRCFPGARegister::getAddress() const
{
	quint32 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 8) {
		return value;
	}
    memcpy(&value, buffer.constData() + 4, 4);
	return value;
}

quint16 LBLPackageInteCtrl_ReadRCFPGARegister::getDataLength() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 10) {
		return value;
	}
    memcpy(&value, buffer.constData() + 8, 2);
	return value;
}

QByteArray LBLPackageInteCtrl_ReadRCFPGARegister::getReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 11) {
		return value;
	}
	value.append(buffer.mid(10, buffer.size() - 10));
	return value;
}

QByteArray LBLPackageInteCtrl_ReadRCFPGARegister::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_portIndex, 1);
	temp.append((char *)&m_moduleIndex, 1);
	temp.append((char *)&m_addr, 4);
	temp.append((char *)&m_dataLength, 2);
	return temp;
}

/*********************************************************************************************************
** LBLPackageInteCtrl_WriteSaveRCParam
*********************************************************************************************************/

LBLPackageInteCtrl_WriteSaveRCParam::LBLPackageInteCtrl_WriteSaveRCParam(quint8 port, quint16 module) :
	m_portIndex(port), m_moduleIndex(module)
{
}


quint16 LBLPackageInteCtrl_WriteSaveRCParam::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_WriteSaveRCParam::CmdContent() const
{
	QByteArray temp;
	temp.append(m_portIndex);
	temp.append((char *)&m_moduleIndex, 2);
	return temp;
}

/*********************************************************************************************************
** LBLPackageInteCtrl_ReadRCStatusInfo
*********************************************************************************************************/
QByteArray LBLPackageInteCtrl_ReadRCStatusInfo::CmdContent() const
{
	QByteArray temp;
	temp.append(m_portStart);
	temp.append(m_portCount);
	temp.append(m_moduleStart);
	temp.append(m_moduleCount);
	temp.append(m_lengthFlag);
	return temp;
}

LBLPackageInteCtrl_ReadRCStatusInfo::LBLPackageInteCtrl_ReadRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag):
	m_portStart(portStart),m_portCount(portCount),m_moduleStart(moduleStart),m_moduleCount(moduleCount),m_lengthFlag(lengthFlag)
{
}

quint16 LBLPackageInteCtrl_ReadRCStatusInfo::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadRCStatusInfo::getPortIndex() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	value = buffer.at(2);
	return value;
}

quint8 LBLPackageInteCtrl_ReadRCStatusInfo::getModuleIndex() const
{
	quint8 value = 0;
	quint8 pos = 4;
	QByteArray buffer = getContent();
	if (buffer.size() < pos) {
		return value;
	}
	value = buffer.at(pos - 1);
	return value;
}

quint32 LBLPackageInteCtrl_ReadRCStatusInfo::getModuleCount() const
{
	quint8 value = 0;
	quint8 pos = 5;
	QByteArray buffer = getContent();
	if (buffer.size() < pos) {
		return value;
	}
	value = buffer.at(pos - 1);
	return value;
}

quint32 LBLPackageInteCtrl_ReadRCStatusInfo::getModuleEndIndex() const
{
	quint8 value = 0;
	quint8 pos = 5;
	QByteArray buffer = getContent();
	if (buffer.size() < pos) {
		return value;
	}
	value = buffer.at(pos - 1);
	return value;
}

QByteArray LBLPackageInteCtrl_ReadRCStatusInfo::getOldReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 6) {
		return value;
	}
	value.append(buffer.constData() + 5, buffer.size() - 5);
	return value;
}

QByteArray LBLPackageInteCtrl_ReadRCStatusInfo::getReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	value.append(buffer.constData() + 2, buffer.size() - 2);
	return value;
}

/*********************************************************************************************************
** LBLPackageInteCtrl_ReadRCStatusInfo
*********************************************************************************************************/
LBLPackageInteCtrl_ReadRCMonitorInfo::LBLPackageInteCtrl_ReadRCMonitorInfo(quint32 addr, quint16 length):
	m_addr(addr),m_dataLength(length)
{

}

quint16 LBLPackageInteCtrl_ReadRCMonitorInfo::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint32 LBLPackageInteCtrl_ReadRCMonitorInfo::getAddress() const
{
	quint32 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 5) {
		return value;
	}
    memcpy(&value, buffer.constData() + 2, 3);
	return value;
}

quint16 LBLPackageInteCtrl_ReadRCMonitorInfo::getDataLength() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 7) {
		return value;
	}
    memcpy(&value, buffer.constData() + 5, 2);
	return value;
}

QByteArray LBLPackageInteCtrl_ReadRCMonitorInfo::getReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 8) {
		return value;
	}
	value.append(buffer.constData() + 7, buffer.size() - 7);
	return value;
}

QByteArray LBLPackageInteCtrl_ReadRCMonitorInfo::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_addr, 3);
	temp.append((char *)&m_dataLength, 2);
	return temp;
}

quint16 LBLPackageInteCtrl_WriteModuleParam::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint16 LBLPackageInteCtrl_ReadModuleParam::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_ReadModuleParam::getReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 2) {
		return value;
	}
	value.append(buffer.constData() + 2, buffer.size() - 2);
	return value;
}
