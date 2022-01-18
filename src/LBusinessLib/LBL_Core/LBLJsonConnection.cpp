#include "LBL_Core/LBLJsonConnection.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>


/**
 * LBLJsonModule
 *
 */
LBLSModule::LBLSModule()
{
}

LBLSModule::LBLSModule(qint16 index, QRectF rect)
{
    setIndex(index);
    setRect(rect);
}


void LBLSModule::setIndex(qint16 index)
{
    m_index = index;
}

qint16 LBLSModule::index() const
{
    return m_index;
}

void LBLSModule::setRect(QRectF rect)
{
    m_rect = rect;
}

QRectF LBLSModule::rect() const
{
    return m_rect;
}

void LBLSModule::resetJsonData()
{
    setIndex(-1);
    setRect(QRectF());
}

bool LBLSModule::buildJson(QJsonDocument &doc, const qint8 version)
{
    Q_UNUSED(version);
    QJsonObject moduleObj;
    // build 模组
    moduleObj["index"] = m_index;
    moduleObj["x"] = m_rect.x();
    moduleObj["y"] = m_rect.y();
    moduleObj["width"] = m_rect.width();
    moduleObj["height"] = m_rect.height();

    //设置doc
    doc.setObject(moduleObj);
    return true;
}

bool LBLSModule::parseJson(const QJsonDocument &doc, const qint8 version)
{
    Q_UNUSED(version);
    if (!doc.isObject())
    {
        qDebug() << "jsonDocument type error.";
        return false;
    }
    // parse 模组
    QJsonObject moduleObj = doc.object();
    m_index = moduleObj["index"].toInt();
    m_rect = QRectF(moduleObj["x"].toDouble(), moduleObj["y"].toDouble(), moduleObj["width"].toDouble(), moduleObj["height"].toDouble());
    return true;
}



/**
 * LBLJsonPort
 *
 */
LBLSPort::LBLSPort()
{

}

LBLSPort::LBLSPort(qint8 index, QRectF rect)
{
    setIndex(index);
    setRect(rect);
}

void LBLSPort::setIndex(qint16 index)
{
    m_index = index;
}

qint16 LBLSPort::index() const
{
    return m_index;
}

void LBLSPort::setRect(QRectF rect)
{
    m_rect = rect;
}

QRectF LBLSPort::rect() const
{
    return m_rect;
}

void LBLSPort::setBackupEnable(bool value)
{
    m_backupEnable = value;
}

bool LBLSPort::isBackupEnable() const
{
    return m_backupEnable;
}

void LBLSPort::setSrcBackupPort(quint8 value)
{
    m_srcBackupPort = value;
}

quint8 LBLSPort::srcBackupPort() const
{
    return m_srcBackupPort;
}

quint16 LBLSPort::moduleCount() const
{
    return m_moduleMap.count();
}

LBLSModule &LBLSPort::module(qint16 index)
{
    if (m_moduleMap.contains(index)) {
        return m_moduleMap[index];
    }
    else {
        static LBLSModule errorModule;
        return errorModule;
    }
}

QList<LBLSModule> LBLSPort::moduleList() const
{
    return m_moduleMap.values();
}

bool LBLSPort::addModule(const LBLSModule &module)
{
    if (module.index() < 0)
        return false;
    m_moduleMap.insert(module.index(), module);
    return true;
}

bool LBLSPort::removeModule(const qint16 index)
{
    return m_moduleMap.remove(index);
}

void LBLSPort::resetJsonData()
{
    setIndex(-1);
    setRect(QRectF());
    setBackupEnable(false);
    setSrcBackupPort(0xFF);
    m_moduleMap.clear();
}

bool LBLSPort::fromByteArray(const QByteArray &array)
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

bool LBLSPort::buildJson(QJsonDocument &doc, const qint8 version)
{
    Q_UNUSED(version);
    QJsonObject portObj;

    // 基本信息
    portObj["index"] = m_index;

    // build 网口区域
    QJsonObject rectObj;
    rectObj["x"] = m_rect.x();
    rectObj["y"] = m_rect.y();
    rectObj["width"] = m_rect.width();
    rectObj["height"] = m_rect.height();

    portObj["rect"] = rectObj;

    // build 网口备份
    QJsonObject backObj;
    backObj["enable"] = m_backupEnable;
    backObj["srcPort"] = m_srcBackupPort;

    portObj["backUp"] = backObj;

    // build 模组
    QJsonArray moduleArray;
    for (auto &&item : m_moduleMap)
    {
        QJsonDocument tempDoc;
        if (item.buildJson(tempDoc))
        {
            if (tempDoc.isObject())
            {
                moduleArray.append(tempDoc.object());
            }
        }
    }
    portObj["module"] = moduleArray;

    //设置doc
    doc.setObject(portObj);
    return true;
}

bool LBLSPort::parseJson(const QJsonDocument &doc, const qint8 version)
{
    Q_UNUSED(version);
    if (!doc.isObject())
    {
        qDebug() << "jsonDocument type error.";
        return false;
    }
    // 基础信息
    QJsonObject portObj = doc.object();
    m_index = portObj["index"].toInt();

    // parse 网口区域
    QJsonObject rectObj = portObj["rect"].toObject();
    m_rect = QRectF(rectObj["x"].toDouble(), rectObj["y"].toDouble(), rectObj["width"].toDouble(), rectObj["height"].toDouble());

    // parse 网口备份
    QJsonObject backObj = portObj["backUp"].toObject();
    m_backupEnable = backObj["enable"].toBool();
    m_srcBackupPort = backObj["srcPort"].toInt();

    // parse 模组
    m_moduleMap.clear();
    QJsonArray moduleArray = portObj["module"].toArray();
    for (auto &&item : moduleArray)
    {
        QJsonDocument tempDoc;
        if (item.isObject())
        {
            tempDoc.setObject(item.toObject());
        }
        LBLSModule tempModule;
        tempModule.parseJson(tempDoc);
        m_moduleMap.insert(tempModule.index(), tempModule);
    }

    return true;
}



/**
 * LBLJsonConnection
 *
 */
QUuid LBLJsonConnection::uuid() const
{
    return m_uuid;
}

QRectF LBLJsonConnection::rect() const
{
    return boundingRect();
}

void LBLJsonConnection::setParseVersion(const LBLJsonConnection::EVersion version)
{
    m_parseVersion = version;
}

LBLJsonConnection::EVersion LBLJsonConnection::parseVersion() const
{
    return m_parseVersion;
}

quint16 LBLJsonConnection::portCount() const
{
    return m_portMap.count();
}

LBLSPort &LBLJsonConnection::port(qint8 portIndex)
{
    if (m_portMap.contains(portIndex)) {
        return m_portMap[portIndex];
    }
    else {
        static LBLSPort errorPort;
        return errorPort;
    }
}

QList<LBLSPort> LBLJsonConnection::portList() const
{
    return m_portMap.values();
}

bool LBLJsonConnection::addPort(const LBLSPort &value)
{
    m_portMap.insert(value.index(), value);
    return true;
}

bool LBLJsonConnection::removePort(const quint8 index)
{
    return m_portMap.remove(index);
}

void LBLJsonConnection::resetJsonData()
{
    setParseVersion(EVersion::StdV1);
    m_rect = QRectF();
    m_portMap.clear();
}

bool LBLJsonConnection::buildJson(QJsonDocument &doc, const qint8 version)
{
    QJsonObject sendCardObj;

    // 基本信息
    sendCardObj["uuid"] = m_uuid.toString();
    sendCardObj["version"] = version;

    // build 发送卡区域
    m_rect = boundingRect();
    QJsonObject rectObj;
    rectObj["x"] = m_rect.x();
    rectObj["y"] = m_rect.y();
    rectObj["width"] = m_rect.width();
    rectObj["height"] = m_rect.height();

    sendCardObj["rect"] = rectObj;

    // build 发送卡备份
    QJsonObject backObj;

    // build 网口
    QJsonArray portArray;
    for (auto &&item : m_portMap)
    {
        QJsonDocument tempDoc;
        if (item.buildJson(tempDoc))
        {
            if (tempDoc.isObject())
            {
                portArray.append(tempDoc.object());
            }
        }
    }
    sendCardObj["port"] = portArray;

    //设置doc
    doc.setObject(sendCardObj);
    return true;
}

bool LBLJsonConnection::parseJson(const QJsonDocument &doc, const qint8 version)
{
    Q_UNUSED(version);
    if (!doc.isObject())
    {
        qDebug() << "jsonDocument type error.";
        return false;
    }
    // 基础信息
    QJsonObject sendCardObj = doc.object();
    EVersion jsonVersion = (EVersion)sendCardObj["version"].toInt();
    if (jsonVersion > m_supportParseVersion)
    {
        qDebug() << "jsonDocument version:"<<jsonVersion<<",not supported.";
        return false;
    }
    m_uuid = sendCardObj["uuid"].toString();

    // parse 发送卡区域
    QJsonObject rectObj = sendCardObj["rect"].toObject();
    m_rect = QRectF(rectObj["x"].toDouble(), rectObj["y"].toDouble(), rectObj["width"].toDouble(), rectObj["height"].toDouble());

    // parse 发送卡备份
    QJsonObject backObj;

    // parse 网口
    m_portMap.clear();
    QJsonArray portArray = sendCardObj["port"].toArray();
    for (auto &&item : portArray)
    {
        QJsonDocument tempDoc;
        if (item.isObject())
        {
            tempDoc.setObject(item.toObject());
        }
        LBLSPort tempPort;
        tempPort.parseJson(tempDoc);
        m_portMap.insert(tempPort.index(), tempPort);
    }

    return true;
}

QRectF LBLJsonConnection::boundingRect() const
{
    QRectF boundingRect;
    for (auto&& item : m_portMap) {
        boundingRect |= item.rect();
    }
    return boundingRect;
}



/**
 * LBLJsonConnectionCluster
 *
 */
LBLJsonConnection *LBLJsonConnectionCluster::connection(QUuid uuid)
{
    if (m_sendCardConnectionMap.contains(uuid))
    {
        return &m_sendCardConnectionMap[uuid];
    }
    else
    {
        return nullptr;
    }
}

bool LBLJsonConnectionCluster::addConnection(const LBLJsonConnection& ct)
{
    if (m_sendCardConnectionMap.contains(ct.uuid()))
    {
        qDebug() << "Connection:" << ct.uuid() << ", already exists , update it.";
    }
    m_sendCardConnectionMap.insert(ct.uuid(), ct);
    return true;
}

void LBLJsonConnectionCluster::resetJsonData()
{
    m_sendCardConnectionMap.clear();
}

bool LBLJsonConnectionCluster::buildJson(QJsonDocument &doc, const qint8 version)
{
    Q_UNUSED(version);
    QJsonObject connectionObj;
    // 基本信息

    // build 发送卡
    QJsonArray sendCardArray;
    for (auto &&item : m_sendCardConnectionMap)
    {
        QJsonDocument tempDoc;
        if (item.buildJson(tempDoc))
        {
            if (tempDoc.isObject())
            {
                sendCardArray.append(tempDoc.object());
            }
        }
    }
    connectionObj["sendCard"] = sendCardArray;

    //设置doc
    doc.setObject(connectionObj);
    return true;
}

bool LBLJsonConnectionCluster::parseJson(const QJsonDocument &doc, const qint8 version)
{
    Q_UNUSED(version);
    if (!doc.isObject())
    {
        qDebug() << "jsonDocument type error.";
        return false;
    }
    // 基础信息
    QJsonObject connectionObj = doc.object();

    // parse 发送卡
    m_sendCardConnectionMap.clear();
    QJsonArray sendCardArray = connectionObj["senderCard"].toArray();
    for (auto &&item : sendCardArray)
    {
        QJsonDocument tempDoc;
        if (item.isObject())
        {
            tempDoc.setObject(item.toObject());
        }
        LBLJsonConnection tempSendCard;
        tempSendCard.parseJson(tempDoc);
        m_sendCardConnectionMap.insert(tempSendCard.uuid(), tempSendCard);
    }

    return true;
}

