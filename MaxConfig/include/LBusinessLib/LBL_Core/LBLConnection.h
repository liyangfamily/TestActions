/*********************************************************************************************************
** This file is part of the LBL_Core module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLCONNECTION
#define CVTE_H_LBLCONNECTION
#pragma once

#include <LBL_Core/LBLCoreGlobal>
#include <LBL_Core/LAPIDef>
#include <QObject>
#include <QMap>
#include <QRectF>

class LBL_CORE_EXPORT LBLSModule {
public:
	LBLSModule() {}
    LBLSModule(qint16 index) :
		m_index(index) {
	}
    LBLSModule(qint16 index, QRectF area) :
		m_index(index), m_area(area) {
	}
    void setIndex(qint16 index) {
		m_index = index;
	}
    qint16 index() const {
		return m_index;
	}
	void setRect(QRectF rect) {
		m_area = rect;
	}
	QRectF rect() const {
		return m_area;
	}
private:
    qint16 m_index = 0;
	QRectF m_area;
};

class LBL_CORE_EXPORT LBLSPort {
public:
	LBLSPort() {}
	LBLSPort(quint8 index) :
		m_index(index) {
	}
    LBLSPort(qint8 index, QRectF area) :
		m_index(index), m_rect(area) {
	}
    void setIndex(qint16 index) {
		m_index = index;
	}
    qint16 index() const {
		return m_index;
	}
	void setRect(QRectF rect) {
		m_rect = rect;
	}
	QRectF rect() const {
		return m_rect;
	}
	void setBackupEnable(bool value) {
		m_backupEnable = value;
	}
	bool isBackupEnable() const {
		return m_backupEnable;
	}
    void setSrcBackupPort(quint8 value) {
		m_srcBackupPort = value;
	}
    quint8 srcBackupPort() const {
		return m_srcBackupPort;
	}
	qint8 moduleCount() const;
    LBLSModule& module(qint16 index);
	QMap<int, LBLSModule> getAllModuleMap() const {
		return m_moduleAreaMap;
	}
	bool addModule(const LBLSModule&module);
	bool containsModule(const LBLSModule&module) const;

	bool fromByteArray(const QByteArray& array);
	QByteArray toByteArray();
private:
    qint8 m_index = 0;
	QRectF m_rect;
    qint8 m_backupEnable = 0;
    quint8 m_srcBackupPort = 0xFF;
	QMap<int, LBLSModule> m_moduleAreaMap;
};

class LBLConnectionPrivate;
class LBL_CORE_EXPORT LBLConnection : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(LBLConnection)
public:
	LBLConnection();
	~LBLConnection();
	LBLConnection &operator=(const LBLConnection &);
public:
	int row() const;
	int col() const;
    void setModuleWidth(qint16 value);
    qint16 moduleWidth() const;
    void setModuleHeight(qint16 value);
    qint16 moduleHeight() const;
    void setPortCount(qint8 value);
    qint8 portCount() const;

	bool addPort(const LBLSPort&);
	bool containsPort(const LBLSPort&);
    bool containsPort(qint8 index);
    LBLSPort& getPort(qint8 portIndex);
	QList<LBLSPort> getPortList() const;
	QMap<int, LBLSPort> getPortMap() const;
	bool clearPort();
	void clear();
	QRectF boundingRect();
	void calculateRowAndCol();

    bool addModule(qint8 portIndex, const LBLSModule&);
    bool containsModule(qint8 portIndex, const LBLSModule&);
    bool containsModule(qint8 portIndex, qint16 moduleIndex);
    LBLSModule& module(qint8 portIndex, qint16 moduleIndex);

    quint16 checkPortLoadArea(const QList<LBLSPort>& data);
    quint16 parseConnectionData(const QByteArray& data);
	QByteArray buildConnectionDataV1();
	QByteArray buildConnectionDataV2();
	QByteArray buildConnectionDataXA();
	QByteArray buildConnectionDataV0();
protected:
	quint16 parseConnectionDataV1(const QByteArray& data);
	quint16 parseConnectionDataV2(const QByteArray& data);
	quint16 parseConnectionDataXA(const QByteArray& data);
	quint16 parseConnectionDataV0(const QByteArray& data);
private:
	QScopedPointer<LBLConnectionPrivate> d_ptr;
};

#endif
