/****************************************************************************
**
** This Interface file is part of the SenderCard module of the LBL.
** 这个是LBL中的SenderCard控制抽象类，该模块不对外开放
**
** 该接口文件包含LED系统中SenderCard相关操作,与通信层联系
**
****************************************************************************/
#ifndef CVTE_H_LBLSENDERCARDABSTRACT
#define CVTE_H_LBLSENDERCARDABSTRACT
#pragma once

#include "LBLSenderCardGlobal.h"
#include <LBL_Control/LBLSenderCardStructGlobal> //包含发送卡相关的数据结构
#include <QObject>
#include <QScopedPointer>

#include <LBL_Core/LBLConnection>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_Cored.lib")
#else
#pragma comment(lib,"LBL_Core.lib")
#endif
#endif

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
	namespace SC
	{
		class LBLSenderCardAbstractPrivate;
		class LBL_SENDERCARD_EXPORT LBLSenderCardAbstract :public QObject
		{
			Q_DECLARE_PRIVATE(LBLSenderCardAbstract)
		public:
			virtual ~LBLSenderCardAbstract();

			bool setDetectInfoStruct(SDetectItemInfo *detectInfo);
			virtual bool init() = 0;

			virtual void checkItemUuid();
			//由发送卡分发数据包
			virtual bool parsingDataFrame(const LBLPackage& pack);

			/*********************************************************************************************************
			**寄存器相关 - 注意：如果读取函数为异步读取，则无法保证获取到的结果为预期结果
            *********************************************************************************************************/
			virtual quint16 writeFPGARegister(quint32 addr, QByteArray value, bool sync, int msec) ;
			virtual QByteArray readFPGARegister(quint32 addr, quint16 len, bool sync, int msec) ;
			virtual QByteArray getFPGARegister() ;

			virtual QByteArray readFPGAVersion(bool sync, int msec);
			virtual QString getFPGAVersion();

			virtual quint16 writeFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec);
			virtual QByteArray readFPGAEthLoad(bool sync, int msec);
			virtual QList<LBLSPort> getFPGAEthLoad();

			virtual quint16 readMCUAppVersion(bool sync, int msec) ;
			virtual QString getMCUAppVersion() ;
			virtual quint16 readMCUBootVersion(bool sync, int msec) ;
			virtual QString getMCUBootVersion() ;

			virtual QByteArray readEthLoopTest(bool sync, int msec);
			virtual quint8  getEthLoopTest_Count();
			virtual QMap<quint8, float> getEthLoopTest_BitErrRate();

			virtual quint16 writeSelfTestModeOpen(quint8 value, bool sync, int msec);
			virtual QByteArray readSelfTestModeOpen(bool sync, int msec);
			virtual quint8 getSelfTestModeOpen();

			virtual quint16 writeSelfTestModeStart(quint8 value, bool sync, int msec);
			virtual QByteArray readSelfTestModeStart(bool sync, int msec);
			virtual quint8 getSelfTestModeStart();

			virtual quint16 writeSelfTestMode(quint8 mode, bool sync, int msec);
			virtual QByteArray readSelfTestMode(bool sync, int msec);
			virtual quint8 getSelfTestMode();

			virtual quint16 writeSelfTestModeSpeed(quint8 speed, bool sync, int msec);
			virtual QByteArray readSelfTestModeSpeed(bool sync, int msec);
			virtual quint8 getSelfTestModeSpeed();
			/*********************************************************************************************************
			**连接关系相关
            *********************************************************************************************************/
			virtual quint16 sendConnectionBuffer(bool sync = true, int msec = 1500);
			virtual quint16 readConnectionBuffer(bool sync = true, int msec = 3000); //默认同步读取
			virtual QByteArray getConnectionBuffer();
			/*********************************************************************************************************
			**其他
            *********************************************************************************************************/
			virtual quint16 writeSaveSCParam(bool sync, int msec) ;

			virtual quint16 writeBrightness(int value, bool sync, int msec) ;
			virtual quint16 readBrightness(bool sync, int msec) ;
			virtual int  getBrightness() ;

			virtual quint16 writeSenderCardUuid(quint8 idType, QUuid uuid, bool sync, int msec) ;
			virtual quint16 readSenderCardUuid(bool sync, int msec) ;
			virtual QUuid  getSenderCardUuid() ;
			virtual quint8  getSenderCardUuidType() ;


			/*********************************************************************************************************
			**发送卡寄存器--一些开关量                                                                     
			*********************************************************************************************************/

			virtual quint16 writeScreenBlack(quint8 value, bool sync, int msec);
			virtual QByteArray readScreenBlack(bool sync, int msec);
			virtual quint8 getScreenBlack();

			virtual quint16 writeScreenLock(quint8 value, bool sync, int msec);
			virtual QByteArray readScreenLock(bool sync, int msec);
			virtual quint8 getScreenLock();

			virtual quint16 writeZoomMode(quint8 value, bool sync, int msec);
			virtual QByteArray readZoomMode(bool sync, int msec);
			virtual quint8 getZoomMode();

			virtual quint16 writeZoomSize(QSize value, bool sync, int msec);
			virtual QByteArray readZoomSize(bool sync, int msec);
			virtual QSize getZoomSize();

			virtual quint16 writeErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec);
			virtual QByteArray readErrorBitRateStatisticalSwitch(bool sync, int msec);
			virtual quint8 getErrorBitRateStatisticalSwitch();

			virtual quint16 writeCorrectionSwitch(quint8 value, bool sync, int msec);
			virtual QByteArray readCorrectionSwitch(bool sync, int msec);
			virtual quint8 getCorrectionSwitch();

			virtual quint16 writeSpreadSpectrumSwitch(quint8 value, bool sync, int msec);
			virtual QByteArray readSpreadSpectrumSwitch(bool sync, int msec);
			virtual quint8 getSpreadSpectrumSwitch();

			virtual quint16 write24BitGammaSwitch(quint8 value, bool sync, int msec);
			virtual QByteArray read24BitGammaSwitch(bool sync, int msec);
			virtual quint8 get24BitGammaSwitch();

			virtual quint16 writeProtocolType(quint8 value, bool sync, int msec);
			virtual QByteArray readProtocolType(bool sync, int msec);
			virtual quint8  getProtocolType();
		protected:
			LBLSenderCardAbstract(QObject* parent = 0);
			LBLSenderCardAbstract(LBLSenderCardAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化

		protected:
			QScopedPointer<LBLSenderCardAbstractPrivate> d_ptr;
		};
	}
}
#endif
