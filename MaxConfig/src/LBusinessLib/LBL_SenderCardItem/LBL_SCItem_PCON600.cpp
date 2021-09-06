#include "LBL_SCItem_PCON600.h"
#include "LBL_SCItem_PCON600_p.h"
#define LBL_TAG_SENDERCARDPCON600 "SenderCard_PCON600"
namespace LBL
{
	namespace SCItem
	{

		SenderCardItem_PCON600::SenderCardItem_PCON600(QObject* parent/* = 0*/):
			LBLAbstractSCItem(*new SenderCardItem_PCON600Private(), parent)
		{
			Q_D(SenderCardItem_PCON600);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}


		SenderCardItem_PCON600::SenderCardItem_PCON600(SenderCardItem_PCON600Private& dd, QObject* parent) :
			LBLAbstractSCItem(dd, parent)
		{
			Q_D(SenderCardItem_PCON600);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		SenderCardItem_PCON600::~SenderCardItem_PCON600()
		{
			qDebug() << __FUNCTION__;
		}

		QString SenderCardItem_PCON600::senderCardTag() const
		{
			return LBL_TAG_SENDERCARDPCON600;
		}

		quint16 SenderCardItem_PCON600::writeBrightness(int value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeBrightness(value, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readBrightness(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readBrightness(sync, msec);
		}

		int SenderCardItem_PCON600::getBrightness()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getBrightness();
		}

		quint16 SenderCardItem_PCON600::writeSCFPGARegister(quint32 addr, QByteArray value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeFPGARegister(addr, value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCFPGARegister(quint32 addr, quint16 len, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readFPGARegister(addr, len, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::getSCFPGARegister()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getFPGARegister();
		}

		QByteArray SenderCardItem_PCON600::readSCFPGAVersion(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readFPGAVersion(sync, msec);
		}

		QString SenderCardItem_PCON600::getSCFPGAVersion()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getFPGAVersion();
		}

		quint16 SenderCardItem_PCON600::writeSCFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeFPGAEthLoad(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCFPGAEthLoad(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readFPGAEthLoad(sync, msec);
		}

		QList<LBLSPort> SenderCardItem_PCON600::getSCFPGAEthLoad()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getFPGAEthLoad();
		}

		quint16 SenderCardItem_PCON600::writeSaveSCParam(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeSaveSCParam(sync, msec);
		}

		quint16 SenderCardItem_PCON600::writeSCSelfTestMode(quint8 mode, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeSelfTestMode(mode, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCSelfTestMode(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readSelfTestMode(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSCSelfTestMode()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getSelfTestMode();
		}

		quint16 SenderCardItem_PCON600::writeSCSelfTestModeSpeed(quint8 speed, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeSelfTestModeSpeed(speed, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCSelfTestModeSpeed(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readSelfTestModeSpeed(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSCSelfTestModeSpeed()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getSelfTestModeSpeed();
		}

		quint16 SenderCardItem_PCON600::writeSCScreenBlack(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeScreenBlack(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCScreenBlack(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readScreenBlack(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSCScreenBlack()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getScreenBlack();
		}

		quint16 SenderCardItem_PCON600::writeSCScreenLock(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeScreenLock(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCScreenLock(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readScreenLock(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSCScreenLock()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getScreenLock();
		}

		quint16 SenderCardItem_PCON600::writeSCZoomMode(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeZoomMode(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCZoomMode(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readZoomMode(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSCZoomMode()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getZoomMode();
		}

		quint16 SenderCardItem_PCON600::writeSCZoomSize(QSize value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeZoomSize(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCZoomSize(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readZoomSize(sync, msec);
		}

		QSize SenderCardItem_PCON600::getSCZoomSize()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getZoomSize();
		}

		quint16 SenderCardItem_PCON600::writeSCErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeErrorBitRateStatisticalSwitch(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCErrorBitRateStatisticalSwitch(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readErrorBitRateStatisticalSwitch(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSCErrorBitRateStatisticalSwitch()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getErrorBitRateStatisticalSwitch();
		}

		quint16 SenderCardItem_PCON600::writeSCCorrectionSwitch(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeCorrectionSwitch(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCCorrectionSwitch(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readCorrectionSwitch(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSCCorrectionSwitch()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getCorrectionSwitch();
		}

		quint16 SenderCardItem_PCON600::writeSCSpreadSpectrumSwitch(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeSpreadSpectrumSwitch(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCSpreadSpectrumSwitch(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readSpreadSpectrumSwitch(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSCSpreadSpectrumSwitch()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getSpreadSpectrumSwitch();
		}

		quint16 SenderCardItem_PCON600::writeSC24BitGammaSwitch(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->write24BitGammaSwitch(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSC24BitGammaSwitch(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->read24BitGammaSwitch(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSC24BitGammaSwitch()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->get24BitGammaSwitch();
		}


		quint16 SenderCardItem_PCON600::writeSCProtocolType(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->writeProtocolType(value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readSCProtocolType(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->readProtocolType(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getSCProtocolType()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getProtocolType();
		}

		quint16 SenderCardItem_PCON600::writeConnection(LBLConnection * value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (!value) {
				return LAPI::EResult::ER_InDataNullptr;
			}
			quint16 ret = writeSCFPGAEthLoad(value->getPortList(), sync, msec);
			if (ret != LAPI::EResult::ER_INTECTRL_Success) {
				return ret;
			}
			ret = upgradeFile(sync, msec, LBLFileTransferPackage::EFileType::EFT_ConnectionFile, (*value).buildConnectionDataV0());
			if (ret != LAPI::EResult::ER_INTECTRL_Success) {
				return ret;
			}
			return d->m_SenderCardCtrl->sendConnectionBuffer(sync, 1500);
		}

		quint16 SenderCardItem_PCON600::readConnection(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (readSCFPGAEthLoad(sync, 1500).isEmpty()) {
				return LAPI::EResult::ER_CONNECT_NetPortLoadingAreaNotRead;
			}
			QByteArray connectionData;
			quint16 ret = d->m_SenderCardCtrl->readConnectionBuffer(sync, msec);
			if (ret != LAPI::EResult::ER_INTECTRL_Success) {
				return ret;
			}
			ret = d->m_connection.parseConnectionData(d->m_SenderCardCtrl->getConnectionBuffer());
			if (ret != LAPI::EResult::ER_Success) {
				return ret;
			}
			
			ret = d->m_connection.checkPortLoadArea(getSCFPGAEthLoad());
			if (ret != LAPI::EResult::ER_Success) {
				return ret;
			}
			return LAPI::EResult::ER_Success;
		}


		quint16 SenderCardItem_PCON600::writeRCFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_ReceiveCardCtrl->writeFPGARegister(port, module, addr, value, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::readRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_ReceiveCardCtrl->readFPGARegister(port, module, addr, len, sync, msec);
		}

		QByteArray SenderCardItem_PCON600::getRCFPGARegister()
		{
			Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->getFPGARegister();
        }

        quint16 SenderCardItem_PCON600::writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->writeModuleParam(port, module, value, sync, msec);
        }

        QByteArray SenderCardItem_PCON600::readModuleParam(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->readModuleParam(port, module, sync, msec);
        }

        QByteArray SenderCardItem_PCON600::getModuleParam()
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->getModuleParam();
        }

        quint16 SenderCardItem_PCON600::writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->writeDriveICParam(port, module, value, sync, msec);
        }

        QByteArray SenderCardItem_PCON600::readDriveICParam(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->readDriveICParam(port, module, sync, msec);
        }

        QByteArray SenderCardItem_PCON600::getDriveICParam()
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->getDriveICParam();
        }

        quint16 SenderCardItem_PCON600::writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->writeDecodingICParam(port, module, value, sync, msec);
        }

        QByteArray SenderCardItem_PCON600::readDecodingICParam(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->readDecodingICParam(port, module, sync, msec);
        }

        QByteArray SenderCardItem_PCON600::getDecodingICParam()
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->getDecodingICParam();
        }

        quint16 SenderCardItem_PCON600::writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->writeCalibrationDataErase(port, module, sync, msec);
        }

		quint16 SenderCardItem_PCON600::writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_ReceiveCardCtrl->writeCalibrationDataSave(port, module, sync, msec);
		}

		quint16 SenderCardItem_PCON600::writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->writeCalibrationDataReload(port, module, sync, msec);
        }

		QList<RC::SRCStatusInfo> SenderCardItem_PCON600::readRCStatusInfo(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			d->m_allRCStatusInfo.clear();
			for (auto port : d->m_connection.getPortList()) {
				for (auto module : port.getAllModuleMap()) {
					QList<RC::SRCStatusInfo> rcInfo = readRCStatusInfo(port.index(), 1, module.index(), 1, 0x03, sync, msec);
					if (rcInfo.isEmpty()) {
						break;
					}
					else {
						if (!rcInfo.at(0).IsVaild()) {
							break;
						}
					}
					d->m_allRCStatusInfo.append(rcInfo);
				}
			}
			return d->m_allRCStatusInfo;
		}

		QList<RC::SRCStatusInfo> SenderCardItem_PCON600::readRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec)
		{
            Q_UNUSED(lengthFlag)
			Q_D(SenderCardItem_PCON600);
			QList<RC::SRCStatusInfo> defaultList;
			quint16 ret = d->m_ReceiveCardCtrl->readStatusInfo(portStart, portCount, moduleStart, moduleCount, 0x03, sync, msec);
			if (LAPI::EResult::ER_INTECTRL_Success == ret) {
				return d->m_ReceiveCardCtrl->getStatusInfo();
			}
			return defaultList;
		}

		QList<RC::SRCStatusInfo> SenderCardItem_PCON600::getRCStatusInfo()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_ReceiveCardCtrl->getStatusInfo();
		}

		QList<RC::SRCMonitorInfo> SenderCardItem_PCON600::readRCMonitorInfo(quint8 portIndex, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			QList<RC::SRCMonitorInfo> defaultList;
			for (int i = 0; i < LBL_Max_UsingSenderCardPort; ++i)
			{
				if (portIndex != 0xFF) {
					if (i != portIndex) {
						continue;
					}
				}
				quint16 ret = d->m_ReceiveCardCtrl->readMonitorInfo(i, sync, msec);
				if (LAPI::EResult::ER_INTECTRL_Success == ret) {
					defaultList.append(d->m_ReceiveCardCtrl->getMonitorInfo());
				}
				if (portIndex != 0xFF) {
					break;
				}
			}
			return defaultList;
		}

		QList<RC::SRCMonitorInfo> SenderCardItem_PCON600::getRCMonitorInfo()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_ReceiveCardCtrl->getMonitorInfo();
		}

        quint16 SenderCardItem_PCON600::writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_PCON600);
            return d->m_ReceiveCardCtrl->writeSaveRCParamByRegister(port, module, sync, msec);
        }

		quint16 SenderCardItem_PCON600::writeHDMIByPassStatus(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->writeSetting_ByPass(value, 0, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDMIByPassStatus(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->readSetting_ByPass(0, sync, msec);
		}

		quint16 SenderCardItem_PCON600::getHDMIByPassStatus()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->getSetting_ByPass();
		}

		quint16 SenderCardItem_PCON600::writeHDMIImageRatio(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->writeRatio(value, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDMIImageRatio(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->readRatio(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getHDMIImageRatio()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->getRatio();
		}

		quint16 SenderCardItem_PCON600::writeHDMIInputSource(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->writeSource(value, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDMIInputSource(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->readSource(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getHDMIInputSource()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->getSource();
		}

		quint16 SenderCardItem_PCON600::writeHDMIImageContrast(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->writeContrast(value, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDMIImageContrast(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->readContrast(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getHDMIImageContrast()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->getContrast();
		}

		quint16 SenderCardItem_PCON600::writeHDMIImageColorTtemperature(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->writeColortemperature(value, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDMIImageColorTtemperature(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->readColortemperature(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getHDMIImageColorTtemperature()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->getColortemperature();
		}

		quint16 SenderCardItem_PCON600::writeHDMIImageBrightness(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->writeBrightness(value, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDMIImageBrightness(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->readBrightness(sync, msec);
		}

		quint8 SenderCardItem_PCON600::getHDMIImageBrightness()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->getBrightness();
		}

		quint16 SenderCardItem_PCON600::writeHDMIRGBGain(const int rValue, const int gValue, const int bValue, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			quint16 ret;
			if (-3 == rValue + gValue + bValue) {
				ret = d->m_HDMIChip->writeRGBGain(rValue, gValue, bValue, sync, msec);
			}
			if (-1 != rValue) {
				ret = d->m_HDMIChip->writeRGain(rValue, sync, msec);
			}
			if (-1 != gValue) {
				ret = d->m_HDMIChip->writeGGain(gValue, sync, msec);
			}
			if (-1 != bValue) {
				ret = d->m_HDMIChip->writeBGain(bValue, sync, msec);
			}
			return ret;
		}

		quint16 SenderCardItem_PCON600::readHDMIRGBGain(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->readRGBGain(sync, msec);
		}

		QList<quint8> SenderCardItem_PCON600::getHDMIRGBGain()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_HDMIChip->getRGBGain();
		}

		quint16 SenderCardItem_PCON600::readHDMIInputSignalInfo(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->readSignal_InputSignalInfo(0, sync, msec);
		}

		QString SenderCardItem_PCON600::getHDMIInputSignalInfo()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->getSignal_InputSignalInfo();
		}

		quint16 SenderCardItem_PCON600::readHDMIVersion(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->readSys_Version(0, sync, msec);
		}

		QString SenderCardItem_PCON600::getHDMIVersion()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->getSys_Version();
		}

		quint16 SenderCardItem_PCON600::writeHDMIMultiScreenMode(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->writeDP_PIPorPBP(value, 0, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDMIMultiScreenMode(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->readDP_PIPorPBP(0, sync, msec);
		}

		quint8 SenderCardItem_PCON600::getHDMIMultiScreenMode()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->getDP_PIPorPBP();
		}

		quint16 SenderCardItem_PCON600::writeHDMIMultiScreenInputSource(const quint8 param, const quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->writeDP_MainorPIPInput(param, param, param, param, channel, sync, msec);
		}

		quint16 SenderCardItem_PCON600::writeHDMIMultiScreenInputSourceList(const QList<quint8>& values, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (values.size() != d->m_NT68400Ctrl->channelCount()) {
				return LAPI::ER_InDataError;
			}
			return d->m_NT68400Ctrl->writeDP_MainorPIPInput(values.at(0), values.at(1), values.at(2), values.at(3), 0, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDMIMultiScreenInputSource(const quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->readDP_MainorPIPInput(channel, sync, msec);
		}
		
		quint16 SenderCardItem_PCON600::resetHDMISetting(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->resetHDMISetting(sync, msec);
		}

		quint16 SenderCardItem_PCON600::writeHDIMIWindowSize(QSize value, quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->writeDP_WindowSize(value.width(), value.height(), channel, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDIMIWindowSize(quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->readDP_WindowSize(channel, sync, msec);
		}

		QSize SenderCardItem_PCON600::getHDIMIWindowSize()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->getDP_WindowSize();
		}

		quint16 SenderCardItem_PCON600::writeHDIMIWindowPos(QPoint value, quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->writeDP_WindowPos(value.x(), value.y(), channel, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDIMIWindowPos(quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->readDP_WindowPos(channel, sync, msec);
		}

		QPoint SenderCardItem_PCON600::getHDIMIWindowPos()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->getDP_WindowPos();
		}

		quint16 SenderCardItem_PCON600::writeHDIMIWindowStatus(quint8 status, quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->writeDP_PIPWindowStatus(status, channel, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDIMIWindowStatus(quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->readDP_PIPWindowStatus(channel, sync, msec);
		}

		quint8 SenderCardItem_PCON600::getHDIMIWindowStatus()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->getDP_PIPWindowStatus();
		}

		quint16 SenderCardItem_PCON600::writeHDIMIAudioSrc(quint8 param, quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->writeSetting_AudioSrc(param, channel, sync, msec);
		}

		quint16 SenderCardItem_PCON600::readHDIMIAudioSrc(quint8 channel, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->readSetting_AudioSrc(channel, sync, msec);
		}

		quint8 SenderCardItem_PCON600::getHDIMIAudioSrc()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_NT68400Ctrl->getSetting_AudioSrc();
		}

		QList<quint8> SenderCardItem_PCON600::getHDMIMultiScreenInputSource(const quint8 channel)
		{
			Q_D(SenderCardItem_PCON600);
			if (!channel) {
				return d->m_NT68400Ctrl->getDP_MainorPIPInputList();
			}
			else {
				if (channel > d->m_NT68400Ctrl->getDP_MainorPIPInputList().size()) {
					return QList<quint8>();
				}
				else {
					return QList<quint8>() << d->m_NT68400Ctrl->getDP_MainorPIPInputList().at(channel-1);
				}
			}
		}

		quint16 SenderCardItem_PCON600::upgradeFile(bool sync, int msec, quint16 fileType, QString fileName)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_FileTransfer->common_UpgradeFile(sync, msec, fileType, fileName);
		}

		quint16 SenderCardItem_PCON600::upgradeFile(bool sync, int msec, quint16 fileType, QByteArray data)
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_FileTransfer->common_UpgradeFile(sync, msec, fileType, data);
		}

		quint16 SenderCardItem_PCON600::requestFile(bool sync, int msec, quint16 fileType, QString fileName)
		{
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            Q_UNUSED(fileType);
            Q_UNUSED(fileName);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 SenderCardItem_PCON600::requestFile(bool sync, int msec, quint16 fileType, QByteArray & data)
		{
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            Q_UNUSED(fileType);
            Q_UNUSED(data);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 SenderCardItem_PCON600::readAndroidVersion(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readAndroidVersion(sync, msec);
			}
			else {
				return LAPI::EResult::ER_NotSupportThisCommand;
			}
		}

		QString SenderCardItem_PCON600::getAndroidVersion()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getAndroidVersion();
			}
			else {
				return QString();
			}
			
		}

		quint16 SenderCardItem_PCON600::writeKeyEvent(quint8 status, quint16 keyCode, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->writeKeyEvent(status, keyCode, sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::getKeyEvent_Result()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getKeyEvent_Result();
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::writeDeviceName(QString name, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->writeDeviceName(name, sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::readDeviceName(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readDeviceName(sync, msec);
			}
			else {
				return quint16();
			}
		}

		QString SenderCardItem_PCON600::getDeviceName()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getDeviceName();
			}
			else {
				return QString();
			}
		}

		quint16 SenderCardItem_PCON600::readNetDeviceOnlineStatus(QString ip, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readNetDeviceOnlineStatus(ip, sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::getNetDevice_Status()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getNetDevice_Status();
			}
			else {
				return quint16();
			}
		}

		QString SenderCardItem_PCON600::getNetDevice_IP()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getNetDevice_IP();
			}
			else {
				return QString();
			}
		}

		quint16 SenderCardItem_PCON600::readSCEthLoopTestResult(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			/*if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readSCEthLoopTestResult(sync, msec);
			}
			else {
				return quint16();
			}*/
			d->m_SenderCardCtrl->readEthLoopTest(sync, msec);
			return LAPI::EResult::ER_INTECTRL_Success;
		}

		quint16 SenderCardItem_PCON600::getSCEthLoopTest_Result()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getSCEthLoopTest_Result();
			}
			else {
				return quint16();
			}
			return quint16();
		}

		quint8 SenderCardItem_PCON600::getSCEthLoopTest_EffectiveEthCount()
		{
			Q_D(SenderCardItem_PCON600);
			/*if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getSCEthLoopTest_EffectiveEthCount();
			}
			else {
				return quint8();
			}*/
			return d->m_SenderCardCtrl->getEthLoopTest_Count();
		}

		QByteArray SenderCardItem_PCON600::getSCEthLoopTest_ReplyData()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getSCEthLoopTest_ReplyData();
			}
			else {
				return QByteArray();
			}
		}

		QMap<quint8, float> SenderCardItem_PCON600::getSCEthLoopTest_BitErrRate()
		{
			Q_D(SenderCardItem_PCON600);
			return d->m_SenderCardCtrl->getEthLoopTest_BitErrRate();
		}

		quint16 SenderCardItem_PCON600::readUDiskMountingStatus(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readUDiskMountingStatus(sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getUDiskMounting_Count()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getUDiskMounting_Count();
			}
			else {
				return quint8();
			}
		}

		QStringList SenderCardItem_PCON600::getUDiskMounting_List()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getUDiskMounting_List();
			}
			else {
				return QStringList();
			}
		}

		quint16 SenderCardItem_PCON600::writeStartOSDTest(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->writeStartOSDTest(sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getOSDTest_WhiteScreenTestResult()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getOSDTest_BlackScreenTestResult();
			}
			else {
				return quint8();
			}
		}

		quint8 SenderCardItem_PCON600::getOSDTest_BlackScreenTestResult()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getOSDTest_BlackScreenTestResult();
			}
			else {
				return quint8();
			}
		}

		quint16 SenderCardItem_PCON600::writeRelaySwitc(quint8 status, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->writeRelaySwitc(status, sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::getRelaySwitc_Result()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getRelaySwitc_Result();
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getRelaySwitc_Status()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getRelaySwitc_Status();
			}
			else {
				return quint8();
			}
		}

		quint16 SenderCardItem_PCON600::writeEnterKeyTest(quint8 status, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->writeEnterKeyTest(status, sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getKeyTest_Result()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getKeyTest_Result();
			}
			else {
				return quint8();
			}
		}

		quint16 SenderCardItem_PCON600::readKeyTestResult(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readKeyTestResult(sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getKeyTestResult_Count()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getKeyTestResult_Count();
			}
			else {
				return quint8();
			}
		}

		QList<quint16> SenderCardItem_PCON600::getKeyTestResult_List()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getKeyTestResult_List();
			}
			else {
				return QList<quint16>();
			}
		}

		quint16 SenderCardItem_PCON600::readOpticalSensorParam(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readOpticalSensorParam(sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::getOpticalSensor_Param()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getOpticalSensor_Param();
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::readRouterStatus(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readRouterStatus(sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getRouter_5GWifiStatus()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getRouter_5GWifiStatus();
			}
			else {
				return quint8();
			}
		}

		quint8 SenderCardItem_PCON600::getRouter_2_4GWifiStatus()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getRouter_2_4GWifiStatus();
			}
			else {
				return quint8();
			}
		}

		quint16 SenderCardItem_PCON600::writeNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->writeNetworkCardMACAddr(flage, mac, sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::getNetworkCardMACAddr_Results()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getNetworkCardMACAddr_Results();
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getNetworkCardMACAddr_Flage()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getNetworkCardMACAddr_Flage();
			}
			else {
				return quint8();
			}
		}

		QByteArray SenderCardItem_PCON600::getNetworkCardMACAddr_MAC()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getNetworkCardMACAddr_MAC();
			}
			else {
				return QByteArray();
			}
		}

		quint16 SenderCardItem_PCON600::writePlayTestSound_1KHZ(quint8 status, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->writePlayTestSound_1KHZ(status, sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::getPlayTestSound_Results()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getPlayTestSound_Results();
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getPlayTestSound_Status()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getPlayTestSound_Status();
			}
			else {
				return quint8();
			}
		}

		quint16 SenderCardItem_PCON600::writeWIFIModuleScanTest(quint8 status, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->writeWIFIModuleScanTest(status, sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::getWIFIModuleScanTest_Results()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getWIFIModuleScanTest_Results();
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::readWIFIScanList(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readWIFIScanList(sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getWIFIScanList_Count()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getWIFIScanList_Count();
			}
			else {
				return quint8();
			}
		}

		quint16 SenderCardItem_PCON600::readLoadPowerAmplifierChipParam(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readLoadPowerAmplifierChipParam(sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint8 SenderCardItem_PCON600::getPowerAmplifierChipParam_Results()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getPowerAmplifierChipParam_Results();
			}
			else {
				return quint8();
			}
		}

		quint8 SenderCardItem_PCON600::getPowerAmplifierChipParam_30Results()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getPowerAmplifierChipParam_30Results();
			}
			else {
				return quint8();
			}
		}

		quint8 SenderCardItem_PCON600::getPowerAmplifierChipParam_31Results()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getPowerAmplifierChipParam_31Results();
			}
			else {
				return quint8();
			}
		}

		quint16 SenderCardItem_PCON600::readCOMLoopTestResult(bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readSCCOMLoopTestResult(sync, msec);
			}
			else {
				return quint8();
			}
		}

		quint8 SenderCardItem_PCON600::getCOMLoopTest_INResult()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getSCCOMLoopTest_INResult();
			}
			else {
				return quint8();
			}
		}

		quint8 SenderCardItem_PCON600::getCOMLoopTest_OUTResult()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getSCCOMLoopTest_OUTResult();
			}
			else {
				return quint8();
			}
		}

		quint16 SenderCardItem_PCON600::writeEnterTestMode(QString key, bool sync, int msec)
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->writeEnterTestMode(key, sync, msec);
			}
			else {
				return quint16();
			}
		}

		quint16 SenderCardItem_PCON600::getEnterTestMode_Results()
		{
			Q_D(SenderCardItem_PCON600);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getEnterTestMode_Results();
			}
			else {
				return quint16();
			}
		}

		bool SenderCardItem_PCON600::registerControl()
		{
			Q_D(SenderCardItem_PCON600);
			//创建控制接口
			//创建Android接口
			if (d->m_detectInfo.communType != ECommunicatType::ECT_COM) {
				d->m_AndroidCtrl = Android::LBLAndroidFactory<Android::LBLAndroidAbstract, \
					Android::LBLAndroidCentralCtrl>::creatAndroidDevice(&(d->m_detectInfo), this);
                d->m_AndroidCtrl->readDeviceName(true, 150);
			}
			//创建SenderCard接口
			d->m_SenderCardCtrl = SC::LBLSenderCardFactory<SC::LBLSenderCardAbstract, \
				SC::LBLSenderCardCentralCtrl>::creatSenderCardDevice(&(d->m_detectInfo), this);
			d->m_SenderCardCtrl->checkItemUuid();
			//创建ReceiveCard接口
			d->m_ReceiveCardCtrl = RC::LBLReceiveCardFactory<RC::LBLReceiveCardAbstract, \
				RC::LBLReceiveCardCentralCtrl>::creatReceiveCardDevice(&(d->m_detectInfo), this);
			//创建HDMI接口
			d->m_HDMIChip = HDMIChip::LBLHDMIChipFactory<HDMIChip::LBLHDMIChipAbstract, \
				HDMIChip::LBLHDMIChipCentralCtrl>::creatHDMIChipDevice(&(d->m_detectInfo), this);
			//创建NT68400接口
			d->m_NT68400Ctrl = NT68400::LBLNT68400Factory<NT68400::LBLNT68400Abstract, \
				NT68400::LBLNT68400CentralCtrl>::creatNT68400Device(&(d->m_detectInfo), this);
			//创建文件传输接口
			d->m_FileTransfer = FileTransfer::LBLFileTransferFactory<FileTransfer::LBLFileTransferAbstract, \
				FileTransfer::LBLFileTransferCentralCtrl>::creatFileTransferDevice(&(d->m_detectInfo), this);
			return true;
		}

		bool SenderCardItem_PCON600::dispatcherPackage(const LBLEnginePackage& pack)
		{
			if (pack.isEmpty() || pack.hostName() != this->hostName())
			{
				return false;
			}
			Q_D(SenderCardItem_PCON600);
			LBLPackage tempPackage(pack.data());
			LBLPackage::EDeviceType dataSourceDevice = LBLPackage::EDeviceType(tempPackage.getSourceDevice());
			switch (dataSourceDevice)
			{
			case LBLPackage::EDT_Android:
			{
				if (d->m_AndroidCtrl)
					d->m_AndroidCtrl->parsingDataFrame(tempPackage);
				if (d->m_SenderCardCtrl)
					d->m_SenderCardCtrl->parsingDataFrame(tempPackage);
			}
				break;
			case LBLPackage::EDT_Monitor_In_Sender:
				break;
			case LBLPackage::EDT_MCU_In_Sender:
			{
				if (d->m_SenderCardCtrl)
					d->m_SenderCardCtrl->parsingDataFrame(tempPackage);
			}
				break;
			case LBLPackage::EDT_ReceiveCard:
				break;
			case LBLPackage::EDT_FPGA:
				break;
			case LBLPackage::EDT_NT68400:
				break;
			case LBLPackage::EDT_MS9570:
				break;
			case LBLPackage::EDT_External:
				break;
			case LBLPackage::EDT_CtrlSW:
				break;
			case LBLPackage::EDT_NULL:
				break;
			default:
				break;
			}
			return false;
		}

	}
}
