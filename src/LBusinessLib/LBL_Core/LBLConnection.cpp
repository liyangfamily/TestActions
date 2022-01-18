#include "LBL_Core/LBLConnection.h"
#include "LBL_Core/LBLUIHelper"

#include <QLineF>
#include <QRectF>
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

class LBLConnectionPrivate
{
    Q_DECLARE_PUBLIC(LBLConnection)
public:
    LBLConnectionPrivate(){}

    LBLConnection *q_ptr = nullptr;
    quint8 m_moduleRow = 0, m_moduleCol = 0;
    quint16 m_moduleWidth = 0, m_moduleHeight = 0;
};

#define LBL_TAG_CONNECTION_PORTPACKV0 "CVTE-CONNECTION"
class LBLConnectionData_PortPackageV0
{
public:
	LBLConnectionData_PortPackageV0() {}
	LBLConnectionData_PortPackageV0(const QByteArray &data) : m_data(data) {}
	bool valid()
	{
		unsigned char sum = 0;
		for (int i = 2; i < m_data.size(); ++i)
		{
			if ((i + 1 - 2) % 16 == 0)
			{
				if (sum - 1 != (unsigned char)(m_data.at(i)))
					return false;
				else
				{
					sum = 0;
				}
			}
			else
			{
				sum += m_data.at(i);
			}
		}
		return true;
		;
	}
	quint16 packageLength()
	{
		quint16 length = 0;
		length = moduleCount() * 16 + 2;
		return length;
	}
	virtual quint8 portIndex()
	{
		quint8 index = 0;
		if (m_data.size() < 1)
		{
			return index;
		}
		index = m_data.at(0);
		return index;
	}
	virtual quint8 moduleCount()
	{
		quint8 count = 0;
		if (m_data.size() < 2)
		{
			return count;
		}
		count = m_data.at(1);
		return count;
	}
	virtual QMap<int, QRectF> moduleRectMap()
	{
		if (!valid())
		{
			return QMap<int, QRectF>();
		}
		QMap<int, QRectF> tempMap;
		QByteArray posData(m_data.constData() + 2, m_data.size() - 2);
		int tempCount = 0;
		tempCount = moduleCount();
		const char *dptr = posData.constData();
		for (int i = 0; i < tempCount; ++i)
		{
			quint8 moduleIndex = *dptr - 1;
			quint16 startPos_X = 0, startPos_Y = 0, width = 0, height = 0;
			//宽低8位
			memcpy(&width, (dptr + 1), 1);
			//高低8位
			memcpy(&height, (dptr + 2), 1);
			// x
			memcpy(&startPos_X, dptr + 3, 2);
			// y
			memcpy(&startPos_Y, dptr + 5, 2);

			//宽高高位
			quint16 temp = 0;
			memcpy(&temp, dptr + 7, 1);
			width = (width & 0x00FF) | ((temp << 8) & 0x0F00);
			height = (height & 0x00FF) | ((temp << 4) & 0x0F00);
			tempMap.insert(moduleIndex, QRectF(startPos_X, startPos_Y, width + 1, height + 1));

			dptr += 16;
		}
		return tempMap;
	}
    virtual LBLConnectionData_PortPackageV0 &build(const LBLSPort &port)
	{
		m_data.clear();
        QList<LBLSModule> tempModuleList = port.moduleList();
		quint8 moduleCount = tempModuleList.size();
		m_data.append(port.index());
		m_data.append(moduleCount);
		for (auto it = tempModuleList.begin(); it != tempModuleList.end(); ++it)
		{
			quint16 startPos_X = it->rect().x(), startPos_Y = it->rect().y(), width = it->rect().width(), height = it->rect().height();
			QByteArray temp;
			temp.append(quint8(it->index() + 1));
			width -= 1;
			temp.append((char *)&(width), 1);
			height -= 1;
			temp.append((char *)&(height), 1);
			temp.append((char *)&(startPos_X), 2);
			temp.append((char *)&(startPos_Y), 2);
			temp.append(quint8((width >> 8) & 0x000F) | ((height >> 4) & 0x00F0));
			temp.append(QByteArray(7, char(0)));
			quint8 sum = 0;
			for (int i = 0; i < temp.size(); i++)
			{
				sum += temp.at(i);
			}
			temp.append(sum - 1);
			m_data.append(temp);
		}
		return *this;
	}
	virtual QByteArray getDataToSend()
	{
		return m_data;
	}

protected:
	QByteArray m_data;
};

#define LBL_TAG_CONNECTION_PORTPACKV1 "LData_Connection_2Plus_V1"
class LBLConnectionData_PortPackageV1
{
public:
	LBLConnectionData_PortPackageV1() {}
	LBLConnectionData_PortPackageV1(const QByteArray &data) : m_data(data) {}
	bool valid()
	{
		unsigned char sum = 0;
		for (int i = 0; i < m_data.size() - 1; i++)
		{
			sum += m_data.at(i);
		}
		return sum == (unsigned char)m_data.back();
	}
	quint16 packageLength()
	{
		quint16 length = 0;
		if (m_data.size() < 2)
		{
			return length;
		}
		memcpy(&length, m_data.constData(), sizeof(quint16));
		return length;
	}
	virtual quint8 portIndex()
	{
		quint8 index = 0;
		if (m_data.size() < 3)
		{
			return index;
		}
		index = m_data.at(2);
		return index;
	}
	virtual quint8 moduleCount()
	{
		quint8 count = 0;
		if (m_data.size() < 4)
		{
			return count;
		}
		count = m_data.at(3);
		return count;
	}
	virtual QMap<int, QPointF> modulePosMap()
	{
		if (!valid())
		{
			return QMap<int, QPointF>();
		}
		QMap<int, QPointF> tempMap;
		QByteArray posData(m_data.constData() + 4, m_data.size() - 5);
		int pos = 0, tempCount = 0;
		tempCount = posData.size() / 4;
		if (moduleCount() != tempCount)
			return tempMap;
		for (int i = 0; i < tempCount; ++i)
		{
			quint16 startPos_X = 0, startPos_Y = 0;
			memcpy(&startPos_X, posData.constData() + pos, sizeof(quint16));
			pos += sizeof(quint16);
			memcpy(&startPos_Y, posData.constData() + pos, sizeof(quint16));
			pos += sizeof(quint16);
			tempMap.insert(i, QPointF(startPos_X, startPos_Y));
		}
		return tempMap;
	}
    virtual LBLConnectionData_PortPackageV1 &build(const LBLSPort &port)
	{
		m_data.clear();
        QList<LBLSModule> tempModuleList = port.moduleList();
		quint8 moduleCount = tempModuleList.size();
		quint16 packageLength = 5 + moduleCount * 4;
		m_data.append((char *)(&packageLength), 2);
		m_data.append(port.index());
		m_data.append(moduleCount);
		for (auto it = tempModuleList.begin(); it != tempModuleList.end(); ++it)
		{
			quint16 startPos_X = 0, startPos_Y = 0;
			startPos_X = it->rect().x();
			m_data.append((char *)(&startPos_X), 2);
			startPos_Y = it->rect().y();
			m_data.append((char *)(&startPos_Y), 2);
		}
		quint8 sum = 0;
		for (int i = 0; i < m_data.size(); i++)
		{
			sum += m_data.at(i);
		}
		m_data.append(sum);
		return *this;
	}
	virtual QByteArray getDataToSend()
	{
		return m_data;
	}

protected:
	QByteArray m_data;
};

#define LBL_TAG_CONNECTION_PORTPACKV2 "LData_Connection_2Plus_V2"
class LBLConnectionData_PortPackageV2 : public LBLConnectionData_PortPackageV1
{
public:
	LBLConnectionData_PortPackageV2() {}
	LBLConnectionData_PortPackageV2(const QByteArray &data) : LBLConnectionData_PortPackageV1(data) {}

	quint16 packageType()
	{
		quint16 value = 0;
		if (m_data.size() < 4)
		{
			return value;
		}
		memcpy(&value, m_data.constData() + 2, sizeof(quint16));
		return value;
	}
	quint8 portIndex()
	{
		quint8 value = 0;
		if (m_data.size() < 5)
		{
			return value;
		}
		value = m_data.at(4);
		return value;
	}
	quint8 backUpEnable()
	{
		quint8 value = 0;
		if (m_data.size() < 6)
		{
			return value;
		}
		value = m_data.at(5);
		return value;
	}
	quint8 backUpSrcPort()
	{
		quint8 value = 0;
		if (m_data.size() < 7)
		{
			return value;
		}
		value = m_data.at(6);
		return value;
	}
	quint8 moduleCount()
	{
		quint8 value = 0;
		if (m_data.size() < 8)
		{
			return value;
		}
		value = m_data.at(7);
		return value;
	}
	QMap<int, QPointF> modulePosMap()
	{
		if (!valid())
		{
			return QMap<int, QPointF>();
		}
		QMap<int, QPointF> tempMap;
		QByteArray posData(m_data.constData() + 8, m_data.size() - 9);
		int pos = 0, tempCount = 0;
		tempCount = posData.size() / 4;
		if (moduleCount() != tempCount)
			return tempMap;
		for (int i = 0; i < tempCount; ++i)
		{
			quint16 startPos_X = 0, startPos_Y = 0;
			memcpy(&startPos_X, posData.constData() + pos, sizeof(quint16));
			pos += sizeof(quint16);
			memcpy(&startPos_Y, posData.constData() + pos, sizeof(quint16));
			pos += sizeof(quint16);
			tempMap.insert(i, QPointF(startPos_X, startPos_Y));
		}
		return tempMap;
	}
    virtual LBLConnectionData_PortPackageV2 &build(const LBLSPort &port)
	{
		m_data.clear();
        QList<LBLSModule> tempModuleList = port.moduleList();
		quint8 moduleCount = tempModuleList.size();
		quint16 packageLength = 9 + moduleCount * 4;
		quint16 packageType = 0x0001;
		m_data.append((char *)(&packageLength), 2);
		m_data.append((char *)(&packageType), 2);
		m_data.append(port.index());
		m_data.append(port.isBackupEnable());
		m_data.append(port.srcBackupPort());
		m_data.append(moduleCount);
		for (auto it = tempModuleList.begin(); it != tempModuleList.end(); ++it)
		{
			quint16 startPos_X = 0, startPos_Y = 0;
			startPos_X = it->rect().x();
			m_data.append((char *)(&startPos_X), 2);
			startPos_Y = it->rect().y();
			m_data.append((char *)(&startPos_Y), 2);
		}
		quint8 sum = 0;
		for (int i = 0; i < m_data.size(); i++)
		{
			sum += m_data.at(i);
		}
		m_data.append(sum);
		return *this;
	}
};

LBLConnection::LBLConnection() : d_ptr(new LBLConnectionPrivate)
{
    d_ptr->q_ptr = this;
}

LBLConnection::~LBLConnection()
{

}

LBLConnection::LBLConnection(const LBLConnection &ct) : LBLConnection()
{
    cloneConnection(ct);
}

LBLConnection &LBLConnection::operator=(const LBLConnection &ct)
{
    cloneConnection(ct);
    return *this;
}

void LBLConnection::setRow(int value)
{
    d_func()->m_moduleRow = value;
}

int LBLConnection::row() const
{
    return d_func()->m_moduleRow;
}

void LBLConnection::setCol(int value)
{
    d_func()->m_moduleCol = value;
}

int LBLConnection::col() const
{
	return d_func()->m_moduleCol;
}

void LBLConnection::setModuleWidth(qint16 value)
{
	if (value < 0)
		return;
	Q_D(LBLConnection);
	d->m_moduleWidth = value;
}

qint16 LBLConnection::moduleWidth() const
{
	return d_func()->m_moduleWidth;
}

void LBLConnection::setModuleHeight(qint16 value)
{
	if (value < 0)
		return;
	Q_D(LBLConnection);
	d->m_moduleHeight = value;
}

qint16 LBLConnection::moduleHeight() const
{
	return d_func()->m_moduleHeight;
}

void LBLConnection::calculateBaseInfo()
{
	Q_D(LBLConnection);
	for (auto &&i : m_portMap)
	{
		for (auto &&k : i.moduleList())
		{
			d->m_moduleWidth = k.rect().width();
			d->m_moduleHeight = k.rect().height();
			break;
		}
		break;
    }
}

void LBLConnection::calculateRowAndCol()
{
	Q_D(LBLConnection);
	QRectF rect = boundingRect();
	int width = moduleWidth();
	int height = moduleHeight();
	QLineF hline(rect.topLeft() + QPointF(0, height / 2), rect.topRight() + QPointF(0, height / 2));
	QLineF vline(rect.topLeft() + QPointF(width / 2, 0), rect.bottomLeft() + QPointF(width / 2, 0));
	int col = 0;
	int row = 0;
	int emptyCount = 0;
	// col
	for (int i = 0; i < rect.width() / moduleWidth(); ++i)
	{
		bool find = false;
		for (auto &&port : m_portMap)
		{
			QRectF portRect = port.rect();
			for (auto &&item : port.moduleList())
			{
				QRectF itemRect(item.rect().topLeft() + portRect.topLeft(), item.rect().size());
				if (!LBLUIHelper::clipLineWithRect(vline, itemRect).isNull())
				{
					find = true;
					break;
				}
			}
			if (find)
			{
				break;
			}
		}
		if (find)
		{
			++col;
			col += emptyCount;
			emptyCount = 0;
		}
		else
		{
			++emptyCount;
		}

		QLineF dxline = QLineF(QPointF(width, 0), QPointF(width, 0));
		vline.setP1(vline.p1() + dxline.p1());
		vline.setP2(vline.p2() + dxline.p2());
	}
	// row
	emptyCount = 0;
	for (int i = 0; i < rect.height() / moduleHeight(); ++i)
	{
		bool find = false;
		for (auto &&port : m_portMap)
		{
			QRectF portRect = port.rect();
			for (auto &&item : port.moduleList())
			{
				QRectF itemRect(item.rect().topLeft() + portRect.topLeft(), item.rect().size());
				if (!LBLUIHelper::clipLineWithRect(hline, itemRect).isNull())
				{
					find = true;
					break;
				}
			}
			if (find)
			{
				break;
			}
		}
		if (find)
		{
			++row;
			row += emptyCount;
			emptyCount = 0;
		}
		else
		{
			++emptyCount;
		}
		QLineF dyline = QLineF(QPointF(0, height), QPointF(0, height));
		hline.setP1(hline.p1() + dyline.p1());
		hline.setP2(hline.p2() + dyline.p2());
	}
	d->m_moduleRow = row;
	d->m_moduleCol = col;
}

quint16 LBLConnection::checkPortLoadArea(const QList<LBLSPort> &data)
{
	quint16 ret = LAPI::EResult::ER_Success;
	for (auto it = data.cbegin(); it != data.cend(); ++it)
	{
		if (!m_portMap.contains(it->index()) && !it->rect().isEmpty())
		{
			ret = LAPI::EResult::ER_CONNECT_NetPortLoadingAreaNotMatch;
			continue;
		}
		port(it->index()).setRect(it->rect());
	}
	calculateRowAndCol();
	return ret;
}

quint16 LBLConnection::parseConnectionData(const QByteArray &data)
{
	m_portMap.clear();
	quint32 datalen = data.size();
	const char *dataptr = data.constData();
	int fileHeaderMaxLen = 32;
	if (32 > datalen)
		return LAPI::EResult::ER_CONNECT_IllegalData;

	QByteArray header(dataptr, fileHeaderMaxLen);
	QString headerStr = header;
	if (headerStr == LBL_TAG_CONNECTION_PORTPACKV1)
	{
		return parseConnectionDataV1(data);
	}
	else if (headerStr == LBL_TAG_CONNECTION_PORTPACKV2)
	{
		return parseConnectionDataV2(data);
	}
	else if (headerStr == LBL_TAG_CONNECTION_PORTPACKV0)
	{
		return parseConnectionDataV0(data);
	}
	else
	{
		return parseConnectionDataXA(data);
	}
}

QByteArray LBLConnection::buildConnectionDataV1()
{
	Q_D(LBLConnection);
	QByteArray data;
	QByteArray header;
	header.fill(0, 32);
	QByteArray headerStr = LBL_TAG_CONNECTION_PORTPACKV1;
	header.replace(0, headerStr.size(), headerStr);
	data.append(header);
	data.append((char *)&d->m_moduleWidth, 2);
    data.append((char *)&d->m_moduleHeight, 2);
    data.append(portCount());
	for (auto it = m_portMap.begin(); it != m_portMap.end(); ++it)
	{
		LBLConnectionData_PortPackageV1 temp;
		QByteArray bulidData = temp.build(it.value()).getDataToSend();
		data.append(bulidData);
	}
	return data;
}

QByteArray LBLConnection::buildConnectionDataV2()
{
	Q_D(LBLConnection);
	QByteArray data;
	QByteArray header;
	header.fill(0, 32);
	QByteArray headerStr = LBL_TAG_CONNECTION_PORTPACKV2;
	header.replace(0, headerStr.size(), headerStr);
	data.append(header);
	data.append((char *)&d->m_moduleWidth, 2);
	data.append((char *)&d->m_moduleHeight, 2);
    data.append(portCount());
	for (auto it = m_portMap.begin(); it != m_portMap.end(); ++it)
	{
		LBLConnectionData_PortPackageV2 temp;
		QByteArray bulidData = temp.build(it.value()).getDataToSend();
		data.append(bulidData);
	}
	return data;
}

QByteArray LBLConnection::buildConnectionDataXA()
{
	return QByteArray();
}

QByteArray LBLConnection::buildConnectionDataV0()
{
	QByteArray data;
	QByteArray header;
	header.fill(0, 20);
	QByteArray headerStr = LBL_TAG_CONNECTION_PORTPACKV0;
	header.replace(0, headerStr.size(), headerStr);
	data.append(header);
    data.append(portCount());
	for (auto it = m_portMap.begin(); it != m_portMap.end(); ++it)
	{
		LBLConnectionData_PortPackageV0 temp;
		QByteArray bulidData = temp.build(it.value()).getDataToSend();
		data.append(bulidData);
	}
	return data;
}

quint16 LBLConnection::parseConnectionDataV1(const QByteArray &data)
{
	Q_D(LBLConnection);
	quint32 datalen = data.size();
	const char *dataptr = data.constData();
	int fileHeaderMaxLen = 32;
	quint16 pos = 0;

	if (37 > datalen)
		return LAPI::EResult::ER_CONNECT_IllegalData;
	QByteArray header(dataptr, fileHeaderMaxLen);
	pos += fileHeaderMaxLen;

	memcpy(&d->m_moduleWidth, dataptr + pos, sizeof(quint16));
	pos += sizeof(quint16);
	memcpy(&d->m_moduleHeight, dataptr + pos, sizeof(quint16));
	pos += sizeof(quint16);
    quint8 portCount = this->portCount();
    memcpy(&portCount, dataptr + pos, sizeof(quint8));
	pos += sizeof(quint8);

    if (portCount > LBL_Max_UsingSenderCardPort)
		return LAPI::EResult::ER_CONNECT_IllegalPortCount;

    for (int i = 0; i < portCount; ++i)
	{
		quint16 packageLength = 0;
		if (pos + sizeof(quint16) > datalen)
			return LAPI::EResult::ER_CONNECT_IllegalData;
		memcpy(&packageLength, dataptr + pos, sizeof(quint16));
		if (quint32(pos + packageLength) > datalen) //判断子包长度
			return LAPI::EResult::ER_CONNECT_IllegalData;

		LBLConnectionData_PortPackageV1 portPack(QByteArray(dataptr + pos, packageLength));
		if (!portPack.valid())
			continue;
		quint8 portIndex = portPack.portIndex();
		addPort(LBLSPort(portIndex, QRectF()));
        LBLSPort &port = this->port(portIndex);

		QMap<int, QPointF> tempMap = portPack.modulePosMap();
		for (auto it = tempMap.begin(); it != tempMap.end(); ++it)
		{
			port.addModule(LBLSModule(it.key(), QRectF(it.value().x(), it.value().y(), d->m_moduleWidth, d->m_moduleHeight)));
		}

		pos += packageLength;
	}
	return LAPI::EResult::ER_Success;
}

quint16 LBLConnection::parseConnectionDataV2(const QByteArray &data)
{
	Q_D(LBLConnection);
	quint32 datalen = data.size();
	const char *dataptr = data.constData();
	int fileHeaderMaxLen = 32;
	quint16 pos = 0;

	if (37 > datalen)
		return LAPI::EResult::ER_CONNECT_IllegalData;
	QByteArray header(dataptr, fileHeaderMaxLen);
	pos += fileHeaderMaxLen;

	memcpy(&d->m_moduleWidth, dataptr + pos, sizeof(quint16));
	pos += sizeof(quint16);
	memcpy(&d->m_moduleHeight, dataptr + pos, sizeof(quint16));
	pos += sizeof(quint16);
    quint8 portCount = this->portCount();
    memcpy(&portCount, dataptr + pos, sizeof(quint8));
	pos += sizeof(quint8);

    if (portCount > LBL_Max_UsingSenderCardPort)
		return LAPI::EResult::ER_CONNECT_IllegalPortCount;

    for (int i = 0; i < portCount; ++i)
	{
		quint16 packageLength = 0;
		if (pos + sizeof(quint16) > datalen)
			return LAPI::EResult::ER_CONNECT_IllegalData;
		memcpy(&packageLength, dataptr + pos, sizeof(quint16));
		if (quint32(pos + packageLength) > datalen) //判断子包长度
			return LAPI::EResult::ER_CONNECT_IllegalData;

		LBLConnectionData_PortPackageV2 portPack(QByteArray(dataptr + pos, packageLength));
		if (!portPack.valid())
			continue;
		quint8 portIndex = portPack.portIndex();
		addPort(LBLSPort(portIndex, QRectF()));
        LBLSPort &port = this->port(portIndex);
		port.setBackupEnable(portPack.backUpEnable());
		port.setSrcBackupPort(portPack.backUpSrcPort());
		QMap<int, QPointF> tempMap = portPack.modulePosMap();
		for (auto it = tempMap.begin(); it != tempMap.end(); ++it)
		{
			port.addModule(LBLSModule(it.key(), QRectF(it.value().x(), it.value().y(), d->m_moduleWidth, d->m_moduleHeight)));
		}

		pos += packageLength;
	}
	return LAPI::EResult::ER_Success;
}

quint16 LBLConnection::parseConnectionDataXA(const QByteArray &data)
{
	Q_UNUSED(data)
	return false;
}

quint16 LBLConnection::parseConnectionDataV0(const QByteArray &data)
{
	Q_D(LBLConnection);
	quint32 datalen = data.size();
	const char *dataptr = data.constData();
	quint8 fileHeaderMaxLen = 20;
	quint16 pos = 0;

	if (fileHeaderMaxLen > datalen)
		return LAPI::EResult::ER_CONNECT_IllegalData;
	QByteArray header(dataptr, fileHeaderMaxLen);
	pos += fileHeaderMaxLen;
    quint8 portCount = this->portCount();
    memcpy(&portCount, dataptr + pos, sizeof(quint8));
	pos += sizeof(quint8);

    if (portCount > LBL_Max_UsingSenderCardPort)
		return LAPI::EResult::ER_CONNECT_IllegalPortCount;

    for (int i = 0; i < portCount; ++i)
	{
		quint8 portIndex = 0, moduleCount = 0;
		if (pos + sizeof(quint8) > datalen)
		{
			break;
			return LAPI::EResult::ER_CONNECT_IllegalData;
		}
		memcpy(&portIndex, dataptr + pos, sizeof(quint8));
		pos += sizeof(quint8);
		if (pos + sizeof(quint8) > datalen)
		{
			break;
			return LAPI::EResult::ER_CONNECT_IllegalData;
		}
		memcpy(&moduleCount, dataptr + pos, sizeof(quint8));
		pos += sizeof(quint8);
		quint16 packageLength = moduleCount * 16;
		if (quint32(pos + packageLength) > datalen)
		{ //判断子包长度
			break;
			return LAPI::EResult::ER_CONNECT_IllegalData;
		}

		LBLConnectionData_PortPackageV0 portPack(QByteArray(dataptr + pos - 2, packageLength));
		if (!portPack.valid())
			continue;
		quint8 tempPortIndex = portPack.portIndex();
		addPort(LBLSPort(tempPortIndex, QRectF()));
        LBLSPort &port = this->port(tempPortIndex);

		QMap<int, QRectF> tempMap = portPack.moduleRectMap();
		for (auto it = tempMap.begin(); it != tempMap.end(); ++it)
		{
			port.addModule(LBLSModule(it.key(), it.value()));
			if (0 == d->m_moduleWidth)
				d->m_moduleWidth = it.value().width();
			if (0 == d->m_moduleHeight)
				d->m_moduleHeight = it.value().height();
		}

		pos += packageLength;
    }
    return LAPI::EResult::ER_Success;
}

void LBLConnection::cloneConnection(const LBLConnection &ct)
{
    this->setParseVersion(ct.parseVersion());
    this->setCol(ct.col());
    this->setRow(ct.row());
    this->setModuleWidth(ct.moduleWidth());
    this->setModuleHeight(ct.moduleHeight());
    this->resetJsonData();
    this->m_portMap = ct.m_portMap;
    this->m_rect = ct.m_rect;
}
