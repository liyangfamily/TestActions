/****************************************************************************
**
** This Interface file is part of the Android module of the LBL.
** 这个是LBL中的Android模块中集控实现文件，该模块不对外开放
**
** 该接口文件包含LED系统中Android集控相关操作
**
****************************************************************************/
#ifndef CVTE_H_LBLANDROIDCENTRALCTRL
#define CVTE_H_LBLANDROIDCENTRALCTRL
#pragma once

#include "LBLAndroidAbstract.h"

namespace LBL
{
	namespace Android
	{
		template<class AbstractAndroid_t, class ConAndroid_t>
		class LBLAndroidFactory; //前置声明，告诉编译器工厂为模板

		class LBL_ANDROID_EXPORT LBLAndroidCentralCtrl : public LBLAndroidAbstract
		{
			Q_DECLARE_PRIVATE(LBLAndroidAbstract)
		public:
			~LBLAndroidCentralCtrl();

			/*
			* Comments:从本地数据获取版本号
			* Param in:版本类型
			* Param out:
			* @Return void
			*/
			virtual quint16 readAndroidVersion(bool sync, int msec) override;
			virtual QString getAndroidVersion();

			virtual quint16 readVersionNumber(qint64 type, bool sync, int msec) override;

			
			virtual quint16 writeNoSleep(quint8 value, bool sync, int msec) override;
			virtual quint16 readNoSleep(bool sync, int msec) override;
			virtual quint8 getNoSleep() override;

			/*
			* Comments:按键事件
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeKeyEvent(quint8 status, quint16 keyCode, bool sync, int msec) override;
			virtual quint16 getKeyEvent_Result() override;

			/*
			* Comments:设备名
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeDeviceName(QString name, bool sync, int msec) override;
			virtual quint16 readDeviceName(bool sync, int msec) override;
			virtual QString getDeviceName() override;

			/*********************************************************************************************************
			**测试相关
			*********************************************************************************************************/
			/*
			* Comments:回读安卓连接网络设备在线状态  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readNetDeviceOnlineStatus(QString ip, bool sync, int msec) override;
			virtual quint16 getNetDevice_Status() override;
			virtual QString getNetDevice_IP() override;

			/*
			* Comments:回读发送卡网口自回环测试结果  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readSCEthLoopTestResult(bool sync, int msec) override;
			virtual quint16 getSCEthLoopTest_Result() override;
			virtual quint8  getSCEthLoopTest_EffectiveEthCount() override;
			virtual QByteArray  getSCEthLoopTest_ReplyData() override;

			/*
			* Comments:回读Android U盘挂载状态  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readUDiskMountingStatus(bool sync, int msec) override;
			virtual quint8  getUDiskMounting_Count() override;
			virtual QStringList getUDiskMounting_List() override;

			/*
			* Comments:请求开始测试OSD测试  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeStartOSDTest(bool sync, int msec) override;
			virtual quint8  getOSDTest_WhiteScreenTestResult() override;
			virtual quint8 getOSDTest_BlackScreenTestResult() override;

			/*
			* Comments:控制继电器开关  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeRelaySwitc(quint8 status, bool sync, int msec) override;
			virtual quint16 getRelaySwitc_Result() override;
			virtual quint8  getRelaySwitc_Status() override;

			/*
			* Comments:进入按键测试  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeEnterKeyTest(quint8 status, bool sync, int msec) override;
			virtual quint8  getKeyTest_Result() override;

			/*
			* Comments:读取按键测试结果  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readKeyTestResult(bool sync, int msec) override;
			virtual quint8  getKeyTestResult_Count() override;
			virtual QList<quint16>  getKeyTestResult_List() override;

			/*
			* Comments:回读光感元件参数  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readOpticalSensorParam(bool sync, int msec) override;
			virtual quint16 getOpticalSensor_Param() override;

			/*
			* Comments:回读路由器状态  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readRouterStatus(bool sync, int msec) override;
			virtual quint8 getRouter_5GWifiStatus() override;
			virtual quint8 getRouter_2_4GWifiStatus() override;

			/*
			* Comments:设置安卓网卡MAC地址  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync, int msec) override;
			virtual quint16 getNetworkCardMACAddr_Results() override;
			virtual quint8  getNetworkCardMACAddr_Flage() override;
			virtual QByteArray getNetworkCardMACAddr_MAC() override;

			/*
			* Comments:播放测试声音（1KHZ）  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writePlayTestSound_1KHZ(quint8 status, bool sync, int msec) override;
			virtual quint16 getPlayTestSound_Results() override;
			virtual quint8  getPlayTestSound_Status() override;

			/*
			* Comments:测试wifi模块扫描  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeWIFIModuleScanTest(quint8 status, bool sync, int msec) override;
			virtual quint16 getWIFIModuleScanTest_Results() override;

			/*
			* Comments:回读wifi扫描列表  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readWIFIScanList(bool sync, int msec) override;
			virtual quint8  getWIFIScanList_Count() override;

			/*
			* Comments:加载功放芯片参数  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readLoadPowerAmplifierChipParam(bool sync, int msec) override;
			virtual quint8  getPowerAmplifierChipParam_Results() override;
			virtual quint8  getPowerAmplifierChipParam_30Results() override;
			virtual quint8  getPowerAmplifierChipParam_31Results() override;

			/*
			* Comments:回读发送卡串口自回环测试结果  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 readSCCOMLoopTestResult(bool sync, int msec) override;
			virtual quint8 getSCCOMLoopTest_INResult() override;
			virtual quint8 getSCCOMLoopTest_OUTResult() override;

			/*
			* Comments:进入工厂测试模式  注意：如果异步读取，则无法保证获取到的结果为预期结果
			* Param in:
			* Param out:
			* @Return void
			*/
			virtual quint16 writeEnterTestMode(QString key, bool sync, int msec)override;
			virtual quint16  getEnterTestMode_Results()override;
		protected:
			bool init() override;
			virtual void registerCallBack();
			quint16 onParseReadVersionNumber(const QByteArray& data);
			quint16 onParseReadNoSleep(const QByteArray& data);
			quint16 onParseWriteKeyEvent(const QByteArray& data);
			quint16 onParseWriteDeviceName(const QByteArray& data);
			quint16 onParseReadDeviceName(const QByteArray& data);
			quint16 onParseReadNetDeviceOnlineStatus(const QByteArray& data);
			quint16 onParseReadSCEthLoopTestResult(const QByteArray& data);
			quint16 onParseReadUDiskMountingStatus(const QByteArray& data);
			quint16 onParseWriteStartOSDTest(const QByteArray& data);
			quint16 onParseWriteRelaySwitc(const QByteArray& data);
			quint16 onParseWriteEnterKeyTest(const QByteArray& data);
			quint16 onParseReadKeyTestResult(const QByteArray& data);
			quint16 onParseReadOpticalSensorParam(const QByteArray& data);
			quint16 onParseReadRouterStatus(const QByteArray& data);
			quint16 onParseWriteNetworkCardMACAddr(const QByteArray& data);
			quint16 onParseWritePalyTestSound_1KHZ(const QByteArray& data);
			quint16 onParseWriteWIFIModuleScanTest(const QByteArray& data);
			quint16 onParseReadWIFIScanList(const QByteArray& data);
			quint16 onParseReadLoadPowerAmplifierChipParam(const QByteArray& data);
			quint16 onParseReadCOMLoopTestResults(const QByteArray& data);
			quint16 onParseWriteEnterTestMode(const QByteArray& data);
		protected:
			LBLAndroidCentralCtrl(QObject* parent = 0); //禁用外部创建
			LBLAndroidCentralCtrl(LBLAndroidAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
			friend class LBLAndroidFactory<LBLAndroidAbstract, LBLAndroidCentralCtrl>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
		};

	}
}

#endif