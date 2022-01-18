#include "LBLHDMIChipCentralCtrl.h"
#include "LBLHDMIChipAbstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>
#include <QFile>
#include "LBL_Core/LBLUIHelper.h"

namespace LBL
{
    namespace HDMIChip
    {

        LBLHDMIChipCentralCtrl::LBLHDMIChipCentralCtrl(QObject *parent) :
            LBLHDMIChipAbstract(parent)
        {
            Q_D(LBLHDMIChipAbstract);
            d->q_ptr = this;
        }

        LBLHDMIChipCentralCtrl::LBLHDMIChipCentralCtrl(LBLHDMIChipAbstractPrivate & dd, QObject * parent) :
            LBLHDMIChipAbstract(dd, parent)
        {
            Q_D(LBLHDMIChipAbstract);
            d->q_ptr = this;
        }

        LBLHDMIChipCentralCtrl::~LBLHDMIChipCentralCtrl()
        {
        }

        quint16 LBLHDMIChipCentralCtrl::writeVolume(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_volume = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceVolume pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readVolume(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceVolume pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getVolume()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_volume;
        }

        quint16 LBLHDMIChipCentralCtrl::writeBypass(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_bypass = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceByPass pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readBypass(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceByPass pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getBypasss()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_bypass;
        }

        quint16 LBLHDMIChipCentralCtrl::writeRatio(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_ratio = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceRatio pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readRatio(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceRatio pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getRatio()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_ratio;
        }

        quint16 LBLHDMIChipCentralCtrl::writeSource(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_source = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSource pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readSource(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSource pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getSource()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_source;
        }

        quint16 LBLHDMIChipCentralCtrl::writeContrast(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_contrast = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceContrast pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readContrast(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceContrast pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getContrast()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_contrast;
        }

        quint16 LBLHDMIChipCentralCtrl::writeColortemperature(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_colortemperature = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceColortemperature pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readColortemperature(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceColortemperature pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getColortemperature()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_colortemperature;
        }

        quint16 LBLHDMIChipCentralCtrl::writeBrightness(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_brightness = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceBrightness pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readBrightness(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceBrightness pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getBrightness()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_brightness;
        }

        quint16 LBLHDMIChipCentralCtrl::writeRGain(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_rGain = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceRGain pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readRGain(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceRGain pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getRGain()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_rGain;
        }

        quint16 LBLHDMIChipCentralCtrl::writeGGain(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_gGain = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceGGain pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readGGain(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceGGain pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getGGain()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_gGain;
        }

        quint16 LBLHDMIChipCentralCtrl::writeBGain(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_bGain = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceBGain pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readBGain(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceBGain pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getBGain()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_bGain;
        }

        quint16 LBLHDMIChipCentralCtrl::writeRGBGain(quint8 rValue, quint8 gValue, quint8 bValue, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_rGain = rValue;
            d->m_cacheData.m_gGain = gValue;
            d->m_cacheData.m_bGain = bValue;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceRGBGain pack(rValue, gValue, bValue);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readRGBGain(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceRGBGain pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        QList<quint8> LBLHDMIChipCentralCtrl::getRGBGain()
        {
            Q_D(LBLHDMIChipAbstract);
            QList<quint8> tempList;
            tempList.append(d->m_realData.m_rGain);
            tempList.append(d->m_realData.m_gGain);
            tempList.append(d->m_realData.m_bGain);
            return tempList;
        }

        quint16 LBLHDMIChipCentralCtrl::writeResolution(quint32 width, quint32 height, quint8 refreshRate, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_resolutionSize.setWidth(width);
            d->m_cacheData.m_resolutionSize.setHeight(height);
            d->m_cacheData.m_refreshRate = refreshRate;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceResolution pack(d->m_cacheData.m_resolutionSize, refreshRate);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readResolution(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceResolution pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        QSize LBLHDMIChipCentralCtrl::getResolution()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_resolutionSize;
        }

        quint8 LBLHDMIChipCentralCtrl::getRefreshRate()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_refreshRate;
        }

        quint16 LBLHDMIChipCentralCtrl::readCombinationInfo(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceCombinationInfo pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::writeSceneMode(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_sceneMode = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceSceneMode pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readSceneMode(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceSceneMode pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getSceneMode()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_sceneMode;
        }

        quint16 LBLHDMIChipCentralCtrl::writeSplitScreenMode(quint8 value, bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_cacheData.m_splitScreenMode = value;
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_WriteVideoSourceSplitScreenMode pack(value);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint16 LBLHDMIChipCentralCtrl::readSplitScreenMode(bool sync, int msec)
        {
            Q_D(LBLHDMIChipAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageInteCtrl_ReadVideoSourceSplitScreenMode pack;
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBL_DECLARE_COMMANDSEND(d, pack)
        }

        quint8 LBLHDMIChipCentralCtrl::getSplitScreenMode()
        {
            Q_D(LBLHDMIChipAbstract);
            return d->m_realData.m_splitScreenMode;
        }

        bool LBLHDMIChipCentralCtrl::init()
        {
            registerCallBack();
            return true;
        }

        void LBLHDMIChipCentralCtrl::registerCallBack()
        {
            Q_D(LBLHDMIChipAbstract);
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceVolume(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteVolume, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceVolume(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadVolume, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceByPass(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteBypass, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceByPass(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadBypass, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceRatio(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteRatio, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceRatio(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadRatio, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSource(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteSource, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSource(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadSource, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceContrast(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteContrast, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceContrast(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadContrast, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceColortemperature(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteColortemperature, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceColortemperature(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadColortemperature, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceBrightness(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteBrightness, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceBrightness(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadBrightness, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceRGain(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteRGain, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceRGain(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadRGain, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceGGain(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteGGain, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceGGain(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadGGain, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceBGain(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteBGain, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceBGain(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadBGain, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceRGBGain(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteRGBGain, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceRGBGain(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadRGBGain, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceResolution(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteResolution, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceResolution(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadResolution, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceCombinationInfo(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadCombinationInfo, this, std::placeholders::_1));

            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceSceneMode(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteSceneMode, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceSceneMode(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadSceneMode, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceSplitScreenMode(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseWriteSplitScreenMode, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceSplitScreenMode(),
                std::bind(&LBLHDMIChipCentralCtrl::onParseReadSplitScreenMode, this, std::placeholders::_1));
        }

        quint16 LBLHDMIChipCentralCtrl::onParseWriteVolume(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceVolume pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_volume = d->m_cacheData.m_volume;
            }
            return ret;
        }

        quint16 LBLHDMIChipCentralCtrl::onParseReadVolume(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceVolume pack(data);
            d->m_realData.m_volume = pack.getVolume();
            return LBLPackage::EOR_Success;
        }

        quint16 LBLHDMIChipCentralCtrl::onParseWriteBypass(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceByPass pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_bypass = d->m_cacheData.m_bypass;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadBypass(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceByPass pack(data);
            d->m_realData.m_bypass = pack.getBypass();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteRatio(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceRatio pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_ratio = d->m_cacheData.m_ratio;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadRatio(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceRatio pack(data);
            d->m_realData.m_ratio = pack.getRatio();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteSource(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSource pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_source = d->m_cacheData.m_source;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadSource(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSource pack(data);
            d->m_realData.m_source = pack.getSource();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteContrast(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceContrast pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_contrast = d->m_cacheData.m_contrast;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadContrast(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceContrast pack(data);
            d->m_realData.m_contrast = pack.getContrast();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteColortemperature(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceColortemperature pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_colortemperature = d->m_cacheData.m_colortemperature;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadColortemperature(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceColortemperature pack(data);
            d->m_realData.m_colortemperature = pack.getColortemperature();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteBrightness(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceBrightness pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_brightness = d->m_cacheData.m_brightness;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadBrightness(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceBrightness pack(data);
            d->m_realData.m_brightness = pack.getBrightness();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteRGain(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceRGain pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_rGain = d->m_cacheData.m_rGain;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadRGain(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceRGain pack(data);
            d->m_realData.m_rGain = pack.getRGain();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteGGain(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceGGain pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_gGain = d->m_cacheData.m_gGain;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadGGain(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceGGain pack(data);
            d->m_realData.m_gGain = pack.getGGain();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteBGain(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceBGain pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_bGain = d->m_cacheData.m_bGain;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadBGain(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceBGain pack(data);
            d->m_realData.m_bGain = pack.getBGain();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteRGBGain(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_WriteVideoSourceRGBGain pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_rGain = d->m_cacheData.m_rGain;
                d->m_realData.m_gGain = d->m_cacheData.m_gGain;
                d->m_realData.m_bGain = d->m_cacheData.m_bGain;
            }
            return ret;
        }

        quint16 LBLHDMIChipCentralCtrl::onParseReadRGBGain(const QByteArray& data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceRGBGain pack(data);
            d->m_realData.m_rGain = pack.getRGain();
            d->m_realData.m_gGain = pack.getGGain();
            d->m_realData.m_bGain = pack.getBGain();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteResolution(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);
            LBLPackageInteCtrl_WriteVideoSourceResolution pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_resolutionSize = d->m_cacheData.m_resolutionSize;
                d->m_realData.m_refreshRate = d->m_cacheData.m_refreshRate;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadResolution(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceResolution pack(data);
            d->m_realData.m_resolutionSize = pack.getResolution();
            d->m_realData.m_refreshRate = pack.getRefreshRate();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadCombinationInfo(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceCombinationInfo pack(data);
            d->m_realData.m_brightness = pack.getBrightness();
            d->m_realData.m_colortemperature = pack.getColortemperature();
            d->m_realData.m_ratio = pack.getRatio();
            d->m_realData.m_source = pack.getSource();
            d->m_realData.m_volume = pack.getVolume();
            d->m_realData.m_contrast = pack.getContrast();
            d->m_realData.m_sceneMode = pack.getSceneMode();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteSceneMode(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);
            LBLPackageInteCtrl_WriteVideoSourceSceneMode pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_sceneMode = d->m_cacheData.m_sceneMode;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadSceneMode(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceSceneMode pack(data);
            d->m_realData.m_sceneMode = pack.getSceneMode();
            return LBLPackage::EOR_Success;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseWriteSplitScreenMode(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);
            LBLPackageInteCtrl_WriteVideoSourceSplitScreenMode pack(data);
            quint16 ret = pack.getOperationResult();
            if (ret == LBLPackage::EOR_Success)
            {
                d->m_realData.m_splitScreenMode = d->m_cacheData.m_splitScreenMode;
            }
            return ret;
        }
        quint16 LBLHDMIChipCentralCtrl::onParseReadSplitScreenMode(const QByteArray & data)
        {
            Q_D(LBLHDMIChipAbstract);

            LBLPackageInteCtrl_ReadVideoSourceSplitScreenMode pack(data);
            d->m_realData.m_splitScreenMode = pack.getSplitScreenMode();
            return LBLPackage::EOR_Success;
        }

        QByteArray LBLHDMIChipCentralCtrl::GetEDIDData()
        {
            QString fileName = LBLUIHelper::appParamDataLocation()+"//EDID//2nd_Default_EDID.bin";

            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly))
            {
                return nullptr;
            }

            QByteArray data = file.readAll();
            file.close();

            return data;
        }
    }
}

