#include "LBLMS9570Abstract.h"
#include "LBLMS9570Abstract_p.h"

namespace LBL
{
    namespace MS9570
    {
        LBLMS9570Abstract::LBLMS9570Abstract(QObject* parent) :
            QObject(parent), d_ptr(new LBLMS9570AbstractPrivate)
        {
            Q_D(LBLMS9570Abstract);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
        }

        LBLMS9570Abstract::LBLMS9570Abstract(LBLMS9570AbstractPrivate & dd,QObject* parent) :
            QObject(parent), d_ptr(&dd)
        {
            Q_D(LBLMS9570Abstract);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
        }

        LBLMS9570Abstract::~LBLMS9570Abstract()
        {
            d_ptr->m_packageMgr.unregisterAll();
        }

        bool LBLMS9570Abstract::setDetectInfoStruct(SDetectItemInfo * detectInfo)
        {
            Q_ASSERT(detectInfo);
            d_ptr->m_parentItemDetectInfo = detectInfo;
            if (detectInfo->communType == ECommunicatType::ECT_COM&& detectInfo->senderCardClass == ESenderCardClass::ESC_2nd_GZ) {
                d_ptr->m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_MCU_In_Sender;
            }
            return true;
        }

        bool LBLMS9570Abstract::parsingDataFrame(const LBLPackage& pack)
        {
            Q_D(LBLMS9570Abstract);
            return d->m_packageMgr.handle(pack);
        }

        QByteArray LBLMS9570Abstract::GetEDIDData()
        {
            Q_D(LBLMS9570Abstract);
            return d->q_ptr->GetEDIDData();
        }

        quint16	LBLMS9570Abstract::writeHDMIEDID(int index, quint8* pdata,int dataLen)
        {
             Q_D(LBLMS9570Abstract);
            return d->q_ptr->writeHDMIEDID(index,pdata,dataLen);
        }
    }
}
