#pragma once
/****************************************************************************
**
** This Interface file is part of the Android module of the LBusinessLib.
** 这个是LBusinessLib中的Android模块接口文件，该模块不对外开放
**
** 该接口文件为LED系统Android的抽象发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBLANDROIDABSTRACT_P
#define CVTE_H_LBLANDROIDABSTRACT_P
#pragma once

#include "LBLAndroidAbstract.h"
#include <LBL_CommunicatEngine/LBLPackageManager>

namespace LBL
{
	namespace Android
	{
		class LBLAndroidAbstract;
		class LBLAndroidAbstractPrivate
		{
			Q_DECLARE_PUBLIC(LBLAndroidAbstract)
		public:
			LBLAndroidAbstractPrivate() {}
			~LBLAndroidAbstractPrivate()
			{
				qDebug("~LBLAndroidAbstractPrivate()\n");
			}
			LBLAndroidAbstract *q_ptr;

		public:
			//公有数据定义
			QString m_androidVersion;
			quint8 m_noSleep = 0;

			quint16 m_keyEvent_Result = 0;

			QString m_deviceName;

			quint16 m_netDeviceOnline_Status = 0;
			QString m_netDevice_IP;

			quint16 m_scEthLoopTest_Result = 0;
			quint8 m_scEthLoopTest_EffectiveEthCount = 0;
			QByteArray m_scEthLoopTest_ReplyData;

			quint8 m_uDiskMounting_Count = 0;
			QStringList m_uDiskMounting_List;

			quint8 m_OSDTest_WhiteScreenTestResult = 0;
			quint8 m_OSDTest_BlackScreenTestResult = 0;

			quint16 m_RelaySwitc_Result = 0;
			quint8 m_RelaySwitc_Status = 0;

			quint8 m_EnterKeyTest_Result = 0;

			quint8 m_KeyTestResult_Count = 0;
			QList<quint16>  m_KeyTestResult_List;

			quint16 m_OpticalSensor_Param = 0;

			quint8 m_Router_5GWifiStatus = 0;
			quint8 m_Router_2_4GWifiStatus = 0;

			quint16 m_NetworkCardMACAddr_Results = 0;
			quint8  m_NetworkCardMACAddr_Flage = 0;
			QByteArray m_NetworkCardMACAddr_MAC;

			quint16 m_PalyTestSound_Results = 0;
			quint8  m_PalyTestSound_Status = 0;

			quint16 m_WIFIModuleScanTest_Results = 0;

			quint8  m_WIFIScanList_Count = 0;

			quint8  m_PowerAmplifierChipParam_Results = 0;
			quint8  m_PowerAmplifierChipParam_30Results = 0;
			quint8  m_PowerAmplifierChipParam_31Results = 0;

			quint16 m_scCOMLoopTest_Result = 0;
			quint8 m_scCOMLoopTest_INResult = 0;
			quint8 m_scCOMLoopTest_OUTResult = 0;

			quint16 m_EnterTestMode_Results = 0;
			//发送卡的探卡信息指针
			SDetectItemInfo* m_parentItemDetectInfo = nullptr;
			//负责数据包的分发
			LBLPackageManager m_packageMgr;
			LBLInteCtrlPackage::EDeviceType m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_Android;
		};
	}
}
#endif
