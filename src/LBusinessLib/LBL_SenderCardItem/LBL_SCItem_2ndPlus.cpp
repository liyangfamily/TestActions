#include "LBL_SCItem_2ndPlus.h"
#include "LBL_SCItem_2ndPlus_p.h"

#define LBL_TAG_SENDERCARD2NDPLUS "2ndPlus"
namespace LBL
{
    namespace SCItem
    {

        SenderCardItem_2ndPlus::SenderCardItem_2ndPlus(QObject* parent/* = 0*/) :
            LBLAbstractSCItem(*new SenderCardItem_2ndPlusPrivate(), parent)
        {
            Q_D(SenderCardItem_2ndPlus);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
        }

        SenderCardItem_2ndPlus::SenderCardItem_2ndPlus(SenderCardItem_2ndPlusPrivate & dd, QObject * parent) :
            LBLAbstractSCItem(dd, parent)
        {
            Q_D(SenderCardItem_2ndPlus);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
        }


        SenderCardItem_2ndPlus::~SenderCardItem_2ndPlus()
        {
        }

        QString SenderCardItem_2ndPlus::senderCardTag() const
        {
            return LBL_TAG_SENDERCARD2NDPLUS;
        }

        int SenderCardItem_2ndPlus::maxPortCount() const
        {
            return 16;
        }

        bool SenderCardItem_2ndPlus::hasMS9570() const
        {
            return false;
        }

        bool SenderCardItem_2ndPlus::hasNT68400() const
        {
            return true;
        }

        bool SenderCardItem_2ndPlus::hasAndroid() const
        {
            return true;
        }

        quint16 SenderCardItem_2ndPlus::writeBrightness(int value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeBrightness(value, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readBrightness(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readBrightness(sync, msec);
        }

        int SenderCardItem_2ndPlus::getBrightness()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getBrightness();
        }

        quint16 SenderCardItem_2ndPlus::writeSCFPGARegister(quint32 addr, QByteArray value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeFPGARegister(addr, value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCFPGARegister(quint32 addr, quint16 len, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readFPGARegister(addr, len, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::getSCFPGARegister()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getFPGARegister();
        }

        QByteArray SenderCardItem_2ndPlus::readSCFPGAVersion(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readFPGAVersion(sync, msec);
        }

        QString SenderCardItem_2ndPlus::getSCFPGAVersion()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getFPGAVersion();
        }

        quint16 SenderCardItem_2ndPlus::writeSCFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeFPGAEthLoad(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCFPGAEthLoad(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readFPGAEthLoad(sync, msec);
        }

        QList<LBLSPort> SenderCardItem_2ndPlus::getSCFPGAEthLoad()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getFPGAEthLoad();
        }

        quint16 SenderCardItem_2ndPlus::writeSaveSCParam(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeSaveSCParam(sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeSCSelfTestMode(quint8 mode, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeSelfTestMode(mode, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCSelfTestMode(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readSelfTestMode(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCSelfTestMode()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getSelfTestMode();
        }

        quint16 SenderCardItem_2ndPlus::writeSCSelfTestModeSpeed(quint8 speed, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeSelfTestModeSpeed(speed, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCSelfTestModeSpeed(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readSelfTestModeSpeed(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCSelfTestModeSpeed()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getSelfTestModeSpeed();
        }

        quint16 SenderCardItem_2ndPlus::writeSCScreenBlack(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeScreenBlack(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCScreenBlack(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readScreenBlack(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCScreenBlack()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getScreenBlack();
        }

        quint16 SenderCardItem_2ndPlus::writeSCScreenLock(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeScreenLock(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCScreenLock(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readScreenLock(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCScreenLock()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getScreenLock();
        }

        quint16 SenderCardItem_2ndPlus::writeSCZoomMode(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeZoomMode(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCZoomMode(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readZoomMode(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCZoomMode()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getZoomMode();
        }

        quint16 SenderCardItem_2ndPlus::writeSCZoomSize(QSize value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeZoomSize(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCZoomSize(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readZoomSize(sync, msec);
        }

        QSize SenderCardItem_2ndPlus::getSCZoomSize()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getZoomSize();
        }

        quint16 SenderCardItem_2ndPlus::writeSCErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeErrorBitRateStatisticalSwitch(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCErrorBitRateStatisticalSwitch(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readErrorBitRateStatisticalSwitch(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCErrorBitRateStatisticalSwitch()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getErrorBitRateStatisticalSwitch();
        }

        quint16 SenderCardItem_2ndPlus::writeSCCorrectionSwitch(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeCorrectionSwitch(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCCorrectionSwitch(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readCorrectionSwitch(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCCorrectionSwitch()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getCorrectionSwitch();
        }

        quint16 SenderCardItem_2ndPlus::writeSCSpreadSpectrumSwitch(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeSpreadSpectrumSwitch(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCSpreadSpectrumSwitch(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readSpreadSpectrumSwitch(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCSpreadSpectrumSwitch()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getSpreadSpectrumSwitch();
        }

        quint16 SenderCardItem_2ndPlus::writeSC24BitGammaSwitch(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->write24BitGammaSwitch(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSC24BitGammaSwitch(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->read24BitGammaSwitch(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSC24BitGammaSwitch()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->get24BitGammaSwitch();
        }


        quint16 SenderCardItem_2ndPlus::writeSCProtocolType(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeProtocolType(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCProtocolType(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readProtocolType(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCProtocolType()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getProtocolType();
        }

        quint16 SenderCardItem_2ndPlus::writeSCNT68400Resolution(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeNT68400Resolution(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCNT68400Resolution(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readNT68400Resolution(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCNT68400Resolution()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getNT68400Resolution();
        }

        quint16 SenderCardItem_2ndPlus::writeSC10BitSource(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if(!value){
                d->m_ReceiveCardCtrl->write10BitGammaDataReload(0xFF, 0xFF, sync, msec);
            }
            return d->m_SenderCardCtrl->write10BitSource(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSC10BitSource(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->read10BitSource(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSC10BitSource()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->get10BitSource();
        }

        quint16 SenderCardItem_2ndPlus::writeSCLowDelay(quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->writeLowDelay(value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readSCLowDelay(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->readLowDelay(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getSCLowDelay()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getLowDelay();
        }

        quint16 SenderCardItem_2ndPlus::writeConnection(LBLConnection * value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (!value) {
                return LAPI::EResult::ER_InDataNullptr;
            }
            quint16 ret = writeSCFPGAEthLoad(value->portList(), sync, 1500);
            if (ret != LAPI::EResult::ER_INTECTRL_Success) {
                return ret;
            }
            ret = upgradeFile(sync, msec, LBLFileTransferPackage::EFileType::EFT_ConnectionFile, (*value).buildConnectionDataV0());
            if (ret != LAPI::EResult::ER_INTECTRL_Success) {
                return ret;
            }
            return d->m_SenderCardCtrl->sendConnectionBuffer(sync, 1500);
        }

        quint16 SenderCardItem_2ndPlus::readConnection(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (readSCFPGAEthLoad(sync, 1500).isEmpty()) {
                return LAPI::EResult::ER_CONNECT_NetPortLoadingAreaNotRead;
            }
            QByteArray connectionData;
            msec=550;
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

        quint16 SenderCardItem_2ndPlus::writeRCFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeFPGARegister(port, module, addr, value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->readFPGARegister(port, module, addr, len, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::getRCFPGARegister()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->getFPGARegister();
        }


        quint16 SenderCardItem_2ndPlus::writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeModuleParam(port, module, value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readModuleParam(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->readModuleParam(port, module, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::getModuleParam()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->getModuleParam();
        }

        quint16 SenderCardItem_2ndPlus::writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeDriveICParam(port, module, value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readDriveICParam(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->readDriveICParam(port, module, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::getDriveICParam()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->getDriveICParam();
        }

        quint16 SenderCardItem_2ndPlus::writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeDecodingICParam(port, module, value, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::readDecodingICParam(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->readDecodingICParam(port, module, sync, msec);
        }

        QByteArray SenderCardItem_2ndPlus::getDecodingICParam()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->getDecodingICParam();
        }

        quint16 SenderCardItem_2ndPlus::writeLinearTableFile(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeLinearTableFile(port, module, value, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeCalibrationDataErase(port, module, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeCalibrationDataSave(port, module, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeCalibrationDataReload(port, module, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeLowGrayCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeLowGrayCalibrationDataErase(port, module, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeLowGrayCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeLowGrayCalibrationDataSave(port, module, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeLowGrayCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeLowGrayCalibrationDataReload(port, module, sync, msec);
        }

        QList<RC::SRCStatusInfo> SenderCardItem_2ndPlus::readRCStatusInfo(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            d->m_allRCStatusInfo.clear();
            for (auto port : d->m_connection.portList()) {
                for (auto module : port.moduleList()) {
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

        QList<RC::SRCStatusInfo> SenderCardItem_2ndPlus::readRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec)
        {
            Q_UNUSED(lengthFlag)
            Q_D(SenderCardItem_2ndPlus);
            QList<RC::SRCStatusInfo> defaultList;
            quint16 ret = d->m_ReceiveCardCtrl->readStatusInfo(portStart, portCount, moduleStart, moduleCount, 0x03, sync, msec);
            if (LAPI::EResult::ER_INTECTRL_Success == ret) {
                return d->m_ReceiveCardCtrl->getStatusInfo();
            }
            return defaultList;
        }

        QList<RC::SRCStatusInfo> SenderCardItem_2ndPlus::getRCStatusInfo()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->getStatusInfo();
        }

        QList<RC::SRCMonitorInfo> SenderCardItem_2ndPlus::readRCMonitorInfo(quint8 portIndex, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
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

        QList<RC::SRCMonitorInfo> SenderCardItem_2ndPlus::getRCMonitorInfo()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->getMonitorInfo();
        }

        quint16 SenderCardItem_2ndPlus::writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_ReceiveCardCtrl->writeSaveRCParamByRegister(port, module, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIByPassStatus(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeSetting_ByPass(value, 0, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDMIByPassStatus(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readSetting_ByPass(0, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::getHDMIByPassStatus()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getSetting_ByPass();
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIImageRatio(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeDP_AspectRatio(value,LAPI::UI::EHDMIChannel::EHC_All, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDMIImageRatio(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readDP_AspectRatio(LAPI::UI::EHDMIChannel::EHC_All,sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDMIImageRatio()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getDP_AspectRatio();
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIInputSource(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->writeSource(value, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDMIInputSource(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->readSource(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDMIInputSource()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->getSource();
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIImageContrast(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->writeContrast(value, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDMIImageContrast(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->readContrast(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDMIImageContrast()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->getContrast();
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIImageColorTtemperature(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->writeColortemperature(value, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDMIImageColorTtemperature(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->readColortemperature(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDMIImageColorTtemperature()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->getColortemperature();
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIImageBrightness(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->writeBrightness(value, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDMIImageBrightness(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->readBrightness(sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDMIImageBrightness()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_HDMIChip->getBrightness();
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIRGBGain(const int rValue, const int gValue, const int bValue, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            quint16 ret = 0;
            //            if (-1 != rValue && -1 != gValue && -1 != bValue)
            //            {
            //                ret = d->m_HDMIChip->writeRGBGain(rValue, gValue, bValue, sync, msec);
            //            }
            if (-1 != rValue)
            {
                ret = d->m_NT68400Ctrl->writePQ_Color_R(rValue, 0, sync, msec);
            }
            if (-1 != gValue)
            {
                ret = d->m_NT68400Ctrl->writePQ_Color_G(gValue, 0, sync, msec);
            }
            if (-1 != bValue)
            {
                ret = d->m_NT68400Ctrl->writePQ_Color_B(bValue, 0, sync, msec);
            }
            return ret;
        }

        quint16 SenderCardItem_2ndPlus::readHDMIRGBGain(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readAllPQNormalData(0, 0, sync, msec);
        }

        QList<quint8> SenderCardItem_2ndPlus::getHDMIRGBGain()
        {
            Q_D(SenderCardItem_2ndPlus);
            return QList<quint8>() << d->m_NT68400Ctrl->getPQ_Color_R()
                                   << d->m_NT68400Ctrl->getPQ_Color_G()
                                   << d->m_NT68400Ctrl->getPQ_Color_B();
        }


        quint16 SenderCardItem_2ndPlus::readHDMIInputSignalInfo(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readSignal_InputSignalInfo(0, sync, msec);
        }

        QString SenderCardItem_2ndPlus::getHDMIInputSignalInfo()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getSignal_InputSignalInfo();
        }

        quint16 SenderCardItem_2ndPlus::readHDMIVersion(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readSys_Version(0, sync, msec);
        }

        QString SenderCardItem_2ndPlus::getHDMIVersion()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getSys_Version();
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIMultiScreenMode(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeDP_PIPorPBP(value, 0, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDMIMultiScreenMode(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readDP_PIPorPBP(0, sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDMIMultiScreenMode()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getDP_PIPorPBP();
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIMultiScreenInputSource(const quint8 param, const quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeDP_MainorPIPInput(param, param, param, param, channel, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIMultiScreenInputSourceList(const QList<quint8>& values, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (values.size() != d->m_NT68400Ctrl->channelCount()) {
                return LAPI::ER_InDataError;
            }
            return d->m_NT68400Ctrl->writeDP_MainorPIPInput(values.at(0), values.at(1), values.at(2), values.at(3), 0, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDMIMultiScreenInputSource(const quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readDP_MainorPIPInput(channel, sync, msec);
        }

        QList<quint8> SenderCardItem_2ndPlus::getHDMIMultiScreenInputSource(const quint8 channel)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (!channel) {
                return d->m_NT68400Ctrl->getDP_MainorPIPInputList();
            }
            else {
                if (channel > d->m_NT68400Ctrl->getDP_MainorPIPInputList().size()) {
                    return QList<quint8>();
                }
                else {
                    return QList<quint8>() << d->m_NT68400Ctrl->getDP_MainorPIPInputList().at(channel - 1);
                }
            }
        }

        quint16 SenderCardItem_2ndPlus::resetHDMISetting(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->resetHDMISetting(sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::writeHDIMIWindowSize(QSize value, quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeDP_WindowSize(value.width(), value.height(), channel, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDIMIWindowSize(quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readDP_WindowSize(channel, sync, msec);
        }

        QSize SenderCardItem_2ndPlus::getHDIMIWindowSize()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getDP_WindowSize();
        }

        quint16 SenderCardItem_2ndPlus::writeHDIMIWindowPos(QPoint value, quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeDP_WindowPos(value.x(), value.y(), channel, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDIMIWindowPos(quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readDP_WindowPos(channel, sync, msec);
        }

        QPoint SenderCardItem_2ndPlus::getHDIMIWindowPos()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getDP_WindowPos();
        }

        quint16 SenderCardItem_2ndPlus::writeHDIMIWindowStatus(quint8 status, quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeDP_PIPWindowStatus(status, channel, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDIMIWindowStatus(quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readDP_PIPWindowStatus(channel, sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDIMIWindowStatus()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getDP_PIPWindowStatus();
        }

        quint16 SenderCardItem_2ndPlus::readAllHDMIAdvanceData_PIP(quint8 param, quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readAllDPAdvanceData_PIP(param,channel,sync,msec);
        }

        quint16 SenderCardItem_2ndPlus::writeHDMIOutputSource(quint8 hdmi1, quint8 hdmi2, quint8 dp, quint8 channel, bool sync, int msec)
        {
            if(hdmi1==5){
                hdmi1=0xFF;
            }
            if(hdmi2==5){
                hdmi2=0xFF;
            }
            if(dp==5){
                dp=0xFF;
            }
            if(hdmi1==6){
                hdmi1=5;
            }
            if(hdmi2==6){
                hdmi2=5;
            }
            if(dp==6){
                dp=5;
            }
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeSetting_DP_TX(hdmi1, hdmi2, dp, channel, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDMIOutputSource(quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readSetting_DP_TX(channel, sync, msec);
        }

        QList<quint8> SenderCardItem_2ndPlus::getHDMIOutputSource()
        {
            Q_D(SenderCardItem_2ndPlus);
            QList<quint8> temp=d->m_NT68400Ctrl->getSetting_DP_TX();
            for(auto&& i:temp){
                if(i==5){
                    i=6;
                }
            }
            return temp;
        }

        quint16 SenderCardItem_2ndPlus::writeHDIMIAudioSrc(quint8 param, quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeSetting_AudioSrc(param, channel, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDIMIAudioSrc(quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readSetting_AudioSrc(channel, sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDIMIAudioSrc()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getSetting_AudioSrc();
        }

        quint16 SenderCardItem_2ndPlus::writeHDIMIAudioVolume(quint8 param, quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeSetting_Volume(param, channel, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDIMIAudioVolume(quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readSetting_Volume(channel, sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDIMIAudioVolume()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getSetting_Volume();
        }

        quint16 SenderCardItem_2ndPlus::writeHDIMISharpness(quint8 param, quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writePQ_Sharpness(param, channel, sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDIMISharpness(quint8 channel, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readPQ_Sharpness(channel, sync, msec);
        }

        quint8 SenderCardItem_2ndPlus::getHDIMISharpness()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getPQ_Sharpness();
        }

        quint16 SenderCardItem_2ndPlus::writeHDIMIDisplayArea(QSize value, quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(channel);
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->writeSys_DisplayArea(value.width(),value.height(), sync, msec);
        }

        quint16 SenderCardItem_2ndPlus::readHDIMIDisplayArea(quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(channel);
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->readSys_DisplayArea(sync, msec);
        }

        QSize SenderCardItem_2ndPlus::getHDIMIDisplayArea()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_NT68400Ctrl->getSys_DisplayArea();
        }

        quint16 SenderCardItem_2ndPlus::upgradeFile(bool sync, int msec, quint16 fileType, QString fileName, quint8 portIndex, quint16 moduleIndex)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_FileTransfer->common_UpgradeFile(sync, msec, fileType, fileName,portIndex,moduleIndex);
        }

        quint16 SenderCardItem_2ndPlus::upgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex)
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_FileTransfer->common_UpgradeFile(sync, msec, fileType, data,portIndex,moduleIndex);
        }

        quint16 SenderCardItem_2ndPlus::requestFile(bool sync, int msec, quint16 fileType, QString fileName)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            Q_UNUSED(fileType);
            Q_UNUSED(fileName);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        quint16 SenderCardItem_2ndPlus::requestFile(bool sync, int msec, quint16 fileType, QByteArray & data)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            Q_UNUSED(fileType);
            Q_UNUSED(data);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        quint16 SenderCardItem_2ndPlus::readAndroidVersion(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readAndroidVersion(sync, msec);
            }
            else {
                return LAPI::EResult::ER_NotSupportThisCommand;
            }
        }

        QString SenderCardItem_2ndPlus::getAndroidVersion()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getAndroidVersion();
            }
            else {
                return QString();
            }

        }

        quint16 SenderCardItem_2ndPlus::writeKeyEvent(quint8 status, quint16 keyCode, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->writeKeyEvent(status, keyCode, sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::getKeyEvent_Result()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getKeyEvent_Result();
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::writeDeviceName(QString name, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->writeDeviceName(name, sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::readDeviceName(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readDeviceName(sync, msec);
            }
            else {
                return quint16();
            }
        }

        QString SenderCardItem_2ndPlus::getDeviceName()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getDeviceName();
            }
            else {
                return QString();
            }
        }

        quint16 SenderCardItem_2ndPlus::readNetDeviceOnlineStatus(QString ip, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readNetDeviceOnlineStatus(ip, sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::getNetDevice_Status()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getNetDevice_Status();
            }
            else {
                return quint16();
            }
        }

        QString SenderCardItem_2ndPlus::getNetDevice_IP()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getNetDevice_IP();
            }
            else {
                return QString();
            }
        }

        quint16 SenderCardItem_2ndPlus::readSCEthLoopTestResult(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            /*if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readSCEthLoopTestResult(sync, msec);
            }
            else {
                return quint16();
            }*/
            d->m_SenderCardCtrl->readEthLoopTest(sync, msec);
            return LAPI::EResult::ER_INTECTRL_Success;
        }

        quint16 SenderCardItem_2ndPlus::getSCEthLoopTest_Result()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getSCEthLoopTest_Result();
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getSCEthLoopTest_EffectiveEthCount()
        {
            Q_D(SenderCardItem_2ndPlus);
            /*if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getSCEthLoopTest_EffectiveEthCount();
            }
            else {
                return quint8();
            }*/
            return d->m_SenderCardCtrl->getEthLoopTest_Count();
        }

        QByteArray SenderCardItem_2ndPlus::getSCEthLoopTest_ReplyData()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getSCEthLoopTest_ReplyData();
            }
            else {
                return QByteArray();
            }
        }

        QMap<quint8, float> SenderCardItem_2ndPlus::getSCEthLoopTest_BitErrRate()
        {
            Q_D(SenderCardItem_2ndPlus);
            return d->m_SenderCardCtrl->getEthLoopTest_BitErrRate();
        }

        quint16 SenderCardItem_2ndPlus::readUDiskMountingStatus(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readUDiskMountingStatus(sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getUDiskMounting_Count()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getUDiskMounting_Count();
            }
            else {
                return quint8();
            }
        }

        QStringList SenderCardItem_2ndPlus::getUDiskMounting_List()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getUDiskMounting_List();
            }
            else {
                return QStringList();
            }
        }

        quint16 SenderCardItem_2ndPlus::writeStartOSDTest(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->writeStartOSDTest(sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getOSDTest_WhiteScreenTestResult()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getOSDTest_BlackScreenTestResult();
            }
            else {
                return quint8();
            }
        }

        quint8 SenderCardItem_2ndPlus::getOSDTest_BlackScreenTestResult()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getOSDTest_BlackScreenTestResult();
            }
            else {
                return quint8();
            }
        }

        quint16 SenderCardItem_2ndPlus::writeRelaySwitc(quint8 status, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->writeRelaySwitc(status, sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::getRelaySwitc_Result()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getRelaySwitc_Result();
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getRelaySwitc_Status()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getRelaySwitc_Status();
            }
            else {
                return quint8();
            }
        }

        quint16 SenderCardItem_2ndPlus::writeEnterKeyTest(quint8 status, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->writeEnterKeyTest(status, sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getKeyTest_Result()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getKeyTest_Result();
            }
            else {
                return quint8();
            }
        }

        quint16 SenderCardItem_2ndPlus::readKeyTestResult(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readKeyTestResult(sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getKeyTestResult_Count()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getKeyTestResult_Count();
            }
            else {
                return quint8();
            }
        }

        QList<quint16> SenderCardItem_2ndPlus::getKeyTestResult_List()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getKeyTestResult_List();
            }
            else {
                return QList<quint16>();
            }
        }

        quint16 SenderCardItem_2ndPlus::readOpticalSensorParam(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readOpticalSensorParam(sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::getOpticalSensor_Param()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getOpticalSensor_Param();
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::readRouterStatus(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readRouterStatus(sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getRouter_5GWifiStatus()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getRouter_5GWifiStatus();
            }
            else {
                return quint8();
            }
        }

        quint8 SenderCardItem_2ndPlus::getRouter_2_4GWifiStatus()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getRouter_2_4GWifiStatus();
            }
            else {
                return quint8();
            }
        }

        quint16 SenderCardItem_2ndPlus::writeNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->writeNetworkCardMACAddr(flage, mac, sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::getNetworkCardMACAddr_Results()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getNetworkCardMACAddr_Results();
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getNetworkCardMACAddr_Flage()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getNetworkCardMACAddr_Flage();
            }
            else {
                return quint8();
            }
        }

        QByteArray SenderCardItem_2ndPlus::getNetworkCardMACAddr_MAC()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getNetworkCardMACAddr_MAC();
            }
            else {
                return QByteArray();
            }
        }

        quint16 SenderCardItem_2ndPlus::writePlayTestSound_1KHZ(quint8 status, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->writePlayTestSound_1KHZ(status, sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::getPlayTestSound_Results()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getPlayTestSound_Results();
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getPlayTestSound_Status()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getPlayTestSound_Status();
            }
            else {
                return quint8();
            }
        }

        quint16 SenderCardItem_2ndPlus::writeWIFIModuleScanTest(quint8 status, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->writeWIFIModuleScanTest(status, sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::getWIFIModuleScanTest_Results()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getWIFIModuleScanTest_Results();
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::readWIFIScanList(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readWIFIScanList(sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getWIFIScanList_Count()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getWIFIScanList_Count();
            }
            else {
                return quint8();
            }
        }

        quint16 SenderCardItem_2ndPlus::readLoadPowerAmplifierChipParam(bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->readLoadPowerAmplifierChipParam(sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint8 SenderCardItem_2ndPlus::getPowerAmplifierChipParam_Results()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getPowerAmplifierChipParam_Results();
            }
            else {
                return quint8();
            }
        }

        quint8 SenderCardItem_2ndPlus::getPowerAmplifierChipParam_30Results()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getPowerAmplifierChipParam_30Results();
            }
            else {
                return quint8();
            }
        }

        quint8 SenderCardItem_2ndPlus::getPowerAmplifierChipParam_31Results()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getPowerAmplifierChipParam_31Results();
            }
            else {
                return quint8();
            }
        }

        quint16 SenderCardItem_2ndPlus::writeEnterTestMode(QString key, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->writeEnterTestMode(key, sync, msec);
            }
            else {
                return quint16();
            }
        }

        quint16 SenderCardItem_2ndPlus::getEnterTestMode_Results()
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_AndroidCtrl) {
                return d->m_AndroidCtrl->getEnterTestMode_Results();
            }
            else {
                return quint16();
            }
        }

        bool SenderCardItem_2ndPlus::registerControl()
        {
            Q_D(SenderCardItem_2ndPlus);
            //创建控制接口
            //创建Android接口
            if (d->m_detectInfo.communType != ECommunicatType::ECT_COM) {
                d->m_AndroidCtrl = Android::LBLAndroidFactory<Android::LBLAndroidAbstract, \
                    Android::LBLAndroidCentralCtrl>::creatAndroidDevice(&(d->m_detectInfo), this);
                d->m_AndroidCtrl->readDeviceName(true,150);
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
            d->m_FileTransfer = FileTransfer::LBLFileTransferFactory<FileTransfer::LBLFileTransferAbstract, \
                FileTransfer::LBLFileTransferCentralCtrl>::creatFileTransferDevice(&(d->m_detectInfo), this);
            return false;
        }

        bool SenderCardItem_2ndPlus::dispatcherPackage(const LBLEnginePackage & pack)
        {
            if (pack.isEmpty() || pack.hostName() != this->hostName())
            {
                return false;
            }
            Q_D(SenderCardItem_2ndPlus);
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

        quint16 SenderCardItem_2ndPlus::writeFacTest_UpdateEDID(quint8 dataGroupIndex, quint8* pDataBuff, quint8 dataLen, bool sync, int msec)
        {
            Q_D(SenderCardItem_2ndPlus);
            if (d->m_NT68400Ctrl) {
                return d->m_NT68400Ctrl->writeFacTest_UpdateEDID(dataGroupIndex,pDataBuff,dataLen,sync,msec);
            }
            else {
                return quint16();
            }
        }
    }
}
