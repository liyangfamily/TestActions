/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/

/*!
\class LBLPackage

\inmodule LBL_CommunicatEngine

\brief The class is an abstract class of intelCtrl protocol packages.

LBLPackage::build(): it is responsible for constructing data packets in accordance with the protocol.

\code

\endcode

\note:
This class is the base class of all protocol packets and is generally not use.
*/

#include "LBL_CommunicatEngine/LBLPackage.h"

static quint16 g_serialNum = 0;

LBLPackage::LBLPackage()
{
}

LBLPackage::LBLPackage(const QByteArray & data) :m_data(data)
{
}

LBLPackage::~LBLPackage()
{
}

LBLPackage::LBLPackage(const LBLPackage & package)
{
	*this = package;
}

LBLPackage & LBLPackage::operator=(const LBLPackage & package)
{
	if (this == &package)
	{
		return *this;
	}
	m_data = package.m_data;

	m_targetDeviceType = package.m_targetDeviceType;
	m_sourceDeviceType = package.m_sourceDeviceType;
	m_uuidType = package.m_uuidType;
	m_uuid = package.m_uuid;
	m_sendCardIndex = package.m_sendCardIndex;
	return *this;
}

QByteArray LBLPackage::getDataToSend() const
{
	return m_data; 
}

bool LBLPackage::initByDetectInfo(const SDetectItemInfo* info)
{
	if (!info)
	{
		return false;
	}
	this->m_uuidType = info->uuidType;
	this->m_uuid = info->uuid;
	this->m_sendCardIndex = info->senderCardIndex;
	return true;
}

void LBLPackage::SetCmdTargetDevice(quint16 n)
{
	m_targetDeviceType = n;
}

void LBLPackage::SetCmdSourceDevice(quint16 n)
{
	m_sourceDeviceType = n;
}

void LBLPackage::SetCmdUuidType(quint8 n)
{
	m_uuidType = n;
}

void LBLPackage::SetCmdUuid(QUuid n)
{
	m_uuid = n;
}

void LBLPackage::SetCmdSenderIndex(quint8 n)
{
	m_sendCardIndex = n;
}

quint8 LBLPackage::getProtocolNum() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty())
	{
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->protocolNum;
}

quint8 LBLPackage::getProtocolVersion() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty())
	{
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->protocolVersion;
}

quint16 LBLPackage::getCmdNum() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty())
	{
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->cmd;
}

QByteArray LBLPackage::getContent() const
{
	QByteArray data = getData(m_data, EDataBlock::EDB_Content);
	if (data.isEmpty())
	{
		return QByteArray();
	}
	return data;
}

quint16 LBLPackage::getSerialNum() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty())
	{
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->serialNumber;
}

quint8 LBLPackage::getCheckSum() const
{
	QByteArray data = getData(m_data, EDataBlock::EDB_CheckSum);
	if (data.isEmpty())
	{
		return 0;
	}
	return data.front();
}

quint16 LBLPackage::getTargetDevice() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty())
	{
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->targetDeviceType;
}

quint16 LBLPackage::getSourceDevice() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty())
	{
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->sourceDeviceType;
}

quint8 LBLPackage::getUuidType() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty())
	{
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->uuidType;
}

QUuid LBLPackage::getUuid() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty())
	{
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->uuid;
}

quint8 LBLPackage::getSenderCardIndex() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty()) {
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->sendCardIndex;
}

quint16 LBLPackage::getReplayDataLength() const
{
	QByteArray headerData = getData(m_data, EDataBlock::EDB_Header);
	if (headerData.isEmpty()) {
		return 0;
	}
	const SIntegratedCtrlHeader *pHeader = (const SIntegratedCtrlHeader*)headerData.constData();
	return pHeader->dataLength;
}

quint8 LBLPackage::genCheckSum()
{
	quint8 tempCheckSum = 0;
	try
	{
		if (m_data.size() < 9)
		{
			return tempCheckSum;
		}
		QByteArray arrCpy(m_data.data() + 8, m_data.size() - 8);
		tempCheckSum = getCheckSum(arrCpy);
	}
	catch (std::exception e) {
        qDebug() << "LBLPackageInteCtrl::" << "getCheckSum Error : %s "<< e.what();
	}
	return tempCheckSum;
}

quint8 LBLPackage::getCheckSum(const QByteArray & data)
{
	//计算和
	if (data.isEmpty() || data.isNull())
	{
		return 0;
	}

	unsigned char sum = 0;
	for (int i = 0; i < data.size(); i++)
	{
		sum += data.at(i);
	}
	return sum;
}

LBLPackage & LBLPackage::build(quint16 serialNum)
{
    Q_UNUSED(serialNum)
	m_data.clear();

	SIntegratedCtrlHeader sendHeader;
	sendHeader.protocolNum = CmdProtocolNum();
	sendHeader.protocolVersion = CmdProtocolVersion();
	sendHeader.targetDeviceType = CmdTargetDevice();
	sendHeader.sourceDeviceType = CmdSourceDevice();
	sendHeader.cmd = CmdNum();
	sendHeader.serialNumber = g_serialNum++;
	sendHeader.uuidType = CmdUuidType();
	sendHeader.uuid = CmdUuid();
	sendHeader.sendCardIndex = CmdSenderIndex();
	sendHeader.dataLength = CmdContent().size();
	m_data.append((char*)(&sendHeader), sizeof(SIntegratedCtrlHeader));
	if (sendHeader.dataLength > 0)
	{
		//拷贝数据内容
		m_data.append(CmdContent());
	}
	//计算和
	quint8 tempCheckSum = genCheckSum();
	m_data.append(tempCheckSum);
	return *this;
}


quint8 LBLPackage::CmdProtocolNum() const
{
	qDebug() << "LBLPackage::you need to implement ProtocolNum(const QByteArray & data) into Subclass.";
	return quint8();
}

quint8 LBLPackage::CmdProtocolVersion() const
{
	qDebug() << "LBLPackage::you need to implement ProtocolVersion() into Subclass.";
	return quint8();
}

quint16 LBLPackage::CmdNum() const
{
	qDebug() << "LBLPackage::you need to implement CmdNum() into Subclass.";
    return quint16();
}

quint16 LBLPackage::CmdRetNum() const
{
	qDebug() << "LBLPackage::you need to implement CmdRetNum() into Subclass.";
	return quint16();
}

QByteArray LBLPackage::CmdContent() const
{
	qDebug() << "LBLPackage::you need to implement CmdContent() into Subclass.";
	return QByteArray();
}

quint16 LBLPackage::CmdTargetDevice() const
{
	return m_targetDeviceType;
}

quint16 LBLPackage::CmdSourceDevice() const
{
	return m_sourceDeviceType;
}

quint8 LBLPackage::CmdUuidType() const
{
	return m_uuidType;
}

QUuid LBLPackage::CmdUuid() const
{
	return m_uuid;
}

quint8 LBLPackage::CmdSenderIndex() const
{
	return m_sendCardIndex;
}

void LBLPackage::onReceive(const LBLPackage & package)
{
	m_callBack(package.getDataToSend());
}

QByteArray LBLPackage::getData(const QByteArray & data, quint8 index)
{
	QByteArray tempData;
    quint64 datalen = data.size();
	if (datalen < sizeof(SIntegratedCtrlHeader))
	{
		return tempData;
	}
	switch (EDataBlock(index))
	{
	case LBLPackage::EDB_Header:
	{
		//头数据
		tempData.append(data.data(), sizeof(SIntegratedCtrlHeader));
	}
	break;
	case LBLPackage::EDB_Content:
	{
		//校验包长度
		if (datalen <= (sizeof(SIntegratedCtrlHeader) + 1))
		{
			return tempData;
		}
		int byteLeft = datalen - sizeof(SIntegratedCtrlHeader) - 1;
		tempData.append(data.data() + sizeof(SIntegratedCtrlHeader), byteLeft);
	}
	break;
	case LBLPackage::EDB_CheckSum:
	{
		//校验包长度
		if (datalen <= (sizeof(SIntegratedCtrlHeader) + 1))
		{
			return tempData;
		}
		tempData.append(data.back());
	}
	break;
	default:
		break;
	}
	return tempData;
}
