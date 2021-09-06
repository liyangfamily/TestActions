/****************************************************************************
**
** This Interface file is part of the ReceiveCard module of the LBL.
** 这个是LBL中的ReceiveCard模块中集控实现文件，该模块不对外开放
**
** 该接口文件包含LED系统中ReceiveCard集控相关操作
**
****************************************************************************/
#ifndef CVTE_H_LBLRECEIVECARDCENTRALCTRL
#define CVTE_H_LBLRECEIVECARDCENTRALCTRL
#pragma once

#include "LBLReceiveCardAbstract.h"

namespace LBL
{
	namespace RC
	{
		template<class AbstractReceiveCard_t, class ConReceiveCard_t>
		class LBLReceiveCardFactory; //前置声明，告诉编译器工厂为模板

		class LBL_RECEIVECARD_EXPORT LBLReceiveCardCentralCtrl : public LBLReceiveCardAbstract
		{
			Q_DECLARE_PRIVATE(LBLReceiveCardAbstract)

		public:
			~LBLReceiveCardCentralCtrl();

			/*********************************************************************************************************
			**寄存器相关 注意：如果读取函数为异步读取，则无法保证获取到的结果为预期结果
            *********************************************************************************************************/
			virtual quint16 writeFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec) override;
			virtual QByteArray readFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec) override;
			virtual QByteArray getFPGARegister() override;

			virtual quint16 writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec) override;
			virtual QByteArray readModuleParam(quint8 port, quint8 module, bool sync, int msec) override;
			virtual QByteArray getModuleParam() override;

			virtual quint16 writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec) override;
			virtual QByteArray readDriveICParam(quint8 port, quint8 module, bool sync, int msec) override;
			virtual QByteArray getDriveICParam() override;

			virtual quint16 writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec) override;
			virtual QByteArray readDecodingICParam(quint8 port, quint8 module, bool sync, int msec) override;
			virtual QByteArray getDecodingICParam() override;

			virtual quint16 writeSaveRCParamByRegister(quint8 port, quint8 module, bool sync, int msec) override;

            virtual quint16 writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec) override;
			virtual quint16 writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec) override;
			virtual quint16 writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec) override;

			/*********************************************************************************************************
			**其他
            *********************************************************************************************************/
			virtual quint16 readStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec)override;
			virtual QList<SRCStatusInfo> getStatusInfo() override;

			virtual quint16 readMonitorInfo(quint8 portIndex, bool sync, int msec) override;
			virtual QList<SRCMonitorInfo> getMonitorInfo() override;

            virtual quint16 writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec) override;


		protected:
            bool init() override;
			virtual void registerCallBack();
			quint16 onParseWriteFPGARegister(const QByteArray& data);
			quint16 onParseReadFPGARegister(const QByteArray& data);
			quint16 onParseReadStatusInfo(const QByteArray& data);
			quint16 onParseReadMonitorInfo(const QByteArray& data);
			quint16 onParseWriteSaveRCParam(const QByteArray& data);
		protected:
			LBLReceiveCardCentralCtrl(QObject* parent = 0); //禁用外部创建
			LBLReceiveCardCentralCtrl(LBLReceiveCardAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
			friend class LBLReceiveCardFactory<LBLReceiveCardAbstract, LBLReceiveCardCentralCtrl>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
		};

	}
}

#endif
