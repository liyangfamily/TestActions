#include "LBL_CommunicatEngine/LBLInteCtrlSenderCardPackage.h"

quint8 LBLPackageInteCtrl_SCReadBrightness::getBrightness() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1)
	{
		return value;
	}
	value = buffer.at(0);
	return value;
} 

LBLPackageInteCtrl_SCWriteBrightness::LBLPackageInteCtrl_SCWriteBrightness(quint8 brightness) :
	m_brightness(brightness)
{
} 

quint16 LBLPackageInteCtrl_SCWriteBrightness::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
} 


LBLPackageInteCtrl_WriteSCFPGARegister::LBLPackageInteCtrl_WriteSCFPGARegister(quint32 addr, const QByteArray& data) :
	m_addr(addr), m_writeData(data)
{
	m_dataLength = m_writeData.size();
}

quint16 LBLPackageInteCtrl_WriteSCFPGARegister::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_WriteSCFPGARegister::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_addr, 3);
	temp.append((char *)&m_dataLength, 2);
	temp.append(m_writeData);
	return temp;
}

LBLPackageInteCtrl_ReadSCFPGARegister::LBLPackageInteCtrl_ReadSCFPGARegister(quint32 addr, quint16 dataLength) :
	m_addr(addr), m_dataLength(dataLength)
{
}

quint16 LBLPackageInteCtrl_ReadSCFPGARegister::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint32 LBLPackageInteCtrl_ReadSCFPGARegister::getAddress() const
{
	quint32 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 5) {
		return value;
	}
    memcpy(&value, buffer.constData() + 2, 3);
	return value;
}

quint16 LBLPackageInteCtrl_ReadSCFPGARegister::getDataLength() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 7) {
		return value;
	}
    memcpy(&value, buffer.constData() + 5, 2);
	return value;
}

QByteArray LBLPackageInteCtrl_ReadSCFPGARegister::getReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 8) {
		return value;
	}
	value.append(buffer.mid(7, buffer.size() - 7));
	return value;
}

QByteArray LBLPackageInteCtrl_ReadSCFPGARegister::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_addr, 3);
	temp.append((char *)&m_dataLength, 2);
	return temp;
}

QString LBLPackageInteCtrl_ReadMCUAppVersion::getVersion() const
{
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return QString();
	}
	QString value(buffer.constData());
	return value;
}

QString LBLPackageInteCtrl_ReadMCUBootVersion::getVersion() const
{
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return QString();
	}
	QString value(buffer.constData());
	return value;
}

quint16 LBLPackageInteCtrl_WriteSaveSCParam::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint16 LBLPackageInteCtrl_SendConnection::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_SendConnection::getOperatFailReason() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
    memcpy(&value, buffer.constData() + 2, 1);
	return value;
}

quint16 LBLPackageInteCtrl_ReadConnection::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_ReadConnection::getReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	value.append(buffer.mid(2, buffer.size() - 2));
	return value;
}
