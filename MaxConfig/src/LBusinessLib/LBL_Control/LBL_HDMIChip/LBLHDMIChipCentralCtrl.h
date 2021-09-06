/****************************************************************************
**
** This Interface file is part of the HDMIChip module of the LBL.
** 这个是LBL中的HDMIChip模块中集控实现文件，该模块不对外开放
**
** 该接口文件包含LED系统中HDMIChip集控相关操作
**
****************************************************************************/
#ifndef CVTE_H_LBLHDMICHIPCENTRALCTRL
#define CVTE_H_LBLHDMICHIPCENTRALCTRL
#pragma once

#include "LBLHDMIChipAbstract.h"

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
	namespace HDMIChip
	{
		template<class AbstractHDMIChip_t, class ConHDMIChip_t>
		class LBLHDMIChipFactory; //前置声明，告诉编译器工厂为模板

		class LBL_HDMICHIP_EXPORT LBLHDMIChipCentralCtrl : public LBLHDMIChipAbstract
		{
			Q_DECLARE_PRIVATE(LBLHDMIChipAbstract)
		public:
			~LBLHDMIChipCentralCtrl();

			virtual quint16 writeVolume(quint8 value, bool sync, int msec) override;
			virtual quint16 readVolume(bool sync, int msec) override;
			virtual quint8  getVolume() override;

			virtual quint16 writeBypass(quint8 value, bool sync, int msec) override;
			virtual quint16 readBypass(bool sync, int msec) override;
			virtual quint8  getBypasss() override;

			virtual quint16 writeRatio(quint8 value, bool sync, int msec) override;
			virtual quint16 readRatio(bool sync, int msec) override;
			virtual quint8  getRatio() override;

			virtual quint16 writeSource(quint8 value, bool sync, int msec) override;
			virtual quint16 readSource(bool sync, int msec) override;
			virtual quint8  getSource() override;

			virtual quint16 writeContrast(quint8 value, bool sync, int msec) override;
			virtual quint16 readContrast(bool sync, int msec) override;
			virtual quint8  getContrast() override;

			virtual quint16 writeColortemperature(quint8 value, bool sync, int msec) override;
			virtual quint16 readColortemperature(bool sync, int msec) override;
			virtual quint8  getColortemperature() override;

			virtual quint16 writeBrightness(quint8 value, bool sync, int msec) override;
			virtual quint16 readBrightness(bool sync, int msec) override;
			virtual quint8  getBrightness() override;

			virtual quint16 writeRGain(quint8 value, bool sync, int msec) override;
			virtual quint16 readRGain(bool sync, int msec) override;
			virtual quint8  getRGain() override;

			virtual quint16 writeGGain(quint8 value, bool sync, int msec) override;
			virtual quint16 readGGain(bool sync, int msec) override;
			virtual quint8  getGGain() override;

			virtual quint16 writeBGain(quint8 value, bool sync, int msec) override;
			virtual quint16 readBGain(bool sync, int msec) override;
			virtual quint8  getBGain() override;

			virtual quint16 writeRGBGain(quint8 rValue, quint8 gValue, quint8 bValue, bool sync, int msec) override;
			virtual quint16 readRGBGain(bool sync, int msec) override;
			virtual QList<quint8>  getRGBGain() override;

			virtual quint16 writeResolution(quint32 width, quint32 height, quint8 refreshRate, bool sync, int msec) override;
			virtual quint16 readResolution(bool sync, int msec) override;
			virtual QSize  getResolution() override;
			virtual quint8  getRefreshRate() override;

			virtual quint16 readCombinationInfo(bool sync, int msec) override;

			virtual quint16 writeSceneMode(quint8 value, bool sync, int msec) override;
			virtual quint16 readSceneMode(bool sync, int msec) override;
			virtual quint8  getSceneMode() override;

			virtual quint16 writeSplitScreenMode(quint8 value, bool sync, int msec) override;
			virtual quint16 readSplitScreenMode(bool sync, int msec) override;
			virtual quint8  getSplitScreenMode() override;
		protected:
			bool init();
			virtual void registerCallBack();
			quint16 onParseWriteVolume(const QByteArray& data);
			quint16 onParseReadVolume(const QByteArray& data);
			quint16 onParseWriteBypass(const QByteArray& data);
			quint16 onParseReadBypass(const QByteArray& data);
			quint16 onParseWriteRatio(const QByteArray& data);
			quint16 onParseReadRatio(const QByteArray& data);
			quint16 onParseWriteSource(const QByteArray& data);
			quint16 onParseReadSource(const QByteArray& data);
			quint16 onParseWriteContrast(const QByteArray& data);
			quint16 onParseReadContrast(const QByteArray& data);
			quint16 onParseWriteColortemperature(const QByteArray& data);
			quint16 onParseReadColortemperature(const QByteArray& data);
			quint16 onParseWriteBrightness(const QByteArray& data);
			quint16 onParseReadBrightness(const QByteArray& data);
			quint16 onParseWriteRGain(const QByteArray& data);
			quint16 onParseReadRGain(const QByteArray& data);
			quint16 onParseWriteGGain(const QByteArray& data);
			quint16 onParseReadGGain(const QByteArray& data);
			quint16 onParseWriteBGain(const QByteArray& data);
			quint16 onParseReadBGain(const QByteArray& data);
			quint16 onParseWriteRGBGain(const QByteArray& data);
			quint16 onParseReadRGBGain(const QByteArray& data);
			quint16 onParseWriteResolution(const QByteArray& data);
			quint16 onParseReadResolution(const QByteArray& data);
			quint16 onParseReadCombinationInfo(const QByteArray& data);
			quint16 onParseWriteSceneMode(const QByteArray& data);
			quint16 onParseReadSceneMode(const QByteArray& data);
			quint16 onParseWriteSplitScreenMode(const QByteArray& data);
			quint16 onParseReadSplitScreenMode(const QByteArray& data);
		protected:
			LBLHDMIChipCentralCtrl(QObject* parent = 0); //禁用外部创建
			LBLHDMIChipCentralCtrl(LBLHDMIChipAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
			friend class LBLHDMIChipFactory<LBLHDMIChipAbstract, LBLHDMIChipCentralCtrl>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
		};
	}
}

#endif
