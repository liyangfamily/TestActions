/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/

/*!
\class LBLInteCtrlPackage

\inmodule LBL_CommunicatEngine

\brief The class is base class of the intelCtrl protocol. it is used to define some fixed protocol parameters. 
Generally not used directly. 

\code

\endcode

\note:

*/

#include "LBL_CommunicatEngine/LBLInteCtrlPackage.h"

LBLInteCtrlPackage::LBLInteCtrlPackage()
{
	defalutInit();
}

LBLInteCtrlPackage::LBLInteCtrlPackage(const QByteArray& data):
	LBLPackage(data)
{

}

LBLInteCtrlPackage::~LBLInteCtrlPackage()
{
}

quint8 LBLInteCtrlPackage::CmdProtocolNum() const
{
	return quint8(EPackageClass::EPC_IntegratedCtrl);
}

quint8 LBLInteCtrlPackage::CmdProtocolVersion() const
{
	return quint8(EPackageVersion::EPV_3_0);
}

void LBLInteCtrlPackage::defalutInit()
{
	m_targetDeviceType= EDeviceType::EDT_NULL;
	m_sourceDeviceType= EDeviceType::EDT_CtrlSW;
	m_uuidType = 0;
	m_uuid = QUuid();
	m_sendCardIndex = 0;
}


/*!
\class LBLPackageInteCtrl_DetectInfo

\inmodule LBL_CommunicatEngine

\brief The class is a specific intelCtrl protocol packet. Mainly used to send device status query cmd. 
Generally used to determin the status of the senderCard.

\code
	LBLPackageInteCtrl_DetectInfo detectInfo;
	detectInfo.SetCmdTargetDevice(LBLInteCtrlPackage::EDeviceType::EDT_Android);
	detectInfo.build(0);
	QByteArray writeData = detectInfo.getDataToSend();
\endcode

\note:
The CMD content data is empty.
*/

quint8 LBLPackageInteCtrl_DetectInfo::getStatus() const
{
	quint8 status = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1)
	{
		return status;
	}
	status = buffer.at(0);
	return status;
}

quint8 LBLPackageInteCtrl_DetectInfo::getSenderCardClass() const
{
	quint8 sendeCardType = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2)
	{
		return sendeCardType;
	}
	sendeCardType = buffer.at(1);
	return sendeCardType;
}

quint8 LBLPackageInteCtrl_DetectInfo::getProductType() const
{
	quint8 productType = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3)
	{
		return productType;
	}
	productType = buffer.at(2);

	return productType;
}

quint8 LBLPackageInteCtrl_ReadSenderCardUuid::getSenderCardUuidType() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

QUuid LBLPackageInteCtrl_ReadSenderCardUuid::getSenderCardUuid() const
{
	QUuid value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 17) {
		return value;
	}
	memcpy_s(&value, sizeof(QUuid), buffer.constData() + 1, sizeof(QUuid));
	return value;
}

LBLPackageInteCtrl_WriteSenderCardUuid::LBLPackageInteCtrl_WriteSenderCardUuid(quint8 type, QUuid id):
	m_uuidType(type),m_uuid(id)
{
}

quint16 LBLPackageInteCtrl_WriteSenderCardUuid::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_WriteSenderCardUuid::getSenderCardUuidType() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2) {
		return value;
	}
	value = buffer.at(3);
	return value;
}

QUuid LBLPackageInteCtrl_WriteSenderCardUuid::getSenderCardUuid() const
{
	QUuid value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2+17) {
		return value;
	}
	memcpy_s(&value, sizeof(QUuid), buffer.constData() + 3, sizeof(QUuid));
	return value;
}

QByteArray LBLPackageInteCtrl_WriteSenderCardUuid::CmdContent() const
{
	QByteArray temp;
	temp.append(m_uuidType);
	temp.append(QByteArray((const char*)&m_uuid, sizeof(QUuid)));
	return temp;
}

LBLPackageInteCtrl_Penetrate::LBLPackageInteCtrl_Penetrate(quint16 replyDataLength, quint16 maxWaitTime, const QByteArray& data):
	m_replyDataLength(replyDataLength),m_maxWaitTime(maxWaitTime),m_penetratData(data)
{
}

quint16 LBLPackageInteCtrl_Penetrate::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_Penetrate::getReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() <3) {
		return value;
	}
	value.append(buffer.mid(2, buffer.size() - 2));
	return value;
}

QByteArray LBLPackageInteCtrl_Penetrate::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_replyDataLength, sizeof(quint16));
	temp.append((char *)&m_maxWaitTime, sizeof(quint16));
	temp.append(m_penetratData);
	return temp;
}
