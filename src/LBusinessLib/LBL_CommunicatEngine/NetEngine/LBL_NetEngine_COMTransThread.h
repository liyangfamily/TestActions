#ifndef CVTE_H_LBL_NETENGINE_COMTRANSTHREAD
#define CVTE_H_LBL_NETENGINE_COMTRANSTHREAD
#pragma once
#include "LBL_NetEngine_TransThread.h"

class LBL_NetEngine_COMTransThread : public LBL_NetEngine_TransThread
{
	Q_OBJECT

public:
	explicit LBL_NetEngine_COMTransThread(LBL_NetEngine* pThreadEngine, int nPayLoad = 4096, QObject *parent = 0);
	~LBL_NetEngine_COMTransThread();

private:
	//socket终止后响应
	void closeSocket(QObject* objSocket) override;

public slots:
	/******************************Engine信号响应槽函数********************************/
	//建立连接
	void slot_EstablishCOMConnection(LBL_NetEngine_TransThread* threadid, QString comName) override;
	//发送数据
	void slot_SendData(QObject* objSocket, LBLEnginePackage) override;

	/******************************内部响应槽函数********************************/
protected slots:
	//socket收到数据后响应
	void slot_New_Data_Recieved() override;
	//socket发送数据后响应
	void slot_Some_Data_Sended(qint64) override;
	//socket发生错误后响应
	void slot_DisplayError(QSerialPort::SerialPortError serialError) override;
};
#endif