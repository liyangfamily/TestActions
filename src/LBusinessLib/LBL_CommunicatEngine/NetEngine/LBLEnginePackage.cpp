#include "LBL_CommunicatEngine/LBLEnginePackage.h"
#include "LBLEnginePackage_p.h"

LBLEnginePackage::LBLEnginePackage()
{
	//qDebug() << ("1SPackage()");
}

LBLEnginePackage::LBLEnginePackage(QObject *socketObj, ECommunicatType packType, EPackageFromType fromType)
{
	//qDebug() << ("2SPackage()");
	m_packType = packType;
	m_fromType = fromType;
	m_socketObj = socketObj;
}

LBLEnginePackage::LBLEnginePackage(const LBLEnginePackage&other)
{
	*this = other;
	//qDebug() << ("3SPackage()");
}

LBLEnginePackage::~LBLEnginePackage()
{
	//qDebug() << ("~SPackage()");
}

ECommunicatType LBLEnginePackage::type() const
{
	return m_packType;
}

void LBLEnginePackage::setType(ECommunicatType value)
{
	m_packType = value;
}

EPackageFromType LBLEnginePackage::fromType() const
{
	return m_fromType;
}

void LBLEnginePackage::setFromType(EPackageFromType value)
{
	m_fromType = value;
}

QObject* LBLEnginePackage::socketObj() const
{
	return m_socketObj;
}

void LBLEnginePackage::setSocketObj(QObject * value)
{
	m_socketObj = value;
}

QUuid LBLEnginePackage::exclusiveKey() const
{
	return m_exclusiveKey;
}

void LBLEnginePackage::setExClusiveKey(QUuid uuid)
{
	m_exclusiveKey = uuid;
}

QByteArray LBLEnginePackage::data() const
{
	return m_dataArray;
}

void LBLEnginePackage::setData(const QByteArray &value)
{
	m_dataArray = value;
}

QString LBLEnginePackage::hostAddress() const
{
	return m_hostAddress;
}

void LBLEnginePackage::setHostAddres(const QString &value)
{
	m_hostAddress = value;
}

quint16 LBLEnginePackage::hostPort() const
{
	return m_hostPort;
}

void LBLEnginePackage::setHostPort(const quint16 &value)
{
	m_hostPort = value;
}

void LBLEnginePackage::setNetInfo(const QString &addr, const quint16 &port)
{
	setHostAddres(addr);
	setHostPort(port);
}

void LBLEnginePackage::setComName(QString comName)
{
	m_comName = comName;
}

QString LBLEnginePackage::comName() const
{
	return m_comName;
}

QString LBLEnginePackage::hostName() const
{
	QString hostName;
	//if (m_fromType == EPackageFromType::EPFT_Receive)
	{
		switch (m_packType)
		{
		case EPT_NULL:
			break;
		case ECT_UDP:
		case ECT_TCP:
			hostName = genHostName(m_hostAddress, m_hostPort);
			break;
		case ECT_COM:
			hostName = genHostName(m_comName);
			break;
		default:
			break;
		}
	}
	//else
	{
		//qDebug() << "Send Package Can't Get Hostname.";
	}
	return hostName;
}

bool LBLEnginePackage::isEmpty() const
{
	return m_dataArray.isEmpty();
}

QString LBLEnginePackage::genHostName(const QString & addr, const quint16 &port)
{
	return QString(addr + ":" + QString::number(port));
}

QString LBLEnginePackage::genHostName(QString comName)
{
	return comName;
}

bool LBLEnginePackage::initByDetectInfo(const SDetectItemInfo* info)
{
	this->setSocketObj(info->socketObj);
	this->setType(info->communType);
	this->setFromType(EPackageFromType::EPFT_Send);
	if (info->communType == ECommunicatType::ECT_TCP || info->communType == ECommunicatType::ECT_UDP)
	{
		this->setNetInfo(info->netInfo.ipAddr, info->netInfo.port);
	}
	else if(info->communType==ECommunicatType::ECT_COM)
	{
		this->setComName(info->comInfo.comName);
	}
	return true;
}

//QVariant SPackage::exData(int role) const
//{
//	for (int i = 0; i < values.count(); ++i)
//		if (values.at(i).role == role)
//			return values.at(i).value;
//	return QVariant();
//}
//
//void SPackage::setExData(int role, const QVariant & value)
//{
//	bool found = false;
//	for (int i = 0; i < values.count(); ++i) {
//		if (values.at(i).role == role) {
//			if (values.at(i).value == value)
//				return;
//			values[i].value = value;
//			found = true;
//			break;
//		}
//	}
//	if (!found)
//		values.append(SPackageData(role, value));
//}

//bool SPackage::udpPackageCheck(const SPackage & package, QHostAddress & addr, quint16 & port)
//{
//	if (package.packageType() != EPackageType::EPT_UDP || package.packageData().size() == 0)
//	{
//		return false;
//	}
//	QVariant tempVariant = package.exData(EPackageRole::EPR_NetAddress);
//	if (tempVariant.canConvert<QHostAddress>())
//	{
//		addr = tempVariant.value<QHostAddress>();
//	}
//	else
//	{
//		qDebug() << QObject::tr("LBL_NetEngine_UDPTransThread::packageCheck----Can't Convert the Package IP");
//		return false;
//	}
//	tempVariant = package.exData(EPackageRole::EPR_NetPort);
//	if (tempVariant.canConvert<quint16>())
//	{
//		port = tempVariant.value<quint16>();
//	}
//	else
//	{
//		qDebug() << QObject::tr("LBL_NetEngine_UDPTransThread::packageCheck----Can't Convert the Package Port");
//		return false;
//	}
//	return true;
//}

LBLEnginePackage & LBLEnginePackage::operator=(const LBLEnginePackage & other)
{
	m_packType = other.m_packType;
	m_fromType = other.m_fromType;
	m_socketObj = other.m_socketObj;
	m_dataArray = other.m_dataArray;

	m_hostAddress = other.m_hostAddress;
	m_hostPort = other.m_hostPort;
	m_comName = other.m_comName;

	m_exclusiveKey = other.m_exclusiveKey;
	//values = other.values;

	return *this;
}
