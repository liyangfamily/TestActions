#include "LBLSenderCardCentralCtrl_COM.h"
#include "LBLSenderCardAbstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>


LBL::SC::LBLSenderCardCentralCtrl_COM::LBLSenderCardCentralCtrl_COM(QObject * parent) :
	LBLSenderCardCentralCtrl(parent)
{
	Q_D(LBLSenderCardAbstract);
	d->q_ptr = this;
}

LBL::SC::LBLSenderCardCentralCtrl_COM::LBLSenderCardCentralCtrl_COM(LBLSenderCardAbstractPrivate & dd, QObject * parent) :
	LBLSenderCardCentralCtrl(dd, parent)
{
	Q_D(LBLSenderCardAbstract);
	d->q_ptr = this;
}

LBL::SC::LBLSenderCardCentralCtrl_COM::~LBLSenderCardCentralCtrl_COM()
{

}

quint16 LBL::SC::LBLSenderCardCentralCtrl_COM::writeBrightness(int value, bool sync, int msec)
{
	Q_D(LBLSenderCardAbstract);
	//在此处组好集控的包，直接调用通信层
	d->m_cacheData.brightness = value;
	LBLPackageInteCtrl_SCWriteBrightness pack;
	pack.SetCmdTargetDevice(d->m_targetDeviceType);
	pack.setBrightness(value);
	pack.initByDetectInfo(d->m_parentItemDetectInfo);
	pack.build(0);

	LBLEnginePackage enginePack;
	enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
	enginePack.setData(pack.getDataToSend());

	if (sync)
	{
		LBLEnginePackage recEnginePack;
		LBLClusterProxy::syncSend(enginePack, recEnginePack, msec);
		return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
	}
	else
	{
		return LBLClusterProxy::asyncSend(enginePack) ? LBLPackage::EOR_Success : LBLPackage::EOR_Fail_NoReason;
	}
}

quint16 LBL::SC::LBLSenderCardCentralCtrl_COM::readBrightness(bool sync, int msec)
{
	Q_D(LBLSenderCardAbstract);
	//在此处组好集控的包，直接调用通信层
	LBLPackageInteCtrl_SCReadBrightness pack;
	pack.SetCmdTargetDevice(d->m_targetDeviceType);
	pack.initByDetectInfo(d->m_parentItemDetectInfo);
	pack.build(0);

	LBLEnginePackage enginePack;
	enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
	enginePack.setData(pack.getDataToSend());

	if (sync)
	{
		LBLEnginePackage recEnginePack;
		LBLClusterProxy::syncSend(enginePack, recEnginePack, msec);
		return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
	}
	else
	{
		return LBLClusterProxy::asyncSend(enginePack) ? LBLPackage::EOR_Success : LBLPackage::EOR_Fail_NoReason;
	}
}

void LBL::SC::LBLSenderCardCentralCtrl_COM::registerCallBack()
{
	Q_D(LBLSenderCardAbstract);

	d->m_packageMgr.registerPackage(LBLPackageInteCtrl_SCReadBrightness(),
		std::bind(&LBLSenderCardCentralCtrl_COM::onParseSCReadBrightness, this, std::placeholders::_1));
	d->m_packageMgr.registerPackage(LBLPackageInteCtrl_SCWriteBrightness(),
		std::bind(&LBLSenderCardCentralCtrl_COM::onParseSCWriteBrightness, this, std::placeholders::_1));

	LBLSenderCardCentralCtrl::registerCallBack();
}

quint16 LBL::SC::LBLSenderCardCentralCtrl_COM::onParseSCWriteBrightness(const QByteArray & data)
{
	Q_D(LBLSenderCardAbstract);

	LBLPackageInteCtrl_SCWriteBrightness pack(data);
	quint16 ret = pack.getOperationResult();
	if (ret == LBLPackage::EOR_Success)
	{
		d->m_realData.brightness = d->m_cacheData.brightness;
	}
	return ret;
}

quint16 LBL::SC::LBLSenderCardCentralCtrl_COM::onParseSCReadBrightness(const QByteArray & data)
{
	Q_D(LBLSenderCardAbstract);

	LBLPackageInteCtrl_SCReadBrightness pack(data);
	d->m_realData.brightness = pack.getBrightness();
	return LBLPackage::EOR_Success;
}

