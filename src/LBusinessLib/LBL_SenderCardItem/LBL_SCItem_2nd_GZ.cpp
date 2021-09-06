#include "LBL_SCItem_2nd_GZ.h"
#include "LBL_SCItem_2nd_GZ_p.h"
#include <QTimer>
#include <QEventLoop>
#include <QCoreApplication>
#define LBL_TAG_SENDERCARD2NDGZ "SenderCard_2ndGZ"
namespace LBL
{
	namespace SCItem
	{

		SenderCardItem_2nd_GZ::SenderCardItem_2nd_GZ(QObject* parent/* = 0*/) :
			LBLAbstractSCItem(*new SenderCardItem_2nd_GZPrivate(), parent)
		{
			Q_D(SenderCardItem_2nd_GZ);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		SenderCardItem_2nd_GZ::SenderCardItem_2nd_GZ(SenderCardItem_2nd_GZPrivate& dd, QObject* parent /*= 0*/):
			LBLAbstractSCItem(dd,parent)
		{
			Q_D(SenderCardItem_2nd_GZ);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		SenderCardItem_2nd_GZ::~SenderCardItem_2nd_GZ()
		{
			qDebug() << __FUNCTION__;
		}

		QString SenderCardItem_2nd_GZ::senderCardTag() const
		{
			return LBL_TAG_SENDERCARD2NDGZ;
		}

		quint16 SenderCardItem_2nd_GZ::writeBrightness(int value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeBrightness(value, sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::readBrightness(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readBrightness(sync, msec);
		}

		int SenderCardItem_2nd_GZ::getBrightness()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getBrightness();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCFPGARegister(quint32 addr, QByteArray value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeFPGARegister(addr, value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCFPGARegister(quint32 addr, quint16 len, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readFPGARegister(addr, len, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::getSCFPGARegister()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getFPGARegister();
		}

		QByteArray SenderCardItem_2nd_GZ::readSCFPGAVersion(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readFPGAVersion(sync, msec);
		}

		QString SenderCardItem_2nd_GZ::getSCFPGAVersion()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getFPGAVersion();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeFPGAEthLoad(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCFPGAEthLoad(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readFPGAEthLoad(sync, msec);
		}

		QList<LBLSPort> SenderCardItem_2nd_GZ::getSCFPGAEthLoad()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getFPGAEthLoad();
		}

		quint16 SenderCardItem_2nd_GZ::readMCUAppVersion(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readMCUAppVersion(sync, msec);
		}

		QString SenderCardItem_2nd_GZ::getMCUAppVersion()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getMCUAppVersion();
		}

		quint16 SenderCardItem_2nd_GZ::readMCUBootVersion(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readMCUBootVersion(sync, msec);
		}

		QString SenderCardItem_2nd_GZ::getMCUBootVersion()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getMCUBootVersion();
		}

		quint16 SenderCardItem_2nd_GZ::writeSaveSCParam(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeSaveSCParam(sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::writeSCSelfTestMode(quint8 mode, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeSelfTestMode(mode, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCSelfTestMode(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readSelfTestMode(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSCSelfTestMode()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getSelfTestMode();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCSelfTestModeSpeed(quint8 speed, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeSelfTestModeSpeed(speed, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCSelfTestModeSpeed(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readSelfTestModeSpeed(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSCSelfTestModeSpeed()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getSelfTestModeSpeed();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCScreenBlack(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeScreenBlack(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCScreenBlack(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readScreenBlack(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSCScreenBlack()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getScreenBlack();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCScreenLock(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeScreenLock(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCScreenLock(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readScreenLock(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSCScreenLock()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getScreenLock();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCZoomMode(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeZoomMode(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCZoomMode(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readZoomMode(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSCZoomMode()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getZoomMode();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCZoomSize(QSize value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeZoomSize(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCZoomSize(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readZoomSize(sync, msec);
		}

		QSize SenderCardItem_2nd_GZ::getSCZoomSize()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getZoomSize();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeErrorBitRateStatisticalSwitch(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCErrorBitRateStatisticalSwitch(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readErrorBitRateStatisticalSwitch(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSCErrorBitRateStatisticalSwitch()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getErrorBitRateStatisticalSwitch();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCCorrectionSwitch(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeCorrectionSwitch(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCCorrectionSwitch(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readCorrectionSwitch(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSCCorrectionSwitch()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getCorrectionSwitch();
		}

		quint16 SenderCardItem_2nd_GZ::writeSCSpreadSpectrumSwitch(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeSpreadSpectrumSwitch(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCSpreadSpectrumSwitch(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readSpreadSpectrumSwitch(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSCSpreadSpectrumSwitch()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getSpreadSpectrumSwitch();
		}

		quint16 SenderCardItem_2nd_GZ::writeSC24BitGammaSwitch(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->write24BitGammaSwitch(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSC24BitGammaSwitch(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->read24BitGammaSwitch(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSC24BitGammaSwitch()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->get24BitGammaSwitch();
		}


		quint16 SenderCardItem_2nd_GZ::writeSCProtocolType(quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->writeProtocolType(value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readSCProtocolType(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->readProtocolType(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getSCProtocolType()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_SenderCardCtrl->getProtocolType();
		}

		quint16 SenderCardItem_2nd_GZ::writeConnection(LBLConnection * value, bool sync, int msec)
		{
			if (!value) {
				return LAPI::EResult::ER_InDataNullptr;
			}
			quint16 ret = writeSCFPGAEthLoad(value->getPortList(), sync, 1500);
			if (ret != LAPI::EResult::ER_INTECTRL_Success) {
				return ret;
			}
			return upgradeFile(sync, msec, LBLFileTransferPackage::EFileType::EFT_ConnectionFile, (*value).buildConnectionDataV2());
		}

		quint16 SenderCardItem_2nd_GZ::readConnection(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			QByteArray reData = readSCFPGAEthLoad(sync, 1500);
			if (reData.isEmpty()) {
				return LAPI::EResult::ER_CONNECT_NetPortLoadingAreaNotRead;
			}
			QByteArray connectionData;
			quint16 ret = requestFile(sync, msec, LBLFileTransferPackage::EFileType::EFT_ConnectionFile, connectionData);
			if (ret != LAPI::EResult::ER_Success) {
				return ret;
			}
			ret = d->m_connection.parseConnectionData(connectionData);
			if (ret != LAPI::EResult::ER_Success) {
				return ret;
			}

			ret = d->m_connection.checkPortLoadArea(getSCFPGAEthLoad());
			if (ret != LAPI::EResult::ER_Success) {
				return ret;
			}
			return LAPI::EResult::ER_Success;
		}

		quint16 SenderCardItem_2nd_GZ::writeRCFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->writeFPGARegister(port, module, addr, value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->readFPGARegister(port, module, addr, len, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::getRCFPGARegister()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->getFPGARegister();
		}

		quint16 SenderCardItem_2nd_GZ::writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->writeModuleParam(port, module, value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readModuleParam(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->readModuleParam(port, module, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::getModuleParam()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->getModuleParam();
		}

		quint16 SenderCardItem_2nd_GZ::writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->writeDriveICParam(port, module, value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readDriveICParam(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->readDriveICParam(port, module, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::getDriveICParam()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->getDriveICParam();
		}

		quint16 SenderCardItem_2nd_GZ::writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->writeDecodingICParam(port, module, value, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::readDecodingICParam(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->readDecodingICParam(port, module, sync, msec);
		}

		QByteArray SenderCardItem_2nd_GZ::getDecodingICParam()
		{
			Q_D(SenderCardItem_2nd_GZ);
            return d->m_ReceiveCardCtrl->getDecodingICParam();
        }

        quint16 SenderCardItem_2nd_GZ::writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd_GZ);
            return d->m_ReceiveCardCtrl->writeCalibrationDataErase(port, module, sync, msec);
        }

		quint16 SenderCardItem_2nd_GZ::writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->writeCalibrationDataSave(port, module, sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->writeCalibrationDataReload(port, module, sync, msec);
		}

		QList<RC::SRCStatusInfo> SenderCardItem_2nd_GZ::readRCStatusInfo(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
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
			if (!d->m_allRCStatusInfo.isEmpty()) {
				d->m_allRCStatusCacheInfo = d->m_allRCStatusInfo;
			}
			return d->m_allRCStatusCacheInfo;
		}

		QList<RC::SRCStatusInfo> SenderCardItem_2nd_GZ::readRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec)
		{
            Q_UNUSED(lengthFlag)
			Q_D(SenderCardItem_2nd_GZ);
			QList<RC::SRCStatusInfo> defaultList;
			quint16 ret = d->m_ReceiveCardCtrl->readStatusInfo(portStart, portCount, moduleStart, moduleCount, 0x03, sync, msec);
			if (LAPI::EResult::ER_INTECTRL_Success == ret) {
				return d->m_ReceiveCardCtrl->getStatusInfo();
			}
			return defaultList;
		}

		QList<RC::SRCStatusInfo> SenderCardItem_2nd_GZ::getRCStatusInfo()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_allRCStatusCacheInfo;
		}

		QList<RC::SRCMonitorInfo> SenderCardItem_2nd_GZ::readRCMonitorInfo(quint8 portIndex, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			QList<RC::SRCMonitorInfo> defaultList;
			for (int i = 0; i < 8; ++i)
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

		QList<RC::SRCMonitorInfo> SenderCardItem_2nd_GZ::getRCMonitorInfo()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->getMonitorInfo();
		}

		quint16 SenderCardItem_2nd_GZ::writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_ReceiveCardCtrl->writeSaveRCParamByRegister(port, module, sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::writeHDMIByPassStatus(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_MS9570Ctrl->writeBaypass(value, sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::readHDMIByPassStatus(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_MS9570Ctrl->readBaypass(sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::getHDMIByPassStatus()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_MS9570Ctrl->getBaypass();
		}

		quint16 SenderCardItem_2nd_GZ::writeHDMIImageRatio(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->writeRatio(value, sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::readHDMIImageRatio(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->readRatio(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getHDMIImageRatio()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->getRatio();
		}

		quint16 SenderCardItem_2nd_GZ::writeHDMIInputSource(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			quint8 source = 0;
			switch (value)
			{
			case LAPI::UI::EInputSource::EIS_HDMI1:
			{
				source = 0;
				break;
			}
			case LAPI::UI::EInputSource::EIS_HDMI2:
			{
				source = 1;
				break;
			}
			case LAPI::UI::EInputSource::EIS_HDMI3:
			{
				source = 2;
				break;
			}
			default:
				break;
			}
			return d->m_HDMIChip->writeSource(source, sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::readHDMIInputSource(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->readSource(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getHDMIInputSource()
		{
			Q_D(SenderCardItem_2nd_GZ);
			switch (d->m_HDMIChip->getSource())
			{
			case 0:
				return LAPI::UI::EInputSource::EIS_HDMI1;
			case 1:
				return LAPI::UI::EInputSource::EIS_HDMI2;
			case 2:
				return LAPI::UI::EInputSource::EIS_HDMI3;
			default:
				break;
			}
			return d->m_HDMIChip->getSource();
		}

		quint16 SenderCardItem_2nd_GZ::writeHDMIImageContrast(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->writeContrast(value, sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::readHDMIImageContrast(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->readContrast(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getHDMIImageContrast()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->getContrast();
		}

		quint16 SenderCardItem_2nd_GZ::writeHDMIImageColorTtemperature(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->writeColortemperature(value, sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::readHDMIImageColorTtemperature(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->readColortemperature(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getHDMIImageColorTtemperature()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->getColortemperature();
		}

		quint16 SenderCardItem_2nd_GZ::writeHDMIImageBrightness(const quint8 value, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->writeBrightness(value, sync, msec);
		}

		quint16 SenderCardItem_2nd_GZ::readHDMIImageBrightness(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->readBrightness(sync, msec);
		}

		quint8 SenderCardItem_2nd_GZ::getHDMIImageBrightness()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->getBrightness();
		}

		quint16 SenderCardItem_2nd_GZ::writeHDMIRGBGain(const int rValue, const int gValue, const int bValue, bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
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

		quint16 SenderCardItem_2nd_GZ::readHDMIRGBGain(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->readRGBGain(sync, msec);
		}

		QList<quint8> SenderCardItem_2nd_GZ::getHDMIRGBGain()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_HDMIChip->getRGBGain();
		}

		quint16 SenderCardItem_2nd_GZ::readHDMIVersion(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_MS9570Ctrl->readVersion(sync, msec);
		}

		QString SenderCardItem_2nd_GZ::getHDMIVersion()
		{
			Q_D(SenderCardItem_2nd_GZ);
			return d->m_MS9570Ctrl->getVersion();
		}

		quint16 SenderCardItem_2nd_GZ::upgradeFile(bool sync, int msec, quint16 fileType, QString fileName)
		{
			Q_D(SenderCardItem_2nd_GZ);
			if (d->m_AndroidFileTransfer&&fileType == LBLFileTransferPackage::EFileType::EFT_SenderMonitor) {
				d->m_FileTransfer = d->m_AndroidFileTransfer;
				return d->m_AndroidFileTransfer->common_UpgradeFile(sync, msec, fileType, fileName);
			}
			d->m_FileTransfer = d->m_MCUFileTransfer;
			return d->m_MCUFileTransfer->forMCU_UpgradeFile(sync, msec, fileType, fileName);
		}

		quint16 SenderCardItem_2nd_GZ::upgradeFile(bool sync, int msec, quint16 fileType, QString fileName, quint8 portIndex, quint16 moduleIndex)
		{
			Q_D(SenderCardItem_2nd_GZ);
			d->m_FileTransfer = d->m_MCUFileTransfer;
			return d->m_MCUFileTransfer->forMCU_UpgradeFile(sync, msec, fileType, fileName, portIndex, moduleIndex);
		}

		quint16 SenderCardItem_2nd_GZ::upgradeFile(bool sync, int msec, quint16 fileType, QByteArray data)
		{
			Q_D(SenderCardItem_2nd_GZ); 
			if (d->m_AndroidFileTransfer &&
				!d->m_FileTransfer->isUpgrading() &&
				fileType == LBLFileTransferPackage::EFileType::EFT_SenderMonitor) {
				d->m_FileTransfer = d->m_AndroidFileTransfer;
				return d->m_AndroidFileTransfer->common_UpgradeFile(sync, msec, fileType, data);
			}
			d->m_FileTransfer = d->m_MCUFileTransfer;
			return d->m_MCUFileTransfer->forMCU_UpgradeFile(sync, msec, fileType, data);
		}

		quint16 SenderCardItem_2nd_GZ::upgradeFile(bool sync, int msec, quint16 fileType, QByteArray dat, quint8 portIndex, quint16 moduleIndex)
		{
            Q_UNUSED(fileType);
            Q_UNUSED(dat);
            Q_UNUSED(portIndex);
            Q_UNUSED(moduleIndex);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
			return quint16();
		}

		quint16 SenderCardItem_2nd_GZ::requestFile(bool sync, int msec, quint16 fileType, QString fileName)
		{
			Q_D(SenderCardItem_2nd_GZ);
			d->m_FileTransfer = d->m_MCUFileTransfer;
			return d->m_MCUFileTransfer->forMCU_RequestFile(sync, msec, fileType, fileName);
		}

		quint16 SenderCardItem_2nd_GZ::requestFile(bool sync, int msec, quint16 fileType, QByteArray & data)
		{
			Q_D(SenderCardItem_2nd_GZ);
			d->m_FileTransfer = d->m_MCUFileTransfer;
			return d->m_MCUFileTransfer->forMCU_RequestFile(sync, msec, fileType, data);
		}

		quint16 SenderCardItem_2nd_GZ::readAndroidVersion(bool sync, int msec)
		{
			Q_D(SenderCardItem_2nd_GZ);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->readAndroidVersion(sync, msec);
			}
			else {
				return LAPI::EResult::ER_NotSupportThisCommand;
			}
		}

		QString SenderCardItem_2nd_GZ::getAndroidVersion()
		{
			Q_D(SenderCardItem_2nd_GZ);
			if (d->m_AndroidCtrl) {
				return d->m_AndroidCtrl->getAndroidVersion();
			}
			else {
				return QString();
			}
		}

		bool SenderCardItem_2nd_GZ::registerControl()
		{
			Q_D(SenderCardItem_2nd_GZ);
			//创建控制接口
			//创建SenderCard接口
			if (d->m_detectInfo.communType == ECommunicatType::ECT_COM) {
				d->m_SenderCardCtrl = SC::LBLSenderCardFactory<SC::LBLSenderCardAbstract, \
					SC::LBLSenderCardCentralCtrl_COM>::creatSenderCardDevice(&(d->m_detectInfo), this);
			}
			else {
				d->m_SenderCardCtrl = SC::LBLSenderCardFactory<SC::LBLSenderCardAbstract, \
					SC::LBLSenderCardCentralCtrl>::creatSenderCardDevice(&(d->m_detectInfo), this);
			}
			d->m_SenderCardCtrl->checkItemUuid();
			//创建ReceiveCard接口
			d->m_ReceiveCardCtrl = RC::LBLReceiveCardFactory<RC::LBLReceiveCardAbstract, \
				RC::LBLReceiveCardCentralCtrl>::creatReceiveCardDevice(&(d->m_detectInfo), this);
			//创建HDMI接口
			d->m_HDMIChip = HDMIChip::LBLHDMIChipFactory<HDMIChip::LBLHDMIChipAbstract, \
				HDMIChip::LBLHDMIChipCentralCtrl>::creatHDMIChipDevice(&(d->m_detectInfo), this);
			//创建MS9570接口
			d->m_MS9570Ctrl = MS9570::MS9570CtrlFactory<MS9570::LBLMS9570Abstract, \
				MS9570::LBLMS9570CentralCtrl>::creatSenderItem(&(d->m_detectInfo), this);
			//创建文件传输接口
			if (d->m_detectInfo.communType != ECommunicatType::ECT_COM) {
				d->m_AndroidCtrl = Android::LBLAndroidFactory<Android::LBLAndroidAbstract, \
					Android::LBLAndroidCentralCtrl>::creatAndroidDevice(&(d->m_detectInfo), this);
				d->m_AndroidCtrl->readDeviceName(true, 150);
				d->m_AndroidFileTransfer = FileTransfer::LBLFileTransferFactory<FileTransfer::LBLFileTransferAbstract, \
					FileTransfer::LBLFileTransferCentralCtrl>::creatFileTransferDevice(&(d->m_detectInfo), this);
			}
			d->m_MCUFileTransfer = FileTransfer::LBLFileTransferFactory<FileTransfer::LBLFileTransferAbstract, \
				FileTransfer::LBLFileTransferCentralCtrl_COM>::creatFileTransferDevice(&(d->m_detectInfo), this);

			return true;
		}

		bool SenderCardItem_2nd_GZ::dispatcherPackage(const LBLEnginePackage & pack)
		{
			if (pack.isEmpty() || pack.hostName() != this->hostName())
			{
				return false;
			}
			Q_D(SenderCardItem_2nd_GZ);
			LBLPackage tempPackage(pack.data());
			LBLPackage::EDeviceType dataSourceDevice = LBLPackage::EDeviceType(tempPackage.getSourceDevice());
			switch (dataSourceDevice)
			{
			case LBLPackage::EDT_Android:
			{
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
				if (d->m_ReceiveCardCtrl)
					d->m_ReceiveCardCtrl->parsingDataFrame(tempPackage);
			}
			break;
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
