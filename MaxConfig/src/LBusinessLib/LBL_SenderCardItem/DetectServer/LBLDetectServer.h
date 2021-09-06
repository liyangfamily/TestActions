/*********************************************************************************************************
** This file is part of the LBL_SenderCardItem module of the LBL Toolkit.
*********************************************************************************************************/
#pragma once
#include "LBL_SenderCardItem/LBLSCItemGlobal.h"
#include "LBL_SenderCardItem/LBLSCItemStruct_BaseDef.h"
#include <LBL_CommunicatEngine/LBLCluster>
#include <LBL_CommunicatEngine/LBLPackageManager>

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>


class LBLDetectServer : public QObject
{
	Q_OBJECT

public:
	LBLDetectServer(QObject *parent = 0);
	~LBLDetectServer();
	 
	const QList<SDetectItemInfo>& getDetectInfoList();

private:
	bool event(QEvent* e) override;
	void checkHeartBeating(int msec = 60000);
	void prepareComDevice();
	void prepareNetDevice();
	quint16 onParsingInteCtrlDetectInfo(const QByteArray& data);
signals:
	void sig_ConnectToUDP(const QString & address, quint16 nPort);
	void sig_ConnectToCOM(QString comName);
	void sig_DisconnectFromCOM(QObject*objSocket);
	void sig_StartDetect();
	void sig_SingleDetectComplite();
	void sig_DetectComplite();
public slots:
	bool slot_startDetectServer(quint16 detectIntervalTime = 1 * 1000, quint16 everyDetectIntervalTime = 30 * 1000, quint16 everyDetectCount = 2);
	void slot_stopDetectServer();
private slots:
	void slot_ParsingDataFrame(QObject* objSocket, LBLEnginePackage pack);
	void slot_detectTimeOut();
private:
	QList<SDetectItemInfo> m_detectList;
	SDetectItemInfo m_curDetectInfo;
	QMutex m_mutex_protect;

	QTimer m_checkHeartBeatingTimer;
	QTimer m_singleDetectTimer;
	QTimer m_detectServerTimer;

	int m_detectIntervalTime = 1 * 1500;//ms
	int m_everyDetectIntervalTime = 30 * 1000;//ms
	int m_targetDetectCount = 2;
	static int m_detectCount;
	
	LBLPackageManager m_manager;
};
