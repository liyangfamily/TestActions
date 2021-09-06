/****************************************************************************
**
** This Interface file is part of the Android module of the LBL.
** 这个是LBL中的Android控制抽象类，该模块不对外开放
**
** 该接口文件包含LED系统中Android相关操作,与通信层联系
**
****************************************************************************/
#ifndef CVTE_H_LBLANDROIDABSTRACT
#define CVTE_H_LBLANDROIDABSTRACT
#pragma once

#include "LBLAndroid_Global.h"
#include <QObject>
#include <QString>
#include <QScopedPointer>

#include <LBL_CommunicatEngine/LBLInteCtrlPackage>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_CommunicatEngined.lib")
#else
#pragma comment(lib,"LBL_CommunicatEngine.lib")
#endif // QT_DEBUG
#endif
namespace LBL
{
	namespace Android
	{
		class LBLAndroidAbstractPrivate;
		class LBL_ANDROID_EXPORT LBLAndroidAbstract : public QObject
		{
			Q_DECLARE_PRIVATE(LBLAndroidAbstract)
		public:
			virtual ~LBLAndroidAbstract();

			bool setDetectInfoStruct(SDetectItemInfo *detectInfo);
			virtual bool init() = 0;

			//由发送卡分发数据包
			virtual bool parsingDataFrame(const LBLPackage& pack);

			/*
			* Comments:从本地数据获取版本号
			* Param in:版本类型
			* Param out:
			* @Return void
			*/
			virtual quint16 readAndroidVersion(bool sync, int msec) = 0;
			virtual QString getAndroidVersion() = 0;


			virtual quint16 readVersionNumber(qint64 type, bool sync, int msec) = 0;

			/*
			* Comments:禁止Android进入深度休眠
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeNoSleep(quint8 value, bool sync, int msec) = 0;
			virtual quint16 readNoSleep(bool sync, int msec) = 0;
			virtual quint8 getNoSleep() = 0;

			/*
			* Comments:按键事件
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeKeyEvent(quint8 status, quint16 keyCode, bool sync, int msec) = 0;
			virtual quint16 getKeyEvent_Result() = 0;

			/*
			* Comments:设备名
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeDeviceName(QString name, bool sync, int msec) = 0;
			virtual quint16 readDeviceName(bool sync, int msec) = 0;
			virtual QString getDeviceName() = 0;

			/*********************************************************************************************************
			**测试相关                                                                     
			*********************************************************************************************************/
			/*
			* Comments:回读安卓连接网络设备在线状态  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readNetDeviceOnlineStatus(QString ip, bool sync, int msec) = 0;
			virtual quint16 getNetDevice_Status() = 0;
			virtual QString getNetDevice_IP() = 0;

			/*
			* Comments:回读发送卡网口自回环测试结果  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readSCEthLoopTestResult(bool sync, int msec) = 0;
			virtual quint16 getSCEthLoopTest_Result() = 0;
			virtual quint8  getSCEthLoopTest_EffectiveEthCount() = 0;
			virtual QByteArray  getSCEthLoopTest_ReplyData() = 0;

			/*
			* Comments:回读Android U盘挂载状态  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readUDiskMountingStatus(bool sync, int msec) = 0;
			virtual quint8  getUDiskMounting_Count() = 0;
			virtual QStringList getUDiskMounting_List() = 0;

			/*
			* Comments:请求开始测试OSD测试  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeStartOSDTest(bool sync, int msec) = 0;
			virtual quint8  getOSDTest_WhiteScreenTestResult() = 0;
			virtual quint8 getOSDTest_BlackScreenTestResult() = 0;

			/*
			* Comments:控制继电器开关  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeRelaySwitc(quint8 status, bool sync, int msec) = 0;
			virtual quint16 getRelaySwitc_Result() = 0;
			virtual quint8  getRelaySwitc_Status() = 0;

			/*
			* Comments:进入按键测试  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeEnterKeyTest(quint8 status, bool sync, int msec) = 0;
			virtual quint8  getKeyTest_Result() = 0;

			/*
			* Comments:读取按键测试结果  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readKeyTestResult(bool sync, int msec) = 0;
			virtual quint8  getKeyTestResult_Count() = 0;
			virtual QList<quint16>  getKeyTestResult_List() = 0;

			/*
			* Comments:回读光感元件参数  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readOpticalSensorParam(bool sync, int msec) = 0;
			virtual quint16 getOpticalSensor_Param() = 0;

			/*
			* Comments:回读路由器状态  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readRouterStatus(bool sync, int msec) = 0;
			virtual quint8 getRouter_5GWifiStatus() = 0;
			virtual quint8 getRouter_2_4GWifiStatus() = 0;

			/*
			* Comments:设置安卓网卡MAC地址  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync, int msec) = 0;
			virtual quint16 getNetworkCardMACAddr_Results() = 0;
			virtual quint8  getNetworkCardMACAddr_Flage() = 0;
			virtual QByteArray getNetworkCardMACAddr_MAC() = 0;

			/*
			* Comments:播放测试声音（1KHZ）  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writePlayTestSound_1KHZ(quint8 status, bool sync, int msec) = 0;
			virtual quint16 getPlayTestSound_Results() = 0;
			virtual quint8  getPlayTestSound_Status() = 0;

			/*
			* Comments:测试wifi模块扫描  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeWIFIModuleScanTest(quint8 status, bool sync, int msec) = 0;
			virtual quint16 getWIFIModuleScanTest_Results() = 0;

			/*
			* Comments:回读wifi扫描列表  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readWIFIScanList(bool sync, int msec) = 0;
			virtual quint8  getWIFIScanList_Count() = 0;

			/*
			* Comments:加载功放芯片参数  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readLoadPowerAmplifierChipParam(bool sync, int msec) = 0;
			virtual quint8  getPowerAmplifierChipParam_Results() = 0;
			virtual quint8  getPowerAmplifierChipParam_30Results() = 0;
			virtual quint8  getPowerAmplifierChipParam_31Results() = 0;

			/*
			* Comments:回读发送卡串口自回环测试结果  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readSCCOMLoopTestResult(bool sync, int msec) = 0;
			virtual quint8 getSCCOMLoopTest_INResult() = 0;
			virtual quint8 getSCCOMLoopTest_OUTResult() = 0;

			/*
			* Comments:进入工厂测试模式  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeEnterTestMode(QString key, bool sync, int msec) = 0;
			virtual quint16  getEnterTestMode_Results() = 0;
		protected:
			LBLAndroidAbstract(QObject* parent = 0);
			LBLAndroidAbstract(LBLAndroidAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化

		protected:
			QScopedPointer<LBLAndroidAbstractPrivate> d_ptr;

		};
	}
}
#endif
