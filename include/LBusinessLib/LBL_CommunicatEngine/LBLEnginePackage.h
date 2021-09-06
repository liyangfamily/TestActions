#ifndef CVTE_H_LBLENGINEPACKAGE
#define CVTE_H_LBLENGINEPACKAGE
#pragma once

#include <LBL_CommunicatEngine/LBLCommunicatEngineGlobal>
#include "LBL_CommunicatEngine/LBLCommunicatEngineDef.h"

#include <QByteArray>
#include <QMetaType>
#include <QObject>
#include <QVariant>
#include <QVector>
#include <QUuid>

enum EPackageRole
{
	EPR_NetAddress = 0,
	EPR_NetPort,
	EPR_COMName,
	//
};

#define DO_BUILDPACKAGE_ASYNC(detectInfo,data) \
    LBLEnginePackage enginePack;\
	enginePack.convertFrom(detectInfo);\
	enginePack.setData(data);\
	return LBLClusterProxy::asyncSend(enginePack);\

class SPackagePrivate;
class LBL_COMMUNICATENGINE_EXPORT LBLEnginePackage
{
public:
	LBLEnginePackage();
	LBLEnginePackage(QObject*, ECommunicatType, EPackageFromType = EPackageFromType::EPFT_Send);
	LBLEnginePackage(const LBLEnginePackage&);
	~LBLEnginePackage();

	ECommunicatType type() const;
	void setType(ECommunicatType value);

	EPackageFromType fromType() const;
	void setFromType(EPackageFromType value);

	QObject* socketObj() const;
	void setSocketObj(QObject *value);

	QUuid exclusiveKey() const;
	void setExClusiveKey(QUuid);

	QByteArray data() const;
	void setData(const QByteArray&);

	QString hostAddress() const;
	void setHostAddres(const QString&);

	quint16 hostPort() const;
	void setHostPort(const quint16&);

	void setNetInfo(const QString&, const quint16&);

	void setComName(QString comName);
	QString comName() const;

	QString hostName() const;

	bool isEmpty() const;

	static QString genHostName(const QString&, const quint16&);
	static QString genHostName(QString comName);

	//从探卡信息中获取目标socket等信息
	bool initByDetectInfo(const SDetectItemInfo*);
	/*QVariant exData(int role) const;
	void setExData(int role, const QVariant &value);*/

	LBLEnginePackage& operator=(const LBLEnginePackage& other);

	//static bool udpPackageCheck(const SPackage &package, QHostAddress &addr, quint16 &port);

private:
	ECommunicatType m_packType = ECommunicatType::ECT_NULL;
	EPackageFromType m_fromType = EPackageFromType::EPFT_NULL;

	QObject* m_socketObj = 0;
	QByteArray m_dataArray;
	//NET
	QString m_hostAddress;
	quint16 m_hostPort = 0;
	//COM
	QString m_comName;

	//独占模式金钥匙
	QUuid m_exclusiveKey;
};
Q_DECLARE_METATYPE(LBLEnginePackage);
#endif
