#include "LBLAndroidAbstract.h"
#include "LBLAndroidAbstract_p.h"
namespace LBL
{
	namespace Android
	{
		LBLAndroidAbstract::~LBLAndroidAbstract()
		{
			Q_D(LBLAndroidAbstract);
			d->m_packageMgr.unregisterAll();
		}

		LBLAndroidAbstract::LBLAndroidAbstract(QObject* parent) :QObject(parent), d_ptr(new LBLAndroidAbstractPrivate)
		{
			Q_D(LBLAndroidAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		LBLAndroidAbstract::LBLAndroidAbstract(LBLAndroidAbstractPrivate & dd, QObject* parent) :QObject(parent), d_ptr(&dd)
		{
			Q_D(LBLAndroidAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		bool LBLAndroidAbstract::setDetectInfoStruct(SDetectItemInfo *detectInfo)
		{
			Q_ASSERT(detectInfo);
			d_ptr->m_parentItemDetectInfo = detectInfo;
			if (d_ptr->m_parentItemDetectInfo->communType == ECommunicatType::ECT_COM)
			{
				d_ptr->m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_MCU_In_Sender;
			}
			else
			{
				d_ptr->m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_Android;
			}
			return true;
		}

		bool LBLAndroidAbstract::parsingDataFrame(const LBLPackage& pack)
		{
			Q_D(LBLAndroidAbstract);
			return d->m_packageMgr.handle(pack);
		}

	}
}
