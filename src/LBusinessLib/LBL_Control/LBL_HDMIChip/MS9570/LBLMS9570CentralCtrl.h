/****************************************************************************
**
** This Interface file is part of the MS9570 module of the LBL.
** 这个是LBL中的MS9570模块中集控实现文件，该模块不对外开放
**
** 该接口文件包含LED系统中MS9570集控相关操作
**
****************************************************************************/
#ifndef CVTE_H_LBL_MS9570CTRLCENTRALCTRL
#define CVTE_H_LBL_MS9570CTRLCENTRALCTRL
#pragma once

#include "LBLMS9570Abstract.h"
#include "LBL_MS9570_Struct.h"
#include <LBL_CommunicatEngine/LBLInteCtrlPackage>
namespace LBL
{
	namespace MS9570
	{
		template<class AbstractMS9570Ctrl_t, class ConMS9570Ctrl_t> 
		class MS9570CtrlFactory; //前置声明，告诉编译器工厂为模板

		class LBL_HDMICHIP_EXPORT LBLMS9570CentralCtrl : public LBLMS9570Abstract
		{
			Q_DECLARE_PRIVATE(LBLMS9570Abstract)
		public:
			~LBLMS9570CentralCtrl();

			virtual quint16 readVersion(bool sync, int msec) override;
			virtual QString getVersion() override;

			virtual quint16 writeReset(bool sync, int msec) override;

			virtual quint16	writeColorMode(quint8 value, bool sync, int msec) override;
			virtual quint16	readColorMode(bool sync, int msec) override;
			virtual quint8	getColorMode() override;

			virtual quint16 writeRGBGain(quint8 rValue, quint8 gValue, quint8 bValue, bool sync, int msec) override;
			virtual quint16 readRGBGain(bool sync, int msec) override;
			virtual QList<quint8>  getRGBGain() override;

			virtual quint16	writeBackLight(quint8 value, bool sync, int msec) override;
			virtual quint16	readBackLight(bool sync, int msec) override;
			virtual quint8	getBackLight() override;

			virtual quint16	writeInputSource(quint8 value, bool sync, int msec) override;
			virtual quint16	readInputSource(bool sync, int msec) override;
			virtual quint8	getInputSource() override;

			virtual quint16	writeImageRatio(quint8 value, bool sync, int msec) override;
			virtual quint16	readImageRatio(bool sync, int msec) override;
			virtual quint8	getImageRatio() override;

			virtual quint16	writeContrast(quint8 value, bool sync, int msec) override;
			virtual quint16	readContrast(bool sync, int msec) override;
			virtual quint8	getContrast() override;

			virtual quint16	writeVolume(quint8 value, bool sync, int msec) override;
			virtual quint16	readVolume(bool sync, int msec) override;
			virtual quint8	getVolume() override;

			virtual quint16	writeBaypass(quint8 value, bool sync, int msec) override;
			virtual quint16	readBaypass(bool sync, int msec) override;
			virtual quint8	getBaypass() override;

			virtual quint16	writeOutputResolutionInfo(quint16 param1, quint16 param2, bool sync, int msec) override;
			virtual quint16	readOutputResolutionInfo(bool sync, int msec) override;
			virtual QSize	getOutputResolutionInfo() override;

			virtual quint16	readInputResolutionInfo(bool sync, int msec) override;
			virtual QSize	getInputResolutionInfo() override;

			virtual quint16	writeHDMIEDID(int index, QByteArray pdata) override;

		protected:
			bool init() override;
			virtual void registerCallBack();

			quint16 syncSend(QByteArray sendData, QByteArray & replyData, bool sync, int msec);
		protected:
			LBLMS9570CentralCtrl(QObject* parent = 0); //禁用外部创建
			LBLMS9570CentralCtrl(LBLMS9570AbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
			friend class MS9570CtrlFactory<LBLMS9570Abstract, LBLMS9570CentralCtrl>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
		};
	}
}
#endif
