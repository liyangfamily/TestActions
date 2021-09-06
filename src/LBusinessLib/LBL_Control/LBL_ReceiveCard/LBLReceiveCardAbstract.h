/****************************************************************************
**
** This Interface file is part of the ReceiveCard module of the LBL.
** 这个是LBL中的ReceiveCard控制抽象类，该模块不对外开放
**
** 该接口文件包含LED系统中ReceiveCard相关操作,与通信层联系
**
****************************************************************************/
#ifndef CVTE_H_LBLRECEIVECARDABSTRACT
#define CVTE_H_LBLRECEIVECARDABSTRACT
#pragma once

#include "LBLReceiveCardGlobal.h"
#include <LBL_Control/LBLReceiveCardStructGlobal> //包含接收卡相关的数据结构
#include <QObject>
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
	namespace RC
	{
		class LBLReceiveCardAbstractPrivate;
		class LBL_RECEIVECARD_EXPORT LBLReceiveCardAbstract :public QObject
		{
			Q_DECLARE_PRIVATE(LBLReceiveCardAbstract)
		public:
			virtual ~LBLReceiveCardAbstract();

			bool setDetectInfoStruct(SDetectItemInfo *detectInfo);
			virtual bool init() = 0;
			//由发送卡分发数据包
			virtual bool parsingDataFrame(const LBLPackage& pack);

			/*********************************************************************************************************
			**寄存器相关- 注意：如果读取函数为异步读取，则无法保证获取到的结果为预期结果
            *********************************************************************************************************/
			virtual quint16 writeFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec);
			virtual QByteArray readFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec);
			virtual QByteArray getFPGARegister();

			virtual quint16 writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec);
			virtual QByteArray readModuleParam(quint8 port, quint8 module, bool sync, int msec);
			virtual QByteArray getModuleParam();

			virtual quint16 writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec);
			virtual QByteArray readDriveICParam(quint8 port, quint8 module, bool sync, int msec);
			virtual QByteArray getDriveICParam();

			virtual quint16 writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec);
			virtual QByteArray readDecodingICParam(quint8 port, quint8 module, bool sync, int msec);
			virtual QByteArray getDecodingICParam();

			virtual quint16 writeSaveRCParamByRegister(quint8 port, quint8 module, bool sync, int msec);

            virtual quint16 writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec);
			virtual quint16 writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec);
			virtual quint16 writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec);

			/*********************************************************************************************************
			**其他
            *********************************************************************************************************/
			virtual quint16 readStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag,bool sync, int msec);
			virtual QList<SRCStatusInfo> getStatusInfo();

			virtual quint16 readMonitorInfo(quint8 portIndex, bool sync, int msec);
			virtual QList<SRCMonitorInfo> getMonitorInfo();

			virtual quint16 writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec);

		protected:
			LBLReceiveCardAbstract(QObject* parent = 0);
			LBLReceiveCardAbstract(LBLReceiveCardAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化

		protected:
			QScopedPointer<LBLReceiveCardAbstractPrivate> d_ptr;
		};
	}
}
#endif
