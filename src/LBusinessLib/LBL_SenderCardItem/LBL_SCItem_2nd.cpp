#include "LBL_SCItem_2nd.h"
#include "LBL_SCItem_2nd_p.h"
#include <LBL_CommunicatEngine/LBLPackageDispatcher>

#define LBL_TAG_SENDERCARD2ND "PCON500"
namespace LBL
{
    namespace SCItem
    {
        SenderCardItem_2nd::SenderCardItem_2nd(QObject* parent/* = 0*/) :
            LBLAbstractSCItem(*new SenderCardItem_2ndPrivate(), parent)
        {
            Q_D(SenderCardItem_2nd);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
        }

        SenderCardItem_2nd::SenderCardItem_2nd(SenderCardItem_2ndPrivate &dd, QObject* parent) :
            LBLAbstractSCItem(dd,parent)
        {
            Q_D(SenderCardItem_2nd);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
        }


        SenderCardItem_2nd::~SenderCardItem_2nd()
        {
        }

        QString SenderCardItem_2nd::senderCardTag() const
        {
            return LBL_TAG_SENDERCARD2ND;
        }

        quint16 SenderCardItem_2nd::writeBrightness(int value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_SenderCardCtrl->writeBrightness(value, sync, msec);
        }

        quint16 SenderCardItem_2nd::readBrightness(bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_SenderCardCtrl->readBrightness(sync, msec);
        }

        int SenderCardItem_2nd::getBrightness()
        {
            Q_D(SenderCardItem_2nd);
            return d->m_SenderCardCtrl->getBrightness();
        }

        quint16 SenderCardItem_2nd::writeHDMIByPassStatus(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->writeBypass(value, sync, msec);
        }

        quint16 SenderCardItem_2nd::readHDMIByPassStatus(bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->readBypass(sync, msec);
        }

        quint16 SenderCardItem_2nd::getHDMIByPassStatus()
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->getBypasss();
        }

        quint16 SenderCardItem_2nd::writeHDMIImageRatio(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->writeRatio(value, sync, msec);
        }

        quint16 SenderCardItem_2nd::readHDMIImageRatio(bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->readRatio(sync, msec);
        }

        quint8 SenderCardItem_2nd::getHDMIImageRatio()
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->getRatio();
        }

        quint16 SenderCardItem_2nd::writeHDMIInputSource(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->writeSource(value, sync, msec);
        }

        quint16 SenderCardItem_2nd::readHDMIInputSource(bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->readSource(sync, msec);
        }

        quint8 SenderCardItem_2nd::getHDMIInputSource()
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->getSource();
        }

        quint16 SenderCardItem_2nd::writeHDMIImageContrast(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->writeContrast(value, sync, msec);
        }

        quint16 SenderCardItem_2nd::readHDMIImageContrast(bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->readContrast(sync, msec);
        }

        quint8 SenderCardItem_2nd::getHDMIImageContrast()
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->getContrast();
        }

        quint16 SenderCardItem_2nd::writeHDMIImageColorTtemperature(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->writeColortemperature(value, sync, msec);
        }

        quint16 SenderCardItem_2nd::readHDMIImageColorTtemperature(bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->readColortemperature(sync, msec);
        }

        quint8 SenderCardItem_2nd::getHDMIImageColorTtemperature()
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->getColortemperature();
        }

        quint16 SenderCardItem_2nd::writeHDMIImageBrightness(const quint8 value, bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->writeBrightness(value, sync, msec);
        }

        quint16 SenderCardItem_2nd::readHDMIImageBrightness(bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->readBrightness(sync, msec);
        }

        quint8 SenderCardItem_2nd::getHDMIImageBrightness()
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->getBrightness();
        }

        quint16 SenderCardItem_2nd::writeHDMIRGBGain(const int rValue, const int gValue, const int bValue, bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            quint16 ret=0;
            if (-3 == rValue+gValue+bValue) {
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

        quint16 SenderCardItem_2nd::readHDMIRGBGain(bool sync, int msec)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->readRGBGain(sync, msec);
        }

        QList<quint8> SenderCardItem_2nd::getHDMIRGBGain()
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->getRGBGain();
        }

        bool SenderCardItem_2nd::registerControl()
        {
            Q_D(SenderCardItem_2nd);
            //创建控制接口
            //创建SenderCard接口
            d->m_SenderCardCtrl = SC::LBLSenderCardFactory<SC::LBLSenderCardAbstract, \
                SC::LBLSenderCardCentralCtrl>::creatSenderCardDevice(&(d->m_detectInfo), this);
            d->m_SenderCardCtrl->checkItemUuid();
            //创建HDMI接口
            d->m_HDMIChip = HDMIChip::LBLHDMIChipFactory<HDMIChip::LBLHDMIChipAbstract, \
                HDMIChip::LBLHDMIChipCentralCtrl>::creatHDMIChipDevice(&(d->m_detectInfo), this);
            //创建MS9570接口
            d->m_MS9570Ctrl = MS9570::MS9570CtrlFactory<MS9570::LBLMS9570Abstract, \
                MS9570::LBLMS9570CentralCtrl>::creatSenderItem(&(d->m_detectInfo), this);
            return true;
        }

        bool SenderCardItem_2nd::dispatcherPackage(const LBLEnginePackage& pack)
        {
            if (pack.isEmpty() || pack.hostName() != this->hostName())
            {
                return false;
            }
            LBLPackage tempPack(pack.data());
            LBLPackage::EDeviceType targetModule = LBLPackage::EDeviceType(tempPack.getSourceDevice());
            switch (targetModule)
            {
            case LBLPackage::EDT_Android:
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


        QByteArray SenderCardItem_2nd::GetEDIDData()
        {
            Q_D(SenderCardItem_2nd);
            if (d->m_HDMIChip) {
                return d->m_HDMIChip->GetEDIDData();
            }
            else {
                return nullptr;
            }
        }

        quint16 SenderCardItem_2nd::writeHDMIEDID(int dataGroupIndex, quint8* pDataBuff,int dataLen)
        {
            Q_D(SenderCardItem_2nd);
            return d->m_HDMIChip->writeHDMIEDID(dataGroupIndex,pDataBuff,dataLen);
        }
    }
}
