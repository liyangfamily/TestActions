#include "LBL_SenderCardItem/LBLAbstractSCItem.h"
#include "LBL_SCItem_Abstract_p.h"
namespace LBL
{
	namespace SCItem
	{
		LBLAbstractSCItem::LBLAbstractSCItem(QObject* parent/* = 0*/) 
			:QObject(parent),d_ptr(new LBLAbstractSCItemPrivate)
		{
			Q_D(LBLAbstractSCItem);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
			gDispatcher->registerTransitObject(this);
		}

		LBLAbstractSCItem::LBLAbstractSCItem(LBLAbstractSCItemPrivate & dd, QObject* parent/* = 0*/) :
			QObject(parent),d_ptr(&dd)
		{
			Q_D(LBLAbstractSCItem);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
			gDispatcher->registerTransitObject(this);
		}

		LBLAbstractSCItem::~LBLAbstractSCItem()
		{
			qDebug() << __FUNCTION__;
			gDispatcher->unregisterTransitObject(this);
		}

		bool LBLAbstractSCItem::setDetectInfoStruct(const SDetectItemInfo *detectInfo)
		{
			d_ptr->m_detectInfo = *detectInfo;
            return true;
        }

        bool LBLAbstractSCItem::isUsing()
        {
            return d_ptr->m_isUsing;
        }

		QUuid LBLAbstractSCItem::internalUuid()
		{
			return d_ptr->itemID;
		}

		EDeviceDetectType LBLAbstractSCItem::detectType() const
		{
			return d_ptr->m_detectInfo.detectType;
		}

		ECommunicatType LBLAbstractSCItem::communType() const
		{
			return d_ptr->m_detectInfo.communType;
		}

		void LBLAbstractSCItem::setSenderCardStatus(ESenderCardStatus status)
		{
            d_ptr->m_detectInfo.senderCardStatus = status;
        }

        void LBLAbstractSCItem::setUsing(bool bUsing)
        {
             d_ptr->m_isUsing = bUsing;
        }

		ESenderCardStatus LBLAbstractSCItem::senderCardStatus() const
		{
			return d_ptr->m_detectInfo.senderCardStatus;
		}

		ESenderCardClass LBLAbstractSCItem::senderCardClass() const
		{
			return d_ptr->m_detectInfo.senderCardClass;
		}

		EProductType LBLAbstractSCItem::productType() const
		{
			return d_ptr->m_detectInfo.productType;
		}

		SNetInfo LBLAbstractSCItem::netInfo() const
		{
			return d_ptr->m_detectInfo.netInfo;
		}

		SComInfo LBLAbstractSCItem::comInfo() const
		{
			return d_ptr->m_detectInfo.comInfo;
		}

		QObject * LBLAbstractSCItem::socketObject() const
		{
			return d_ptr->m_detectInfo.socketObj;
		}

		QString LBLAbstractSCItem::hostName() const
		{
			return d_ptr->m_detectInfo.hostName;
		}

		quint8 LBLAbstractSCItem::itemUuidType() const
		{
			return d_ptr->m_detectInfo.uuidType;
		}

		QUuid LBLAbstractSCItem::itemUuid() const
		{
			return d_ptr->m_detectInfo.uuid;
		}

		quint8 LBLAbstractSCItem::senderCardIndex() const
		{
			return d_ptr->m_detectInfo.senderCardIndex;
		}

		QString LBLAbstractSCItem::senderCardTag() const
		{
			return QString();
		}

		void LBLAbstractSCItem::checkItemInfo()
		{
			if (d_ptr->m_SenderCardCtrl) {
				d_ptr->m_SenderCardCtrl->checkItemUuid();
			}
			if (d_ptr->m_AndroidCtrl) {
				if (d_ptr->m_AndroidCtrl->getDeviceName().isEmpty()) {
					d_ptr->m_AndroidCtrl->readDeviceName(false, 100);
				}
			}
		}

		quint16 LBLAbstractSCItem::writeBrightness(int value, bool sync, int msec)
		{
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readBrightness(bool sync, int msec)
        {
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		int LBLAbstractSCItem::getBrightness()
		{
			return 0;
		}


		bool LBLAbstractSCItem::event(QEvent * e)
		{
			if (e->type() == LBLPackageEvent::s_transitPackage_eventType)
			{
				LBLPackageEvent *tempE = static_cast<LBLPackageEvent*>(e);
				dispatcherPackage(tempE->package());
			}
			return QObject::event(e);
		}

		const SDetectItemInfo & LBLAbstractSCItem::getDetectInfoStruct()
		{
			return d_ptr->m_detectInfo;
		}


		bool LBLAbstractSCItem::dispatcherPackage(const LBLEnginePackage& pack)
		{
            Q_UNUSED(pack)
			qDebug() << "LBLAbstractSCItem::you need to implement dispatcherPackage() into Subclass.";
			return false;
		}


		bool LBLAbstractSCItem::isUpgradeSend()
		{
			if (!d_ptr->m_FileTransfer)
				return false;
			return d_ptr->m_FileTransfer->isUpgradeSend();
		}

		quint16 LBLAbstractSCItem::upgradingFileType()
		{
			if (!d_ptr->m_FileTransfer)
				return false;
			return d_ptr->m_FileTransfer->upgradingFileType();
		}

		quint8 LBLAbstractSCItem::upgradingPortIndex()
		{
			if (!d_ptr->m_FileTransfer)
				return false;
			return d_ptr->m_FileTransfer->upgradingPortIndex();
		}

		quint16 LBLAbstractSCItem::upgradingModuleIndex()
		{
			if (!d_ptr->m_FileTransfer)
				return false;
			return d_ptr->m_FileTransfer->upgradingModuleIndex();
		}

		bool LBLAbstractSCItem::isUpgradeStarted()
		{
			if (!d_ptr->m_FileTransfer)
				return false;
			return d_ptr->m_FileTransfer->isUpgradeStarted();
		}

		bool LBLAbstractSCItem::isUpgrading()
		{
			if (!d_ptr->m_FileTransfer)
				return false;
			return d_ptr->m_FileTransfer->isUpgrading();
		}

		bool LBLAbstractSCItem::isUpgradeFinished()
		{
			if (!d_ptr->m_FileTransfer)
				return false;
			return d_ptr->m_FileTransfer->isUpgradeFinished();
		}

		bool LBLAbstractSCItem::cancelUpgrade()
		{
			if (!d_ptr->m_FileTransfer)
				return false;
			return d_ptr->m_FileTransfer->cancelUpgrade();
		}

		quint16 LBLAbstractSCItem::upgradeResult()
		{
			if (!d_ptr->m_FileTransfer)
				return LAPI::EResult::ER_NotSupportThisCommand;
			return d_ptr->m_FileTransfer->upgradeResult();
		}

		QFuture<quint16> LBLAbstractSCItem::upgradeFuture()
		{
			if (!d_ptr->m_FileTransfer)
				return QFuture<quint16>();
			return d_ptr->m_FileTransfer->upgradeFuture();
		}

		quint16 LBLAbstractSCItem::upgradeFile(bool sync, int msec, quint16 fileType, QString fileName)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(fileName)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::upgradeFile(bool sync, int msec, quint16 fileType, QString fileName, quint8 portIndex, quint16 moduleIndex)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(fileName)
            Q_UNUSED(portIndex)
            Q_UNUSED(moduleIndex)
            return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::upgradeFile(bool sync, int msec, quint16 fileType, QByteArray data)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(data)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::upgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(data)
            Q_UNUSED(portIndex)
            Q_UNUSED(moduleIndex)
            return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::requestFile(bool sync, int msec, quint16 fileType, QString fileName)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(fileName)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::requestFile(bool sync, int msec, quint16 fileType, QByteArray & data)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(data)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readAndroidVersion(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QString LBLAbstractSCItem::getAndroidVersion()
		{
			return QString();
		}

		quint16 LBLAbstractSCItem::writeKeyEvent(quint8 status, quint16 keyCode, bool sync, int msec)
		{
			Q_UNUSED(status)
			Q_UNUSED(keyCode)
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getKeyEvent_Result()
		{
			return quint16();
		}

		quint16 LBLAbstractSCItem::writeDeviceName(QString name, bool sync, int msec)
		{
			Q_UNUSED(name)
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readDeviceName(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QString LBLAbstractSCItem::getDeviceName()
		{
			return QString();
		}

		quint16 LBLAbstractSCItem::readNetDeviceOnlineStatus(QString ip, bool sync, int msec)
		{
			Q_UNUSED(ip)
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getNetDevice_Status()
		{
			return quint16();
		}

		QString LBLAbstractSCItem::getNetDevice_IP()
		{
			return QString();
		}

		quint16 LBLAbstractSCItem::readSCEthLoopTestResult(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getSCEthLoopTest_Result()
		{
			return quint16();
		}

		quint8 LBLAbstractSCItem::getSCEthLoopTest_EffectiveEthCount()
		{
			return quint8();
		}

		QByteArray LBLAbstractSCItem::getSCEthLoopTest_ReplyData()
		{
			return QByteArray();
		}

		QMap<quint8, float> LBLAbstractSCItem::getSCEthLoopTest_BitErrRate()
		{
			return QMap<quint8, float>();
		}

		quint16 LBLAbstractSCItem::readUDiskMountingStatus(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getUDiskMounting_Count()
		{
			return quint8();
		}

		QStringList LBLAbstractSCItem::getUDiskMounting_List()
		{
			return QStringList();
		}

		quint16 LBLAbstractSCItem::writeStartOSDTest(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getOSDTest_WhiteScreenTestResult()
		{
			return quint8();
		}

		quint8 LBLAbstractSCItem::getOSDTest_BlackScreenTestResult()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeRelaySwitc(quint8 status, bool sync, int msec)
		{
			Q_UNUSED(status)
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getRelaySwitc_Result()
		{
			return quint16();
		}

		quint8 LBLAbstractSCItem::getRelaySwitc_Status()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeEnterKeyTest(quint8 status, bool sync, int msec)
		{
			Q_UNUSED(status)
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getKeyTest_Result()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::readKeyTestResult(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getKeyTestResult_Count()
		{
			return quint8();
		}

		QList<quint16> LBLAbstractSCItem::getKeyTestResult_List()
		{
			return QList<quint16>();
		}

		quint16 LBLAbstractSCItem::readOpticalSensorParam(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getOpticalSensor_Param()
		{
			return quint16();
		}

		quint16 LBLAbstractSCItem::readRouterStatus(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getRouter_5GWifiStatus()
		{
			return quint8();
		}

		quint8 LBLAbstractSCItem::getRouter_2_4GWifiStatus()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync, int msec)
		{
			Q_UNUSED(flage)
			Q_UNUSED(mac)
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getNetworkCardMACAddr_Results()
		{
			return quint16();
		}

		quint8 LBLAbstractSCItem::getNetworkCardMACAddr_Flage()
		{
			return quint8();
		}

		QByteArray LBLAbstractSCItem::getNetworkCardMACAddr_MAC()
		{
			return QByteArray();
		}

		quint16 LBLAbstractSCItem::writePlayTestSound_1KHZ(quint8 status, bool sync, int msec)
		{
			Q_UNUSED(status)
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getPlayTestSound_Results()
		{
			return quint16();
		}

		quint8 LBLAbstractSCItem::getPlayTestSound_Status()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeWIFIModuleScanTest(quint8 status, bool sync, int msec)
		{
			Q_UNUSED(status)
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getWIFIModuleScanTest_Results()
		{
			return quint16();
		}

		quint16 LBLAbstractSCItem::readWIFIScanList(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getWIFIScanList_Count()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::readLoadPowerAmplifierChipParam(bool sync, int msec)
		{
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getPowerAmplifierChipParam_Results()
		{
			return quint8();
		}

		quint8 LBLAbstractSCItem::getPowerAmplifierChipParam_30Results()
		{
			return quint8();
		}

		quint8 LBLAbstractSCItem::getPowerAmplifierChipParam_31Results()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::readCOMLoopTestResult(bool sync, int msec)
		{
			Q_UNUSED(sync)
				Q_UNUSED(msec)
				return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getCOMLoopTest_INResult()
		{
			return quint8();
		}

		quint8 LBLAbstractSCItem::getCOMLoopTest_OUTResult()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeEnterTestMode(QString key, bool sync, int msec)
		{
            Q_UNUSED(key)
			Q_UNUSED(sync)
			Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getEnterTestMode_Results()
		{
			return quint16();
		}

		quint16 LBLAbstractSCItem::writeSCFPGARegister(quint32 addr, QByteArray value, bool sync, int msec)
		{
            Q_UNUSED(addr)
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCFPGARegister(quint32 addr, quint16 len, bool sync, int msec)
		{
            Q_UNUSED(addr)
            Q_UNUSED(len)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return QByteArray();
		}

		QByteArray LBLAbstractSCItem::getSCFPGARegister()
		{
			return QByteArray();
		}

		QByteArray LBLAbstractSCItem::readSCFPGAVersion(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
				return QByteArray();
		}

		QString LBLAbstractSCItem::getSCFPGAVersion()
		{
			return QString();
		}

		quint16 LBLAbstractSCItem::writeSCFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec)
		{
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCFPGAEthLoad(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
				return QByteArray();
		}

		QList<LBLSPort> LBLAbstractSCItem::getSCFPGAEthLoad()
		{
			return QList<LBLSPort>();
		}

		quint16 LBLAbstractSCItem::readMCUAppVersion(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
				return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QString LBLAbstractSCItem::getMCUAppVersion()
		{
			return QString();
		}

		quint16 LBLAbstractSCItem::readMCUBootVersion(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QString LBLAbstractSCItem::getMCUBootVersion()
		{
			return QString();
		}

		quint16 LBLAbstractSCItem::writeSaveSCParam(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::writeSCSelfTestMode(quint8 mode, bool sync, int msec)
		{
			Q_UNUSED(mode);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCSelfTestMode(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSCSelfTestMode()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeSCSelfTestModeSpeed(quint8 speed, bool sync, int msec)
		{
			Q_UNUSED(speed);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCSelfTestModeSpeed(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSCSelfTestModeSpeed()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeSCScreenBlack(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCScreenBlack(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSCScreenBlack()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeSCScreenLock(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCScreenLock(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSCScreenLock()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeSCZoomMode(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCZoomMode(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSCZoomMode()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeSCZoomSize(QSize value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCZoomSize(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		QSize LBLAbstractSCItem::getSCZoomSize()
		{
			return QSize();
		}

		quint16 LBLAbstractSCItem::writeSCErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCErrorBitRateStatisticalSwitch(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSCErrorBitRateStatisticalSwitch()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeSCCorrectionSwitch(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCCorrectionSwitch(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSCCorrectionSwitch()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeSCSpreadSpectrumSwitch(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCSpreadSpectrumSwitch(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSCSpreadSpectrumSwitch()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeSC24BitGammaSwitch(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSC24BitGammaSwitch(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSC24BitGammaSwitch()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeSCProtocolType(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readSCProtocolType(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLAbstractSCItem::getSCProtocolType()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeConnection(LBLConnection* value, bool sync, int msec)
		{
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readConnection(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		LBLConnection* LBLAbstractSCItem::getConnection()
		{
			return &(d_ptr->m_connection);
		}

		quint16 LBLAbstractSCItem::writeRCFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec)
		{
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(addr)
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLAbstractSCItem::readRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec)
		{
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(addr)
            Q_UNUSED(len)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            return QByteArray();
		}

		QByteArray LBLAbstractSCItem::getRCFPGARegister()
		{
            return QByteArray();
        }

        quint16 LBLAbstractSCItem::writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        QByteArray LBLAbstractSCItem::readModuleParam(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            return QByteArray();
        }

        QByteArray LBLAbstractSCItem::getModuleParam()
        {
            return QByteArray();
        }

        quint16 LBLAbstractSCItem::writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        QByteArray LBLAbstractSCItem::readDriveICParam(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            return QByteArray();
        }

        QByteArray LBLAbstractSCItem::getDriveICParam()
        {
             return QByteArray();
        }

        quint16 LBLAbstractSCItem::writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        QByteArray LBLAbstractSCItem::readDecodingICParam(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            return QByteArray();
        }

        QByteArray LBLAbstractSCItem::getDecodingICParam()
        {
            return QByteArray();
        }

        quint16 LBLAbstractSCItem::writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_UNUSED(port)
                Q_UNUSED(module)
                Q_UNUSED(sync)
                Q_UNUSED(msec)
                return LAPI::EResult::ER_NotSupportThisCommand;
        }

		quint16 LBLAbstractSCItem::writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

		QList<RC::SRCStatusInfo> LBLAbstractSCItem::readRCStatusInfo(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QList<RC::SRCStatusInfo>();
		}

		QList<RC::SRCStatusInfo> LBLAbstractSCItem::readRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec)
		{
			Q_UNUSED(portStart);
			Q_UNUSED(portCount);
			Q_UNUSED(moduleStart);
			Q_UNUSED(moduleCount);
			Q_UNUSED(lengthFlag);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QList<RC::SRCStatusInfo>();
		}

		QList<RC::SRCStatusInfo> LBLAbstractSCItem::getRCStatusInfo()
		{
			return QList<RC::SRCStatusInfo>();
		}

		QList<RC::SRCMonitorInfo> LBLAbstractSCItem::readRCMonitorInfo(quint8 portIndex, bool sync, int msec)
		{
			Q_UNUSED(portIndex);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QList<RC::SRCMonitorInfo>();
		}

		QList<RC::SRCMonitorInfo> LBLAbstractSCItem::getRCMonitorInfo()
		{
			return QList<RC::SRCMonitorInfo>();
		}

		quint16 LBLAbstractSCItem::writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec)
        {
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

		quint16 LBLAbstractSCItem::writeHDMIByPassStatus(const quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDMIByPassStatus(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::getHDMIByPassStatus()
		{
			return quint16();
		}

		quint16 LBLAbstractSCItem::writeHDMIImageRatio(const quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDMIImageRatio(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getHDMIImageRatio()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeHDMIInputSource(const quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDMIInputSource(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getHDMIInputSource()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeHDMIImageContrast(const quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDMIImageContrast(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getHDMIImageContrast()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeHDMIImageColorTtemperature(const quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDMIImageColorTtemperature(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getHDMIImageColorTtemperature()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeHDMIImageBrightness(const quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDMIImageBrightness(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getHDMIImageBrightness()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeHDMIRGBGain(const int rValue, const int gValue, const int bValue, bool sync, int msec)
		{
			Q_UNUSED(rValue);
			Q_UNUSED(gValue);
			Q_UNUSED(bValue);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDMIRGBGain(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QList<quint8> LBLAbstractSCItem::getHDMIRGBGain()
		{
            return QList<quint8>();
        }

        quint16 LBLAbstractSCItem::readHDMIInputSignalInfo(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        QString LBLAbstractSCItem::getHDMIInputSignalInfo()
        {
            return QString();
        }

		quint16 LBLAbstractSCItem::readHDMIVersion(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QString LBLAbstractSCItem::getHDMIVersion()
		{
			return QString();
		}

		quint16 LBLAbstractSCItem::writeHDMIMultiScreenMode(const quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDMIMultiScreenMode(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLAbstractSCItem::getHDMIMultiScreenMode()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeHDMIMultiScreenInputSource(const quint8 param, const quint8 channel, bool sync, int msec)
		{
			Q_UNUSED(param);
			Q_UNUSED(channel);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::writeHDMIMultiScreenInputSourceList(const QList<quint8>& values, bool sync, int msec)
		{
			Q_UNUSED(values);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDMIMultiScreenInputSource(const quint8 channel, bool sync, int msec)
		{
			Q_UNUSED(channel);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QList<quint8> LBLAbstractSCItem::getHDMIMultiScreenInputSource(const quint8 channel)
		{
			Q_UNUSED(channel);
			return QList<quint8>();
		}

		quint16 LBLAbstractSCItem::resetHDMISetting(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::writeHDIMIWindowSize(QSize value, quint8 channel, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(channel);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDIMIWindowSize(quint8 channel, bool sync, int msec)
		{
			Q_UNUSED(channel);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QSize LBLAbstractSCItem::getHDIMIWindowSize()
		{
			return QSize();
		}

		quint16 LBLAbstractSCItem::writeHDIMIWindowPos(QPoint value, quint8 channel, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(channel);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLAbstractSCItem::readHDIMIWindowPos(quint8 channel, bool sync, int msec)
		{
			Q_UNUSED(channel);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QPoint LBLAbstractSCItem::getHDIMIWindowPos()
		{
			return QPoint();
		}

		quint16 LBLAbstractSCItem::writeHDIMIWindowStatus(quint8 status, quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(status);
            Q_UNUSED(channel);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
			return quint16();
		}

		quint16 LBLAbstractSCItem::readHDIMIWindowStatus(quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(channel);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
			return quint16();
		}

		quint8 LBLAbstractSCItem::getHDIMIWindowStatus()
		{
			return quint8();
		}

		quint16 LBLAbstractSCItem::writeHDIMIAudioSrc(quint8 param, quint8 channel, bool sync, int msec)
		{
            Q_UNUSED(param);
            Q_UNUSED(channel);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
			return quint16();
		}

		quint16 LBLAbstractSCItem::readHDIMIAudioSrc(quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(channel);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
			return quint16();
		}

		quint8 LBLAbstractSCItem::getHDIMIAudioSrc()
		{
			return quint8();
		}

}
}
