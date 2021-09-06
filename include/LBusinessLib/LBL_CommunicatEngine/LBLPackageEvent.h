/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLPACKAGEEVENT
#define CVTE_H_LBLPACKAGEEVENT
#pragma once

#include <LBL_CommunicatEngine/LBLEnginePackage>
#include <QEvent>

class LBL_COMMUNICATENGINE_EXPORT LBLPackageEvent : public QEvent
{
public:
	LBLPackageEvent(QEvent::Type type) :QEvent(type)
	{
	}

	LBLPackageEvent(QEvent::Type type, quint8 protocolNum, quint16 cmdNum) :
		QEvent(type), m_protocolNum(protocolNum), m_cmdNum(cmdNum)
	{
	}
	~LBLPackageEvent()
	{
	}

	void setPackage(const LBLEnginePackage &msg)
	{
		m_package = msg; 
	}

	const LBLEnginePackage & package()const
	{
		return m_package;
	}

	quint8 protocolNum() {
		return m_protocolNum;
	}

	quint16 cmdNum(){
		return m_cmdNum;
	}

	void setSourceDevice(quint16 value)
	{
		m_sourceDevice = value;
	}

	quint16 sourceDevice() {
		return m_sourceDevice;
	}

	//注册两个事件类型
	static QEvent::Type s_disPatcherPackage_eventType;
	static QEvent::Type s_transitPackage_eventType;

private:
	LBLEnginePackage m_package;
	quint8 m_protocolNum = 0;
	quint16 m_cmdNum = 0;
	quint16 m_sourceDevice = 0;
};
#endif
