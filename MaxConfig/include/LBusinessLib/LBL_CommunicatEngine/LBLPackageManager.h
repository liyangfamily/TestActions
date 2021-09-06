/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLPACKAGEMANAGER
#define CVTE_H_LBLPACKAGEMANAGER
#pragma once

#include <LBL_CommunicatEngine/LBLInteCtrlPackage>
#include <LBL_CommunicatEngine/LBLFileTransferPackage>

#include <QMap>

class LBL_COMMUNICATENGINE_EXPORT LBLPackageManager
{
public:
	typedef QMap<quint16, std::function<quint16(const QByteArray&)>> CmdMap;
	typedef QMap<quint8, CmdMap> ProtocolMap;
	LBLPackageManager();
	virtual ~LBLPackageManager();

	template <class T>
	bool registerPackage(const T &package, std::function<quint16(const QByteArray&)>cb)
	{
		quint8 protocolNum = package.CmdProtocolNum();
		quint16 cmdNum = package.CmdRetNum();
		ProtocolMap::iterator iProtocolMap = m_maps.find(protocolNum);
		if (iProtocolMap != m_maps.end()) {
			CmdMap::iterator iCmdNumber = iProtocolMap.value().find(cmdNum);
			if (iCmdNumber != iProtocolMap.value().end()) {
				qDebug() << "LBLPackageManager" << 
					QString("registerPackage failed cmd name : %1   cmd number : %2 is existed").arg(protocolNum).arg(QString::number(cmdNum, 16));
				return false;
			}
		}

		/*T *p_t = new T();
		qDebug() << "LBLPackageManager" << QString("registerPackage cmd name : %1   cmd number : %2.").arg(protocolNum).arg(QString::number(cmdNum, 16));
		p_t->setPackageCallBack(cb);*/

		m_maps[protocolNum][cmdNum] = cb;
		return true;
	}

	void unregisterPackage(LBLPackage package);
	void unregisterAll();

	quint16 handle(const LBLPackage &package);
private:
	ProtocolMap m_maps;
};
#endif
