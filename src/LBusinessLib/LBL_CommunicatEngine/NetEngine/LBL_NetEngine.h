#ifndef CVTE_H_LBL_NETENGINE
#define CVTE_H_LBL_NETENGINE
#pragma once

#include <LBL_CommunicatEngine/LBLEnginePackage>

#include <QObject>
#include <QThread>
#include <QHostAddress>
#include <QScopedPointer>
#include <QAbstractSocket>
#include <QSerialPort>
#include <QUuid>

class LBL_NetEngine_TransThread;
class LBL_NetEngine : public QObject
{
	Q_OBJECT
public:
	explicit LBL_NetEngine(int nPayLoad = 4096, QObject *parent = 0);
	~LBL_NetEngine();

	void creatTransThreads(int nThreads);
	void removeTransThreads(int nThreads);
	//断开所有
	void disconnectAll();
	//立刻设置为不活动
	void deactiveImmediately();
	//when Program exit, wait for close; use this funcion after use kickallCliens();deacticeImmediately();
	bool canExit();

protected:
	//删除某个传输线程
	bool transThreadDelete(LBL_NetEngine_TransThread* threadid);
private:
	void creatUDPTransThreads(int nThreads);
	void creatCOMTransThreads(int nThreads);
signals:
	/*********************************发往外部信号**********************************/
	//向外部发送消息信号
	void sig_Message(QObject * objSocket, QString);
	//向外部发送卡socket错误信息信号
	void sig_SocketError(QObject * objSocket, QAbstractSocket::SocketError socketError);
	void sig_SocketError(QObject * objSocket, QSerialPort::SerialPortError serialError);
	//向外部发送socket终止信号
	void sig_SocketAbort(QObject* objSocket);
	//向外部发送收到数据信号
	void sig_Data_Received(QObject* objSocket, LBLEnginePackage);
	//向外部发送发送数据信号
	void sig_Data_Sended(QObject* objSocket, qint64);
	//向外部发送连接建立的信号，信号内容会被替换为结构体
	void sig_NewUDPConnectionEstablish(QObject* objSocket, const QString& addr, quint16 port);
	void sig_NewCOMConnectionEstablish(QObject* objSocket, QString comName);

	/*********************************发往TransThread信号**********************************/
	//向TransThread发送建立连接信号
	void sig_EstablishUDPConnection(LBL_NetEngine_TransThread* threadid, const QString& addr, quint16 port);
	void sig_EstablishCOMConnection(LBL_NetEngine_TransThread* threadid, QString comName);
	//向TransThread发送数据
	void sig_SendData(QObject * objSocket, LBLEnginePackage);
	//向TransThread发送断开连接信号
	void sig_Disconnect(QObject* objSocket); //通知某个socket剔除它的的连接
	//向TransThread发送断开所有连接信号
	void sig_DisconnectAll(LBL_NetEngine_TransThread* threadid);
	//向TransThread发送立即设置为不活动且断块所有连接信号
	void sig_DeactivteImmediately(LBL_NetEngine_TransThread* threadid);

public slots:
	/******************************外部信号响应槽函数********************************/
	//发送数据
	void slot_SendData(QObject * objSocket, LBLEnginePackage);
	//断开某个连接
	void slot_Disconnect(QObject * objSocket);
	//与目标建立连接
	bool slot_ConnectToUDP(const QString & address, quint16 nPort);
	bool slot_ConnectToCOM(QString comName);
protected:
	int m_nThread = 2;
	int m_nPayLoad;
	QVector<LBL_NetEngine_TransThread*> m_vec_TransThreads;
	QVector<QThread*> m_vec_InternalTransThreads;
};
#endif
