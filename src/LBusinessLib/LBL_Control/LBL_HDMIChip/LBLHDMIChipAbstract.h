/****************************************************************************
**
** This Interface file is part of the HDMIChip module of the LBL.
** 这个是LBL中的HDMIChip控制抽象类，该模块不对外开放
**
** 该接口文件包含LED系统中HDMIChip相关操作,与通信层联系
**
****************************************************************************/
#ifndef CVTE_H_LBLHDMICHIPABSTRACT
#define CVTE_H_LBLHDMICHIPABSTRACT
#pragma once

#include "LBLHDMIChipGlobal.h"
#include <QObject>
#include <QSize>
#include <QScopedPointer>
#include <LBL_CommunicatEngine/LBLPackage>

namespace LBL
{
    namespace HDMIChip
    {
        class LBLHDMIChipAbstractPrivate;
        class LBL_HDMICHIP_EXPORT LBLHDMIChipAbstract :public QObject
        {
            Q_DECLARE_PRIVATE(LBLHDMIChipAbstract)
        public:
            virtual ~LBLHDMIChipAbstract();

            bool setDetectInfoStruct(SDetectItemInfo *detectInfo);
            bool parsingDataFrame(const LBLPackage& pack);

            virtual bool init() = 0;

            virtual quint16 writeVolume(quint8 value, bool sync, int msec);
            virtual quint16 readVolume(bool sync, int msec);
            virtual quint8  getVolume();

            virtual quint16 writeBypass(quint8 value, bool sync, int msec);
            virtual quint16 readBypass(bool sync, int msec);
            virtual quint8  getBypasss();

            virtual quint16 writeRatio(quint8 value, bool sync, int msec);
            virtual quint16 readRatio(bool sync, int msec);
            virtual quint8  getRatio();

            virtual quint16 writeSource(quint8 value, bool sync, int msec);
            virtual quint16 readSource(bool sync, int msec);
            virtual quint8  getSource();

            virtual quint16 writeContrast(quint8 value, bool sync, int msec);
            virtual quint16 readContrast(bool sync, int msec);
            virtual quint8  getContrast();

            virtual quint16 writeColortemperature(quint8 value, bool sync, int msec);
            virtual quint16 readColortemperature(bool sync, int msec);
            virtual quint8  getColortemperature();

            virtual quint16 writeBrightness(quint8 value, bool sync, int msec);
            virtual quint16 readBrightness(bool sync, int msec);
            virtual quint8  getBrightness();

            virtual quint16 writeRGain(quint8 value, bool sync, int msec);
            virtual quint16 readRGain(bool sync, int msec);
            virtual quint8  getRGain();

            virtual quint16 writeGGain(quint8 value, bool sync, int msec);
            virtual quint16 readGGain(bool sync, int msec);
            virtual quint8  getGGain();

            virtual quint16 writeBGain(quint8 value, bool sync, int msec);
            virtual quint16 readBGain(bool sync, int msec);
            virtual quint8  getBGain();

            virtual quint16 writeRGBGain(quint8 rValue, quint8 gValue, quint8 bValue, bool sync, int msec);
            virtual quint16 readRGBGain(bool sync, int msec);
            virtual QList<quint8>  getRGBGain();

            virtual quint16 writeResolution(quint32 width, quint32 height,quint8 refreshRate, bool sync, int msec);
            virtual quint16 readResolution(bool sync, int msec);
            virtual QSize  getResolution();
            virtual quint8  getRefreshRate();

            virtual quint16 readCombinationInfo(bool sync, int msec);

            virtual quint16 writeSceneMode(quint8 value, bool sync, int msec);
            virtual quint16 readSceneMode(bool sync, int msec);
            virtual quint8  getSceneMode();

            virtual quint16 writeSplitScreenMode(quint8 value, bool sync, int msec);
            virtual quint16 readSplitScreenMode(bool sync, int msec);
            virtual quint8  getSplitScreenMode();

             virtual QByteArray GetEDIDData();
             virtual quint16 writeHDMIEDID(int dataGroupIndex, quint8* pDataBuff,int dataLen);
        protected:
            LBLHDMIChipAbstract(QObject* parent = 0);
            LBLHDMIChipAbstract(LBLHDMIChipAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化

        protected:
            QScopedPointer<LBLHDMIChipAbstractPrivate> d_ptr;
        };
    }
}
#endif
