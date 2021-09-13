#ifndef CVTE_H_LBL_TASKENGINE_INTEGRATEDCTRLTASK
#define CVTE_H_LBL_TASKENGINE_INTEGRATEDCTRLTASK
#pragma once

#include "LBL_CommunicatEngine/LBLEnginePackage.h"
#include "LBL_CommunicatEngine/LBLInteCtrlPackage.h"
#include "../TaskEngine/LBL_TaskEngine_TaskBase.h"

class LBLCluster;
class LBL_TaskEngine_IntegratedCtrlTask : public LBL_TaskEngine_TaskBase
{
    Q_OBJECT
public:
	explicit LBL_TaskEngine_IntegratedCtrlTask(LBLCluster* pCluster, QObject* pSocket, QObject * parent = 0);
	~LBL_TaskEngine_IntegratedCtrlTask();
	int run() override;
	void sendHelloPackage() override;
	void checkHeartBeating() override;
protected:
	//返回使用的字节数
	int filter_message(const LBLEnginePackage&, int offset);
	//处理当前的消息块
	virtual int deal_current_message_block(const LBLEnginePackage&);

protected:
	LBLCluster* m_pCluster;

	SIntegratedFrameLimit m_currentFrameLimit;
	SIntegratedFrameLimit m_standerFrameLimit;
	SIntegratedCtrlHeader m_currentHeader;
};

class LBL_TaskEngine_IntegratedCtrlUDPTask : public LBL_TaskEngine_IntegratedCtrlTask
{
public:
	explicit LBL_TaskEngine_IntegratedCtrlUDPTask(LBLCluster* pCluster, QObject* pSocket, QObject * parent = 0);
	~LBL_TaskEngine_IntegratedCtrlUDPTask();
	void sendHelloPackage() override;
protected:
	int deal_current_message_block(const LBLEnginePackage&) override;
protected:
	quint16 m_tagetDeviceType;
	QString m_broadCastIP;
	quint16 m_targetPort;
};

class LBL_TaskEngine_IntegratedCtrlCOMTask : public LBL_TaskEngine_IntegratedCtrlTask
{
public:
	explicit LBL_TaskEngine_IntegratedCtrlCOMTask(LBLCluster* pCluster, QObject* pSocket, QObject * parent = 0);
	~LBL_TaskEngine_IntegratedCtrlCOMTask();
	void sendHelloPackage() override;
protected:
	quint16 m_tagetDeviceType;
	int deal_current_message_block(const LBLEnginePackage&) override;
};
#endif
