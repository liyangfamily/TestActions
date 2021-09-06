/****************************************************************************
**
** This Interface file is part of the HDMI module of the LBL.
** 这个是LBL中的MS9570控制抽象类，该模块不对外开放
**
** 该接口文件包含LED系统中MS9570相关操作,与通信层联系
**
****************************************************************************/
#ifndef CVTE_H_LBL_ABSTRACTMS9570CTRL
#define CVTE_H_LBL_ABSTRACTMS9570CTRL
#pragma once

#include "../LBLHDMIChipGlobal.h"
#include <QObject>
#include <QSize>
#include <QScopedPointer>
#include <LBL_CommunicatEngine/LBLPackage>
namespace LBL
{
	namespace MS9570
	{
		class LBLMS9570AbstractPrivate;
		class LBL_HDMICHIP_EXPORT LBLMS9570Abstract :public QObject
		{
			Q_DECLARE_PRIVATE(LBLMS9570Abstract)
		public:
			virtual ~LBLMS9570Abstract(); 

			bool setDetectInfoStruct(SDetectItemInfo *detectInfo);
			bool parsingDataFrame(const LBLPackage& pack);

			virtual bool init() = 0;

			virtual quint16 readVersion(bool sync, int msec) = 0;
			virtual QString getVersion() = 0;

			virtual quint16 writeReset(bool sync, int msec) = 0;

			virtual quint16	writeColorMode(quint8 value, bool sync, int msec)=0;
			virtual quint16	readColorMode(bool sync, int msec)=0;
			virtual quint8	getColorMode()=0;

			virtual quint16 writeRGBGain(quint8 rValue, quint8 gValue, quint8 bValue, bool sync, int msec)=0;
			virtual quint16 readRGBGain(bool sync, int msec)=0;
			virtual QList<quint8>  getRGBGain()=0; 
			
			virtual quint16	writeBackLight(quint8 value, bool sync, int msec)=0;
			virtual quint16	readBackLight(bool sync, int msec)=0;
			virtual quint8	getBackLight()=0;

			virtual quint16	writeInputSource(quint8 value, bool sync, int msec)=0;
			virtual quint16	readInputSource(bool sync, int msec)=0;
			virtual quint8	getInputSource()=0;

			virtual quint16	writeImageRatio(quint8 value, bool sync, int msec)=0;
			virtual quint16	readImageRatio(bool sync, int msec)=0;
			virtual quint8	getImageRatio()=0;

			virtual quint16	writeContrast(quint8 value, bool sync, int msec)=0;
			virtual quint16	readContrast(bool sync, int msec)=0;
			virtual quint8	getContrast()=0;

			virtual quint16	writeVolume(quint8 value, bool sync, int msec)=0;
			virtual quint16	readVolume(bool sync, int msec)=0;
			virtual quint8	getVolume()=0;

			virtual quint16	writeBaypass(quint8 value, bool sync, int msec)=0;
			virtual quint16	readBaypass(bool sync, int msec)=0;
			virtual quint8	getBaypass()=0;

			virtual quint16	writeOutputResolutionInfo(quint16 param1, quint16 param2, bool sync, int msec)=0;
			virtual quint16	readOutputResolutionInfo(bool sync, int msec)=0;
			virtual QSize	getOutputResolutionInfo()=0;

			virtual quint16	readInputResolutionInfo(bool sync, int msec)=0;
			virtual QSize	getInputResolutionInfo()=0;

			virtual quint16	writeHDMIEDID(int index, QByteArray pdata)=0;
		protected:
			LBLMS9570Abstract(QObject* parent = 0);
			LBLMS9570Abstract(LBLMS9570AbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化

		protected:
			QScopedPointer<LBLMS9570AbstractPrivate> d_ptr;
		};
	}
}
#endif
