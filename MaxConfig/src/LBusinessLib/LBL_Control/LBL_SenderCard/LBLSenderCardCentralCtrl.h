/****************************************************************************
**
** This Interface file is part of the SenderCard module of the LBL.
** 这个是LBL中的SenderCard模块中集控实现文件，该模块不对外开放
**
** 该接口文件包含LED系统中SenderCard集控相关操作
**
****************************************************************************/
#ifndef CVTE_H_LBLSENDERCARDCENTRALCTRL
#define CVTE_H_LBLSENDERCARDCENTRALCTRL
#pragma once

#include "LBLSenderCardAbstract.h"

namespace LBL
{
	namespace SC
	{
		template<class AbstractSenderCard_t, class ConSenderCard_t>
		class LBLSenderCardFactory; //前置声明，告诉编译器工厂为模板

		class LBL_SENDERCARD_EXPORT LBLSenderCardCentralCtrl : public LBLSenderCardAbstract
		{
			Q_DECLARE_PRIVATE(LBLSenderCardAbstract)

		public:
			~LBLSenderCardCentralCtrl();

			/*********************************************************************************************************
			**寄存器相关 - 注意：如果读取函数为异步读取，则无法保证获取到的结果为预期结果
            *********************************************************************************************************/
			virtual quint16 writeFPGARegister(quint32 addr, QByteArray value, bool sync, int msec)override;
			virtual QByteArray readFPGARegister(quint32 addr, quint16 len, bool sync, int msec)override;
			virtual QByteArray getFPGARegister()override;

			virtual QByteArray readFPGAVersion(bool sync, int msec) override;
			virtual QString getFPGAVersion() override;

			virtual quint16 writeFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec) override;
			virtual QByteArray readFPGAEthLoad(bool sync, int msec) override;
			virtual QList<LBLSPort> getFPGAEthLoad() override;

			virtual quint16 readMCUAppVersion(bool sync, int msec)override;
			virtual QString getMCUAppVersion()override;
			virtual quint16 readMCUBootVersion(bool sync, int msec)override;
			virtual QString getMCUBootVersion()override;

			virtual QByteArray readEthLoopTest(bool sync, int msec)override;
			virtual quint8  getEthLoopTest_Count()override;
			virtual QMap<quint8, float> getEthLoopTest_BitErrRate()override;

			virtual quint16 writeSelfTestModeOpen(quint8 value, bool sync, int msec)override;
			virtual QByteArray readSelfTestModeOpen(bool sync, int msec)override;
			virtual quint8 getSelfTestModeOpen()override;

			virtual quint16 writeSelfTestModeStart(quint8 value, bool sync, int msec)override;
			virtual QByteArray readSelfTestModeStart(bool sync, int msec)override;
			virtual quint8 getSelfTestModeStart()override;

			virtual quint16 writeSelfTestMode(quint8 mode, bool sync, int msec)override;
			virtual QByteArray readSelfTestMode(bool sync, int msec)override;
			virtual quint8 getSelfTestMode()override;

			virtual quint16 writeSelfTestModeSpeed(quint8 speed, bool sync, int msec)override;
			virtual QByteArray readSelfTestModeSpeed(bool sync, int msec)override;
			virtual quint8 getSelfTestModeSpeed()override;
			/*********************************************************************************************************
			**连接关系相关
            *********************************************************************************************************/
			virtual quint16 sendConnectionBuffer(bool sync, int msec) override;
			virtual quint16 readConnectionBuffer(bool sync = true, int msec = 3000) override;//默认同步读取
			virtual QByteArray getConnectionBuffer() override;
			/*********************************************************************************************************
			**其他
            *********************************************************************************************************/
			virtual quint16 writeSaveSCParam(bool sync, int msec)override;

			virtual quint16 writeBrightness(int value, bool sync, int msec)override;
			virtual quint16 readBrightness(bool sync, int msec)override;
			virtual int  getBrightness()override;

			virtual quint16 writeSenderCardUuid(quint8 idType, QUuid uuid, bool sync, int msec)override;
			virtual quint16 readSenderCardUuid(bool sync, int msec)override;
			virtual QUuid  getSenderCardUuid()override;
			virtual quint8  getSenderCardUuidType()override;

			/*********************************************************************************************************
			**发送卡寄存器--一些开关量
			*********************************************************************************************************/

			virtual quint16 writeScreenBlack(quint8 value, bool sync, int msec)override;
			virtual QByteArray readScreenBlack(bool sync, int msec)override;
			virtual quint8 getScreenBlack()override;

			virtual quint16 writeScreenLock(quint8 value, bool sync, int msec)override;
			virtual QByteArray readScreenLock(bool sync, int msec)override;
			virtual quint8 getScreenLock()override;

			virtual quint16 writeZoomMode(quint8 value, bool sync, int msec)override;
			virtual QByteArray readZoomMode(bool sync, int msec)override;
			virtual quint8 getZoomMode()override;

			virtual quint16 writeZoomSize(QSize value, bool sync, int msec)override;
			virtual QByteArray readZoomSize(bool sync, int msec)override;
			virtual QSize getZoomSize()override;

			virtual quint16 writeErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec) override;
			virtual QByteArray readErrorBitRateStatisticalSwitch(bool sync, int msec) override;
			virtual quint8 getErrorBitRateStatisticalSwitch() override;

			virtual quint16 writeCorrectionSwitch(quint8 value, bool sync, int msec) override;
			virtual QByteArray readCorrectionSwitch(bool sync, int msec) override;
			virtual quint8 getCorrectionSwitch() override;

			virtual quint16 writeSpreadSpectrumSwitch(quint8 value, bool sync, int msec) override;
			virtual QByteArray readSpreadSpectrumSwitch(bool sync, int msec) override;
			virtual quint8 getSpreadSpectrumSwitch() override;

			virtual quint16 write24BitGammaSwitch(quint8 value, bool sync, int msec) override;
			virtual QByteArray read24BitGammaSwitch(bool sync, int msec) override;
			virtual quint8 get24BitGammaSwitch() override;

			virtual quint16 writeProtocolType(quint8 value, bool sync, int msec)override;
			virtual QByteArray readProtocolType(bool sync, int msec)override;
			virtual quint8  getProtocolType()override;

		protected:
            bool init() override;
			virtual void registerCallBack();
			quint16 onParseWriteFPGARegister(const QByteArray& data);
			quint16 onParseReadFPGARegister(const QByteArray& data);
			quint16 onParseReadMCUAppVersion(const QByteArray& data);
			quint16 onParseReadMCUBootVersion(const QByteArray& data);
			quint16 onParseWriteSaveSCParam(const QByteArray& data);
			quint16 onParseWriteBrightness(const QByteArray& data);
			quint16 onParseReadBrightness(const QByteArray& data);
			quint16 onParseWriteSenderCardUuid(const QByteArray& data);
			quint16 onParseReadSenderCardUuid(const QByteArray& data);
			quint16 onParseSendConnection(const QByteArray& data);
			quint16 onParseReadConnection(const QByteArray& data);

		protected:
			LBLSenderCardCentralCtrl(QObject* parent = 0); //禁用外部创建
			LBLSenderCardCentralCtrl(LBLSenderCardAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
			friend class LBLSenderCardFactory<LBLSenderCardAbstract, LBLSenderCardCentralCtrl>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
		};

	}
}

#endif
