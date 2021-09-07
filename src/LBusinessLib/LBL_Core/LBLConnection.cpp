#include "LBL_Core/LBLConnection.h"
#include <QLineF>
#include <QRectF>
#include "LBL_Core/LBLUIHelper"

qint8 LBLSPort::moduleCount() const
{
	return m_moduleAreaMap.size();
}

LBLSModule& LBLSPort::module(qint16 index)
{
	if (m_moduleAreaMap.contains(index)) {
		return m_moduleAreaMap[index];
	}
	else {
		static LBLSModule errorModule(-1);
		return errorModule;
	}
}

bool LBLSPort::addModule(const LBLSModule&module)
{
	if (module.index() < 0)
		return false;
	m_moduleAreaMap.insert(module.index(), module);
	return true;
}

bool LBLSPort::containsModule(const LBLSModule&module) const
{
	return m_moduleAreaMap.contains(module.index());
}

bool LBLSPort::fromByteArray(const QByteArray& array)
{
	if (8 != array.size())
		return false;
	quint16 value;
    memcpy(&value, array.constData(), sizeof(quint16));
	m_rect.setX(value);
    memcpy(&value, array.constData() + 2, sizeof(quint16));
	m_rect.setY(value);
    memcpy(&value, array.constData() + 4, sizeof(quint16));
	m_rect.setWidth(value);
    memcpy(&value, array.constData() + 6, sizeof(quint16));
	m_rect.setHeight(value);
	return true;
}

QByteArray LBLSPort::toByteArray()
{
	QByteArray temp;
	quint16 value = m_rect.x();
	temp.append((char *)&value, 2);
	value = m_rect.y();
	temp.append((char *)&value, 2);
	value = m_rect.width();
	temp.append((char *)&value, 2);
	value = m_rect.height();
	temp.append((char *)&value, 2);
	return temp;
}

#define LBL_TAG_CONNECTION_PORTPACKV0 "CVTE-CONNECTION"
class LBLConnectionData_PortPackageV0
{
public:
	LBLConnectionData_PortPackageV0() {}
	LBLConnectionData_PortPackageV0(const QByteArray& data) :
		m_data(data) {}
	bool valid() {
		unsigned char sum = 0;
		for (int i = 2; i < m_data.size(); ++i) {
			if ((i + 1 -2)% 16 == 0){
				if (sum-1 != (unsigned char)(m_data.at(i)))
					return false;
				else {
					sum = 0;
				}
			}
			else {
				sum += m_data.at(i);
			}
		}
		return true;;
	}
	quint16 packageLength() {
		quint16 length = 0;
		length = moduleCount() * 16 + 2;
		return length;
	}
	virtual quint8 portIndex() {
		quint8 index = 0;
		if (m_data.size() < 1) {
			return index;
		}
		index = m_data.at(0);
		return index;
	}
	virtual quint8 moduleCount() {
		quint8 count = 0;
		if (m_data.size() < 2) {
			return count;
		}
		count = m_data.at(1);
		return count;
	}
	virtual QMap<int, QRectF> moduleRectMap() {
		if (!valid()) {
			return QMap<int, QRectF>();
		}
		QMap<int, QRectF> tempMap;
		QByteArray posData(m_data.constData() + 2, m_data.size() - 2);
        int tempCount = 0;
		tempCount = moduleCount();
		const char* dptr = posData.constData();
		for (int i = 0; i < tempCount; ++i) {
			quint8 moduleIndex = *dptr - 1;
			quint16 startPos_X = 0, startPos_Y = 0, width = 0, height = 0;
			//宽低8位
            memcpy(&width, (dptr + 1), 1);
			//高低8位
            memcpy(&height, (dptr + 2), 1);
			//x
            memcpy(&startPos_X, dptr + 3, 2);
			//y
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
	virtual LBLConnectionData_PortPackageV0& build(const LBLSPort& port) {
		m_data.clear();
		QMap<int, LBLSModule> tempModuleMap = port.getAllModuleMap();
		quint8 moduleCount = tempModuleMap.size();
		m_data.append(port.index());
		m_data.append(moduleCount);
		for (auto it = tempModuleMap.begin(); it != tempModuleMap.end(); ++it) {
			quint16 startPos_X = it->rect().x(), startPos_Y = it->rect().y(), width = it->rect().width(), height = it->rect().height();
			QByteArray temp;
			temp.append(quint8(it->index()+1));
			width -= 1;
			temp.append((char*)&(width), 1);
			height -= 1;
			temp.append((char*)&(height), 1);
			temp.append((char*)&(startPos_X), 2);
			temp.append((char*)&(startPos_Y), 2);
			temp.append(quint8((width >> 8) & 0x000F) | ((height >> 4) & 0x00F0));
			temp.append(QByteArray(7, char(0)));
			quint8 sum = 0;
			for (int i = 0; i < temp.size(); i++) {
				sum += temp.at(i);
			}
			temp.append(sum - 1);
			m_data.append(temp);
		}
		return *this;
	}
	virtual QByteArray getDataToSend() {
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
	LBLConnectionData_PortPackageV1(const QByteArray& data):
		m_data(data){}
	bool valid() {
		unsigned char sum = 0;
		for (int i = 0; i < m_data.size() - 1; i++)	{
			sum += m_data.at(i);
		}
		return sum == (unsigned char)m_data.back();
	}
	quint16 packageLength() {
		quint16 length = 0;
		if (m_data.size() < 2) {
			return length;
		}
        memcpy(&length, m_data.constData(), sizeof(quint16));
		return length;
	}
	virtual quint8 portIndex() {
		quint8 index = 0;
		if (m_data.size() < 3) {
			return index;
		}
		index = m_data.at(2);
		return index;
	}
	virtual quint8 moduleCount() {
		quint8 count = 0;
		if (m_data.size() < 4) {
			return count;
		}
		count = m_data.at(3);
		return count;
	}
	virtual QMap<int, QPointF> modulePosMap() {
		if (!valid()) {
			return QMap<int, QPointF>();
		}
		QMap<int, QPointF> tempMap;
		QByteArray posData(m_data.constData() + 4, m_data.size() - 5);
		int pos = 0, tempCount = 0;
		tempCount = posData.size() / 4;
		if (moduleCount() != tempCount)
			return tempMap;
		for (int i = 0; i < tempCount; ++i) {
			quint16 startPos_X = 0, startPos_Y = 0;
            memcpy(&startPos_X, posData.constData() + pos, sizeof(quint16));
			pos += sizeof(quint16);
            memcpy(&startPos_Y, posData.constData() + pos, sizeof(quint16));
			pos += sizeof(quint16);
			tempMap.insert(i, QPointF(startPos_X, startPos_Y));
		}
		return tempMap;
	}
	virtual LBLConnectionData_PortPackageV1& build(const LBLSPort& port) {
		m_data.clear();
		QMap<int, LBLSModule> tempModuleMap = port.getAllModuleMap();
		quint8 moduleCount = tempModuleMap.size();
		quint16 packageLength = 5 + moduleCount * 4;
		m_data.append((char*)(&packageLength), 2);
		m_data.append(port.index());
		m_data.append(moduleCount);
		for (auto it = tempModuleMap.begin(); it != tempModuleMap.end(); ++it) {
			quint16 startPos_X = 0, startPos_Y = 0;
			startPos_X = it->rect().x();
			m_data.append((char*)(&startPos_X), 2);
			startPos_Y = it->rect().y();
			m_data.append((char*)(&startPos_Y), 2);
		}
		quint8 sum = 0;
		for (int i = 0; i < m_data.size(); i++) {
			sum += m_data.at(i);
		}
		m_data.append(sum);
		return *this;
	}
	virtual QByteArray getDataToSend() {
		return m_data;
	}
protected:
	QByteArray m_data;
};

#define LBL_TAG_CONNECTION_PORTPACKV2 "LData_Connection_2Plus_V2"
class LBLConnectionData_PortPackageV2 :public LBLConnectionData_PortPackageV1
{
public:
	LBLConnectionData_PortPackageV2() {}
	LBLConnectionData_PortPackageV2(const QByteArray& data) :LBLConnectionData_PortPackageV1(data) {}

	quint16 packageType() {
		quint16 value = 0;
		if (m_data.size() < 4) {
			return value;
		}
        memcpy(&value, m_data.constData() + 2, sizeof(quint16));
		return value;
	}
	quint8 portIndex() {
		quint8 value = 0;
		if (m_data.size() < 5) {
			return value;
		}
		value = m_data.at(4);
		return value;
	}
	quint8 backUpEnable() {
		quint8 value = 0;
		if (m_data.size() < 6) {
			return value;
		}
		value = m_data.at(5);
		return value;
	}
	quint8 backUpSrcPort() {
		quint8 value = 0;
		if (m_data.size() < 7) {
			return value;
		}
		value = m_data.at(6);
		return value;
	}
	quint8 moduleCount() {
		quint8 value = 0;
		if (m_data.size() < 8) {
			return value;
		}
		value = m_data.at(7);
		return value;
	}
	 QMap<int, QPointF> modulePosMap() {
		if (!valid()) {
			return QMap<int, QPointF>();
		}
		QMap<int, QPointF> tempMap;
		QByteArray posData(m_data.constData() + 8, m_data.size() - 9);
		int pos = 0, tempCount = 0;
		tempCount = posData.size() / 4;
		if (moduleCount() != tempCount)
			return tempMap;
		for (int i = 0; i < tempCount; ++i) {
			quint16 startPos_X = 0, startPos_Y = 0;
            memcpy(&startPos_X, posData.constData() + pos, sizeof(quint16));
			pos += sizeof(quint16);
            memcpy(&startPos_Y, posData.constData() + pos, sizeof(quint16));
			pos += sizeof(quint16);
			tempMap.insert(i, QPointF(startPos_X, startPos_Y));
		}
		return tempMap;
	}
	 virtual LBLConnectionData_PortPackageV2& build(const LBLSPort& port) {
		 m_data.clear();
		 QMap<int, LBLSModule> tempModuleMap = port.getAllModuleMap();
		 quint8 moduleCount = tempModuleMap.size();
		 quint16 packageLength = 9 + moduleCount * 4;
		 quint16 packageType = 0x0001;
		 m_data.append((char*)(&packageLength), 2);
		 m_data.append((char*)(&packageType), 2);
		 m_data.append(port.index());
		 m_data.append(port.isBackupEnable());
		 m_data.append(port.srcBackupPort());
		 m_data.append(moduleCount);
		 for (auto it = tempModuleMap.begin(); it != tempModuleMap.end(); ++it) {
			 quint16 startPos_X = 0, startPos_Y = 0;
			 startPos_X = it->rect().x();
			 m_data.append((char*)(&startPos_X), 2);
			 startPos_Y = it->rect().y();
			 m_data.append((char*)(&startPos_Y), 2);
		 }
		 quint8 sum = 0;
		 for (int i = 0; i < m_data.size(); i++) {
			 sum += m_data.at(i);
		 }
		 m_data.append(sum);
		 return *this;
	 }
};

class LBLConnectionPrivate
{
	Q_DECLARE_PUBLIC(LBLConnection)
public:
	LBLConnectionPrivate(){
	}

	LBLConnection* q_ptr = nullptr;
	QRectF m_screenArea;
	quint8 m_moduleRow = 0, m_moduleCol = 0;
	quint16 m_moduleWidth = 0, m_moduleHeight = 0;
	quint8 m_portCount = 0;
	QMap<int, LBLSPort> m_portAreaMap;
};

LBLConnection::LBLConnection():
	d_ptr(new LBLConnectionPrivate)
{
	d_ptr->q_ptr = this;
}

LBLConnection::~LBLConnection()
{

}

LBLConnection & LBLConnection::operator=(const LBLConnection &other)
{
	Q_D(LBLConnection);
	this->clearPort();
	d->m_portAreaMap = other.getPortMap();
	//d->m_screenArea;
	d->m_moduleHeight = other.moduleHeight();
	d->m_moduleWidth = other.moduleWidth();
	d->m_portCount = other.portCount();
	return *this;
}

int LBLConnection::row() const
{
	return d_func()->m_moduleRow;
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

void LBLConnection::setPortCount(qint8 value)
{
	if (value < 0)
		return;
	Q_D(LBLConnection);
	d->m_portCount = value;
}

qint8 LBLConnection::portCount() const
{
	return d_func()->m_portCount;
}

bool LBLConnection::addPort(const LBLSPort &value)
{
	Q_D(LBLConnection);
	d->m_portAreaMap.insert(value.index(), value);
	return true;
}

bool LBLConnection::containsPort(const LBLSPort & value)
{
	return containsPort(value.index());
}

bool LBLConnection::containsPort(qint8 index)
{
	Q_D(LBLConnection);
	return d->m_portAreaMap.contains(index);
}

LBLSPort & LBLConnection::getPort(qint8 portIndex)
{
	Q_D(LBLConnection);
	if (d->m_portAreaMap.contains(portIndex)) {
		return d->m_portAreaMap[portIndex];
	}
	else {
		static LBLSPort errorPort(-1);
		return errorPort;
	}
}

QList<LBLSPort> LBLConnection::getPortList() const
{
	return d_func()->m_portAreaMap.values();
}

QMap<int, LBLSPort> LBLConnection::getPortMap() const
{
	return d_func()->m_portAreaMap;
}

bool LBLConnection::clearPort()
{
	Q_D(LBLConnection);
	d->m_portAreaMap.clear();
	return true;
}

void LBLConnection::clear()
{
	Q_D(LBLConnection);
	clearPort();
	d->m_moduleHeight = 0;
	d->m_moduleWidth = 0;
	d->m_portCount = 0;
	d->m_screenArea = QRectF();
}

QRectF LBLConnection::boundingRect()
{
	Q_D(LBLConnection);
	QRectF boundingRect;
	for (auto item : d->m_portAreaMap) {
		boundingRect |= item.rect();
	}
	return boundingRect;
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
	//col
	for (int i = 0; i < rect.width() / moduleWidth(); ++i) {
		bool find = false;
		for (auto port : d->m_portAreaMap) {
			QRectF portRect = port.rect();
			for (auto item : port.getAllModuleMap()) {
				QRectF itemRect(item.rect().topLeft() + portRect.topLeft(), item.rect().size());
				if (!LBLUIHelper::clipLineWithRect(vline, itemRect).isNull()) {
					find = true;
					break;
				}
			}
			if (find) {
				break;
			}
		}
		if (find) {
			++col;
			col += emptyCount;
			emptyCount = 0;
		}
		else {
			++emptyCount;
		}

		QLineF dxline = QLineF(QPointF(width, 0), QPointF(width, 0));
		vline.setP1(vline.p1() + dxline.p1());
		vline.setP2(vline.p2() + dxline.p2());
	}
	//row
	emptyCount = 0;
	for (int i = 0; i < rect.height() / moduleHeight(); ++i) {
		bool find = false;
		for (auto port : d->m_portAreaMap) {
			QRectF portRect = port.rect();
			for (auto item : port.getAllModuleMap()) {
				QRectF itemRect(item.rect().topLeft() + portRect.topLeft(), item.rect().size());
				if (!LBLUIHelper::clipLineWithRect(hline, itemRect).isNull()) {
					find = true;
					break;
				}
			}
			if (find) {
				break;
			}
		}
		if (find) {
			++row;
			row += emptyCount;
			emptyCount = 0;
		}
		else {
			++emptyCount;
		}
		QLineF dyline = QLineF(QPointF(0, height), QPointF(0, height));
		hline.setP1(hline.p1() + dyline.p1());
		hline.setP2(hline.p2() + dyline.p2());
	}
	d->m_moduleRow = row;
	d->m_moduleCol = col;
}

bool LBLConnection::addModule(qint8 portIndex, const LBLSModule & value)
{
	return getPort(portIndex).addModule(value);
}

bool LBLConnection::containsModule(qint8 portIndex, const LBLSModule &value)
{
	return containsModule(portIndex, value.index());
}

bool LBLConnection::containsModule(qint8 portIndex, qint16 moduleIndex)
{
	return getPort(portIndex).containsModule(moduleIndex);
}

LBLSModule & LBLConnection::module(qint8 portIndex, qint16 moduleIndex)
{
	return getPort(portIndex).module(moduleIndex);
}

quint16 LBLConnection::checkPortLoadArea(const QList<LBLSPort>& data)
{
    quint16 ret = LAPI::EResult::ER_Success;
	for (auto it = data.cbegin(); it != data.cend(); ++it) {
		if (!containsPort(it->index()) && !it->rect().isEmpty()) {
			ret = LAPI::EResult::ER_CONNECT_NetPortLoadingAreaNotMatch;
			continue;
		}
		getPort(it->index()).setRect(it->rect());
	}
	calculateRowAndCol();
	return ret;
}

quint16 LBLConnection::parseConnectionData(const QByteArray & data)
{
	clearPort();
	quint32 datalen = data.size();
	const char * dataptr = data.constData();
	int fileHeaderMaxLen = 32;
	if (32 > datalen)
        return LAPI::EResult::ER_CONNECT_IllegalData;

	QByteArray header(dataptr, fileHeaderMaxLen);
	QString headerStr = header;
	if (headerStr == LBL_TAG_CONNECTION_PORTPACKV1) {
		return parseConnectionDataV1(data);
	}
	else if (headerStr == LBL_TAG_CONNECTION_PORTPACKV2) {
		return parseConnectionDataV2(data);
	}
	else if (headerStr == LBL_TAG_CONNECTION_PORTPACKV0) {
		return parseConnectionDataV0(data);
	}
	else {
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
	data.append((char*)&d->m_moduleWidth, 2);
	data.append((char*)&d->m_moduleHeight, 2);
	data.append(d->m_portCount);
	for (auto it = d->m_portAreaMap.begin(); it != d->m_portAreaMap.end(); ++it) {
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
	data.append((char*)&d->m_moduleWidth, 2);
	data.append((char*)&d->m_moduleHeight, 2);
	data.append(d->m_portCount);
	for (auto it = d->m_portAreaMap.begin(); it != d->m_portAreaMap.end(); ++it) {
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
	Q_D(LBLConnection);
	QByteArray data;
	QByteArray header;
	header.fill(0, 20);
	QByteArray headerStr = LBL_TAG_CONNECTION_PORTPACKV0;
	header.replace(0, headerStr.size(), headerStr);
	data.append(header);
	data.append(d->m_portCount);
	for (auto it = d->m_portAreaMap.begin(); it != d->m_portAreaMap.end(); ++it) {
		LBLConnectionData_PortPackageV0 temp;
		QByteArray bulidData = temp.build(it.value()).getDataToSend();
		data.append(bulidData);
	}
	return data;
}

quint16 LBLConnection::parseConnectionDataV1(const QByteArray & data)
{
	Q_D(LBLConnection);
	quint32 datalen = data.size();
	const char * dataptr = data.constData();
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
    memcpy(&d->m_portCount, dataptr + pos, sizeof(quint8));
	pos += sizeof(quint8);
	
	if (d->m_portCount > LBL_Max_UsingSenderCardPort)
		return LAPI::EResult::ER_CONNECT_IllegalPortCount;

	for (int i=0; i < d->m_portCount; ++i) {
		quint16 packageLength = 0;
		if (pos + sizeof(quint16) > datalen)
            return LAPI::EResult::ER_CONNECT_IllegalData;
        memcpy(&packageLength, dataptr + pos, sizeof(quint16));
        if (quint32(pos + packageLength)> datalen) //判断子包长度
            return LAPI::EResult::ER_CONNECT_IllegalData;

		LBLConnectionData_PortPackageV1 portPack(QByteArray(dataptr + pos, packageLength));
		if (!portPack.valid())
			continue;
		quint8 portIndex = portPack.portIndex();
		addPort(LBLSPort(portIndex));
		LBLSPort& port = getPort(portIndex);

		QMap<int, QPointF> tempMap = portPack.modulePosMap();
		for (auto it = tempMap.begin(); it != tempMap.end(); ++it) {
			port.addModule(LBLSModule(it.key(), QRectF(it.value().x(), it.value().y(), d->m_moduleWidth, d->m_moduleHeight)));
		}

		pos += packageLength;
	}
	return LAPI::EResult::ER_Success;
}

quint16 LBLConnection::parseConnectionDataV2(const QByteArray & data)
{
	Q_D(LBLConnection);
	quint32 datalen = data.size();
	const char * dataptr = data.constData();
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
    memcpy(&d->m_portCount, dataptr + pos, sizeof(quint8));
	pos += sizeof(quint8);

	if (d->m_portCount > LBL_Max_UsingSenderCardPort)
		return LAPI::EResult::ER_CONNECT_IllegalPortCount;

	for (int i = 0; i < d->m_portCount; ++i) {
		quint16 packageLength = 0;
		if (pos + sizeof(quint16) > datalen)
            return LAPI::EResult::ER_CONNECT_IllegalData;
        memcpy(&packageLength, dataptr + pos, sizeof(quint16));
        if (quint32(pos + packageLength )> datalen) //判断子包长度
            return LAPI::EResult::ER_CONNECT_IllegalData;

		LBLConnectionData_PortPackageV2 portPack(QByteArray(dataptr + pos, packageLength));
		if (!portPack.valid())
			continue;
		quint8 portIndex = portPack.portIndex();
		addPort(LBLSPort(portIndex));
		LBLSPort& port = getPort(portIndex);
		port.setBackupEnable(portPack.backUpEnable());
		port.setSrcBackupPort(portPack.backUpSrcPort());
		QMap<int, QPointF> tempMap = portPack.modulePosMap();
		for (auto it = tempMap.begin(); it != tempMap.end(); ++it) {
			port.addModule(LBLSModule(it.key(), QRectF(it.value().x(), it.value().y(), d->m_moduleWidth, d->m_moduleHeight)));
		}

		pos += packageLength;
	}
	return LAPI::EResult::ER_Success;
}

quint16 LBLConnection::parseConnectionDataXA(const QByteArray & data)
{
    Q_UNUSED(data)
	return false;
}

quint16 LBLConnection::parseConnectionDataV0(const QByteArray & data)
{
	Q_D(LBLConnection);
	quint32 datalen = data.size();
	const char * dataptr = data.constData();
    quint8 fileHeaderMaxLen = 20;
    quint16 pos = 0;

	if (fileHeaderMaxLen > datalen)
		return LAPI::EResult::ER_CONNECT_IllegalData;
	QByteArray header(dataptr, fileHeaderMaxLen);
	pos += fileHeaderMaxLen;

    memcpy(&d->m_portCount, dataptr + pos, sizeof(quint8));
	pos += sizeof(quint8);

	if (d->m_portCount > LBL_Max_UsingSenderCardPort)
		return LAPI::EResult::ER_CONNECT_IllegalPortCount;

	for (int i = 0; i < d->m_portCount; ++i) {
		quint8 portIndex = 0, moduleCount = 0;
		if (pos + sizeof(quint8) > datalen) {
			break;
			return LAPI::EResult::ER_CONNECT_IllegalData;
		}
        memcpy(&portIndex, dataptr + pos, sizeof(quint8));
		pos += sizeof(quint8);
		if (pos + sizeof(quint8) > datalen) {
			break;
			return LAPI::EResult::ER_CONNECT_IllegalData;
		}
        memcpy(&moduleCount, dataptr + pos, sizeof(quint8));
		pos += sizeof(quint8);
		quint16 packageLength = moduleCount * 16;
        if (quint32(pos + packageLength )> datalen) { //判断子包长度
			break;
			return LAPI::EResult::ER_CONNECT_IllegalData;
		}

		LBLConnectionData_PortPackageV0 portPack(QByteArray(dataptr + pos - 2, packageLength));
		if (!portPack.valid())
			continue;
		quint8 tempPortIndex = portPack.portIndex();
		addPort(LBLSPort(tempPortIndex));
		LBLSPort& port = getPort(tempPortIndex);

		QMap<int, QRectF> tempMap = portPack.moduleRectMap();
		for (auto it = tempMap.begin(); it != tempMap.end(); ++it) {
			port.addModule(LBLSModule(it.key(), it.value()));
			if (0 == d->m_moduleWidth)
				d->m_moduleWidth = it.value().width();
			if (0 == d->m_moduleHeight)
				d->m_moduleHeight = it.value().height();
		}

		pos += packageLength;
	}
	d->m_portCount = d->m_portAreaMap.size(); //重新计算网口数量
	return LAPI::EResult::ER_Success;
}

