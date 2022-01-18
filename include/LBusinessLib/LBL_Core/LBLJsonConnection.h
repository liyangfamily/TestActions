/*********************************************************************************************************
** This file is part of the LBL_Core module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLJSONCONNECTION
#define CVTE_H_LBLJSONCONNECTION
#pragma once

#include <LBL_Core/LBLCoreGlobal>
#include <LBL_Core/LBLJsonHelper.h>
#include <QObject>
#include <QMap>
#include <QRectF>
#include <QUuid>

class LBL_CORE_EXPORT LBLSModule : public LBLJsonHelper
{
public:
    LBLSModule();
    LBLSModule(qint16 index, QRectF rect);

    void setIndex(qint16 index);
    qint16 index() const;
    void setRect(QRectF rect);
    QRectF rect() const;

    void resetJsonData();

public:
    bool buildJson(QJsonDocument &doc, const qint8 version = 0);
    bool parseJson(const QJsonDocument &doc, const qint8 version = 0);

protected:
    qint16 m_index = -1;
    QRectF m_rect;
};

class LBL_CORE_EXPORT LBLSPort : public LBLJsonHelper
{
public:
    LBLSPort();
    LBLSPort(qint8 index, QRectF rect);

    void setIndex(qint16 index);
    qint16 index() const;
    void setRect(QRectF rect);
    QRectF rect() const;
    void setBackupEnable(bool value);
    bool isBackupEnable() const;
    void setSrcBackupPort(quint8 value);
    quint8 srcBackupPort() const;
    quint16 moduleCount() const;

    LBLSModule &module(qint16 index);
    QList<LBLSModule> moduleList() const;
    bool addModule(const LBLSModule &module);
    bool removeModule(const qint16 index);

    void resetJsonData();

    bool fromByteArray(const QByteArray &array);
    QByteArray toByteArray();
public:
    bool buildJson(QJsonDocument &doc, const qint8 version = 0);
    bool parseJson(const QJsonDocument &doc, const qint8 version = 0);

protected:
    qint8 m_index = -1;
    QRectF m_rect;
    bool m_backupEnable = false;
    quint8 m_srcBackupPort = 0xFF;
    QMap<int, LBLSModule> m_moduleMap;
};

class LBL_CORE_EXPORT LBLJsonConnection : public LBLJsonHelper
{
public:
    enum EVersion
    {
        StdV1,
        UnknownVersion = -1
    };
    LBLJsonConnection(){};

public:
    QUuid uuid() const;
    QRectF rect() const;
    void setParseVersion(const EVersion version);
    EVersion parseVersion() const;

    quint16 portCount() const;
    LBLSPort &port(qint8 portIndex);
    QList<LBLSPort> portList() const;
    bool addPort(const LBLSPort &);
    bool removePort(const quint8 index);

    void resetJsonData();

public:
    bool buildJson(QJsonDocument &doc, const qint8 version = 0);
    bool parseJson(const QJsonDocument &doc, const qint8 version = 0);

protected:
    QRectF boundingRect() const;

protected:
    const static EVersion m_supportParseVersion = EVersion::StdV1;
    EVersion m_parseVersion = EVersion::StdV1;
    QUuid m_uuid = QUuid::createUuid();
    QRectF m_rect; //解析时用
    QMap<int, LBLSPort> m_portMap;
};

class LBL_CORE_EXPORT LBLJsonConnectionCluster : public LBLJsonHelper
{
public:
    LBLJsonConnectionCluster(){};

public:
    LBLJsonConnection *connection(QUuid uuid);
    bool addConnection(const LBLJsonConnection &ct);
    bool removeConnection(const QUuid uuid);

    void resetJsonData();

public:
    bool buildJson(QJsonDocument &doc, const qint8 version = 0);
    bool parseJson(const QJsonDocument &doc, const qint8 version = 0);

protected:
    QMap<QUuid, LBLJsonConnection> m_sendCardConnectionMap;
};

#endif
