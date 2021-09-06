#include "LAPI_Control/LAPIControl.h"

/*!
\class

\inmodule

\brief The file is API of LBusinessLib
 All of The dll and lib (In order of generation):
    LBL_Core
    LBL_CommunicatEngine
    LBL_Android
    LBL_ReceiveCard
    LBL_MS9570
    LBL_NT68400
    LBL_SenderCard
    LBL_SenderCardItem
    LAPI_Control
\code <How To Use The LBusinessLib>
1\ 首先需要在工程属性或者配置文件中添加附加包含目录，必须添加LBusinessLib的include文件夹，
    如果还有使用其他模块的内容，还需要添加其他模块的文件夹，例如API模块：include\LAPI_Control；
    再添加对应的附加依赖库，将lib文件添加进去。

2\开始使用
    #include <LAPIControl>
    #ifdef QT_DEBUG
    #pragma comment(lib,"LAPI_Controld.lib")
    #else
    #pragma comment(lib,"LAPI_Control.lib")
    #endif // QT_DEBUG

    TestDemo::TestDemo(QWidget *parent) : QWidget(parent), ui(new Ui::TestDemo)
    {
        //启动探卡服务
        LAPI::StartDetectServer();
        //绑定探卡结束信号槽，用于更新发送卡列表
        connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_DetectComplit, this, &frmUdpClient::slot_DetectComplit);
        //本界面监听亮度读取命令,在frmUdpClient::event(QEvent * e)中处理
        gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadBrightness(), this);
        //异步读亮度
        LAPI::ReadBrightness();
        //同步写亮度，超时1.5s
        LAPI::WriteBrightness(98, true, 1500);
    }

    TestDemo::~TestDemo()
    {
        //负责退出前的清理工作
        LAPI::ReadyExit();
        int maxWait = 0;
        //等待工作线程退出以及资源释放
        while (!LAPI::CanExit())
        {
            QCoreApplication::processEvents();
            QThread::currentThread()->msleep(200);
            maxWait++;
            if (maxWait >= 150)
            {
                if (QMessageBox::information(0, tr("Confire Exit"),
                    tr("There are still some clients alive in the server. continue waiting?"),
                    QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
                    maxWait = 0;
                else
                    break;
            }
        }
    }

    bool TestDemo::event(QEvent * e)
    {
        if (e->type() == LBLPackageEvent::s_disPatcherPackage_eventType)
        {
            LBLPackageEvent *tempE = static_cast<LBLPackageEvent*>(e);
            if (tempE->cmdNum() == LBLInteCtrlPackage::EC_Read_VideoSourceBrightness)
            {
                tempE->protocolNum();
                LBLPackageInteCtrl_ReadBrightness pack(tempE->package().data());
                ui->horizontalSlider->setValue(pack.getBrightness());
            }
        }
        return QWidget::event(e);
    }

    void TestDemo::slot_DetectComplit()
    {
        QList<LBL::SCItem::LBLAbstractSCItem*> itemList;
        LAPI::GetAllItemList(itemList);
    }
\endcode

\note:

*/

using namespace LBL::SCItem;

namespace LAPI
{
    EResult LAPI_Stdcall StartDetectServer(quint16 detectIntervalTime, quint16 everyDetectIntervalTime, quint16 everyDetectCount)
    {
        return gSCItemMgr->startDetectServer(detectIntervalTime, everyDetectIntervalTime, everyDetectCount) == true ? EResult::ER_Success : EResult::ER_Fail;
    }

    EResult LAPI_Stdcall StoptDetectServer()
    {
        gSCItemMgr->stopDetectServer();
        return EResult::ER_Success;
    }

    QList<LBL::SCItem::LBLAbstractSCItem*> LAPI_Stdcall GetUsingItemList()
    {
        return gSCItemMgr->getUsingItemList();
    }

    QList<LBL::SCItem::LBLAbstractSCItem*> LAPI_Stdcall GetAllItemList()
    {
        return gSCItemMgr->getAllItemList();
    }

    LBL::SCItem::LBLAbstractSCItem* LAPI_Stdcall GetItemByInternalUuid(QUuid internalUuid)
    {
        return gSCItemMgr->getItemByInternalUuid(internalUuid);
    }

    EResult LAPI_Stdcall SetUsingItemByInternalUuid(QUuid internalUuid)
    {
        LBL::SCItem::LBLAbstractSCItem* item = nullptr;
        item = GetItemByInternalUuid(internalUuid);
        if (item)
        {
            QList<LBL::SCItem::LBLAbstractSCItem*> itemList;
            itemList.append(item);
            gSCItemMgr->setUsingItemList(itemList);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ConnectItemByInternalUuid(QUuid internalUuid)
    {
        return gSCItemMgr->connectItem(internalUuid)?EResult::ER_Success:EResult::ER_Fail;
    }

    EResult LAPI_Stdcall DisconnectItemByInternalUuid(QUuid internalUuid)
    {
        return gSCItemMgr->disconnectItem(internalUuid)?EResult::ER_Success:EResult::ER_Fail;
    }

    EResult LAPI_Stdcall ReadyExit()
    {
        //反注册分发器监听者
        gDispatcher->unregisterAllDispatcherPackage();
        gDispatcher->unregisterAllTransitObject();
        //停止探卡服务
        gSCItemMgr->stopDetectServer();
        //通信库准备退出
        gCluster->readyToExit();
        //取消所有升级任务
        for (auto i : gSCItemMgr->getAllItemList()) {
            i->cancelUpgrade();
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall CanExit()
    {
        for (auto i : gSCItemMgr->getAllItemList()) {
            if (i->isUpgrading()) {
                return EResult(0);
            }
        }
        return EResult(gCluster->canExit());
    }

    EResult LAPI_Stdcall WriteBrightness(const int value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeBrightness(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadBrightness(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->readBrightness(sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall WriteSCFPGARegister(quint32 addr, QByteArray value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->writeSCFPGARegister(addr, value, sync, msec);
        }
        return EResult::ER_Success;
    }

    QByteArray LAPI_Stdcall ReadSCFPGARegister(quint32 addr, quint16 len, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCFPGARegister(addr, len, sync, msec);
        }
        return QByteArray();
    }

    QByteArray LAPI_Stdcall GetSCFPGARegister()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCFPGARegister();
            break;
        }
        return QByteArray();
    }

    QByteArray LAPI_Stdcall ReadSCFPGAVersion(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCFPGAVersion(sync, msec);
        }
        return QByteArray();
    }

    QString LAPI_Stdcall GetSCFPGAVersion()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCFPGAVersion();
            break;
        }
        return QString();
    }

    EResult LAPI_Stdcall WriteSCFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCFPGAEthLoad(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    QByteArray LAPI_Stdcall ReadSCFPGAEthLoad(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCFPGAEthLoad(sync, msec);
        }
        return QByteArray();
    }

    QList<LBLSPort> LAPI_Stdcall GetSCFPGAEthLoad()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCFPGAEthLoad();
        }
        return QList<LBLSPort>();
    }

    EResult LAPI_Stdcall ReadMCUAppVersion(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->readMCUAppVersion(sync, msec);
        }
        return EResult::ER_Success;
    }

    QString LAPI_Stdcall GetMCUAppVersion()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getMCUAppVersion();
            break;
        }
        return QString();
    }

    EResult LAPI_Stdcall ReadMCUBootVersion(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->readMCUBootVersion(sync, msec);
        }
        return EResult::ER_Success;
    }

    QString LAPI_Stdcall GetMCUBootVersion()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getMCUBootVersion();
            break;
        }
        return QString();
    }

    EResult LAPI_Stdcall WriteSaveSCParam(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSaveSCParam(sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall WriteConnection(LBLConnection * value, bool sync, int msec)
    {
        if (!value) {
            return EResult::ER_InDataNullptr;
        }
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeConnection(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadConnection(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->readConnection(sync, msec);
        }
        return EResult::ER_Success;
    }

    LBLConnection* LAPI_Stdcall GetConnection()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getConnection();
        }
        return nullptr;
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCSelfTestMode(UI::EPictureTestMode mode, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCSelfTestMode(mode, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCSelfTestMode(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCSelfTestMode(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT UI::EPictureTestMode LAPI_Stdcall GetSCSelfTestMode()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (UI::EPictureTestMode)i->getSCSelfTestMode();
        }
        return UI::EPictureTestMode();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCSelfTestModeSpeed(UI::EPictureTestModeSpeed speed, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCSelfTestModeSpeed(speed, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCSelfTestModeSpeed(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCSelfTestModeSpeed(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT UI::EPictureTestModeSpeed LAPI_Stdcall GeSCtSelfTestModeSpeed()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (UI::EPictureTestModeSpeed)i->getSCSelfTestModeSpeed();
        }
        return UI::EPictureTestModeSpeed();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCScreenBlack(quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCScreenBlack(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCScreenBlack(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCScreenBlack(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCScreenBlack()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCScreenBlack();
        }
        return quint8();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCScreenLock(quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCScreenLock(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCScreenLock(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCScreenLock(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCScreenLock()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCScreenLock();
        }
        return quint8();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCZoomMode(quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCZoomMode(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCZoomMode(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCZoomMode(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCZoomMode()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCZoomMode();
        }
        return quint8();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCZoomSize(QSize value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCZoomSize(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCZoomSize(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCZoomSize(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT QSize LAPI_Stdcall GetSCZoomSize()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCZoomSize();
        }
        return QSize();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCErrorBitRateStatisticalSwitch(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCErrorBitRateStatisticalSwitch(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCErrorBitRateStatisticalSwitch(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCErrorBitRateStatisticalSwitch()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCErrorBitRateStatisticalSwitch();
        }
        return quint8();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCCorrectionSwitch(quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCCorrectionSwitch(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCCorrectionSwitch(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCCorrectionSwitch(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCCorrectionSwitch()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCCorrectionSwitch();
        }
        return quint8();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCSpreadSpectrumSwitch(quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCSpreadSpectrumSwitch(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCSpreadSpectrumSwitch(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCSpreadSpectrumSwitch(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCSpreadSpectrumSwitch()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCSpreadSpectrumSwitch();
        }
        return quint8();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSC24BitGammaSwitch(quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSC24BitGammaSwitch(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSC24BitGammaSwitch(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSC24BitGammaSwitch(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSC24BitGammaSwitch()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSC24BitGammaSwitch();
        }
        return quint8();
    }

    ILAPI_CONTROL_EXPORT EResult WriteSCProtocolType(quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeSCProtocolType(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCProtocolType(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readSCProtocolType(sync, msec);
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCProtocolType()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getSCProtocolType();
        }
        return quint8();
    }

    EResult WriteRCFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->writeRCFPGARegister(port,module,addr, value, sync, msec);
        }
        return EResult::ER_Success;
    }

    QByteArray ReadRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->readRCFPGARegister(port,module,addr, len, sync, msec);
        }
        return QByteArray();
    }

    QByteArray GetRCFPGARegister()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getRCFPGARegister();
        }
        return QByteArray();
    }

    EResult WriteModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeModuleParam(port,module,value, sync, msec);
        }
        return EResult::ER_Success;
    }

    QByteArray ReadModuleParam(quint8 port, quint8 module, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->readModuleParam(port,module, sync, msec);
        }
        return QByteArray();
    }

    QByteArray GetModuleParam()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getModuleParam();
        }
        return QByteArray();
    }

    EResult WriteDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeDriveICParam(port,module,value, sync, msec);
        }
        return EResult::ER_Success;
    }

    QByteArray ReadDriveICParam(quint8 port, quint8 module, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->readDriveICParam(port,module, sync, msec);
        }
        return QByteArray();
    }

    QByteArray GetDriveICParam()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getDriveICParam();
        }
        return QByteArray();
    }

    EResult WriteDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeDecodingICParam(port,module,value, sync, msec);
        }
        return EResult::ER_Success;
    }

    QByteArray ReadDecodingICParam(quint8 port, quint8 module, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->readDecodingICParam(port,module, sync, msec);
        }
        return QByteArray();
    }

    QByteArray GetDecodingICParam()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getDecodingICParam();
        }
        return QByteArray();
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeCalibrationDataErase(port, module, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeCalibrationDataSave(port, module, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult WriteCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeCalibrationDataReload(port,module, sync, msec);
        }
        return EResult::ER_Success;
    }

    QList<LBL::RC::SRCStatusInfo> ReadRCStatusInfo(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->readRCStatusInfo(sync, msec);
        }
        return QList<LBL::RC::SRCStatusInfo>();
    }

    QList<LBL::RC::SRCStatusInfo> ReadRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->readRCStatusInfo(portStart, portCount, moduleStart, moduleCount, lengthFlag, sync, msec);
        }
        return QList<LBL::RC::SRCStatusInfo>();
    }

    QList<LBL::RC::SRCStatusInfo> GetRCStatusInfo()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getRCStatusInfo();
        }
        return QList<LBL::RC::SRCStatusInfo>();

    }

    ILAPI_CONTROL_EXPORT QList<LBL::RC::SRCMonitorInfo>LAPI_Stdcall ReadRCMonitorInfo(quint8 portIndex, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->readRCMonitorInfo(portIndex, sync, msec);
        }
        return QList<LBL::RC::SRCMonitorInfo>();
    }

    ILAPI_CONTROL_EXPORT QList<LBL::RC::SRCMonitorInfo>LAPI_Stdcall GetRCMonitorInfo()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getRCMonitorInfo();
        }
        return QList<LBL::RC::SRCMonitorInfo>();
    }

    EResult WriteSaveRCParam(quint8 port, quint16 module, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeSaveRCParam(port,module, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall WriteHDMIByPassStatus(const quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->writeHDMIByPassStatus(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadHDMIByPassStatus(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->readHDMIByPassStatus(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetHDMIByPassStatus()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getHDMIByPassStatus();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteHDMIImageRatio(const quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->writeHDMIImageRatio(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadHDMIImageRatio(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->readHDMIImageRatio(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetHDMIImageRatio()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getHDMIImageRatio();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteHDMIInputSource(const quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->writeHDMIInputSource(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadHDMIInputSource(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->readHDMIInputSource(sync, msec);
        }
        return EResult::ER_Success;
    }

    UI::EInputSource LAPI_Stdcall GetHDMIInputSource()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (UI::EInputSource)i->getHDMIInputSource();
        }
        return UI::EInputSource();
    }

    EResult LAPI_Stdcall WriteHDMIImageContrast(const quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->writeHDMIImageContrast(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadHDMIImageContrast(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->readHDMIImageContrast(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetHDMIImageContrast()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getHDMIImageContrast();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteHDMIImageColorTtemperature(const quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->writeHDMIImageColorTtemperature(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadHDMIImageColorTtemperature(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->readHDMIImageColorTtemperature(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetHDMIImageColorTtemperature()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getHDMIImageColorTtemperature();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteHDMIImageBrightness(const quint8 value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->writeHDMIImageBrightness(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadHDMIImageBrightness(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->readHDMIImageBrightness(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetHDMIImageBrightness()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getHDMIImageBrightness();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteHDMIRGBGain(const int rValue, const int gValue, const int bValue, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->writeHDMIRGBGain(rValue, gValue, bValue, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadHDMIRGBGain(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            i->readHDMIRGBGain(sync, msec);
        }
        return EResult::ER_Success;
    }

    QList<quint8> LAPI_Stdcall GetHDMIRGBGain()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->getHDMIRGBGain();
        }
        return QList<quint8>();
    }

    bool LAPI_Stdcall IsUpgradeSend()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->isUpgradeSend();
        }
        return true;
    }

    quint16 LAPI_Stdcall UpgradingFileType()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->upgradingFileType();
        }
        return LBLFileTransferPackage::EFileType::EFT_SelectFile;
    }

    quint8 LAPI_Stdcall UpgradingPortIndex()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->upgradingPortIndex();
        }
        return 0;
    }

    quint16 LAPI_Stdcall UpgradingModuleIndex()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->upgradingModuleIndex();
        }
        return 0;
    }

    bool LAPI_Stdcall IsUpgradeStarted()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->isUpgradeStarted();
        }
        return false;
    }

    bool LAPI_Stdcall IsUpgrading()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->isUpgrading();
        }
        return false;
    }

    bool LAPI_Stdcall IsUpgradeFinished()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->isUpgradeFinished();
        }
        return true;
    }

    bool LAPI_Stdcall CancelUpgrade()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->cancelUpgrade();
        }
        return true;
    }

    EResult LAPI_Stdcall UpgradeResult()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->upgradeResult();
        }
        return EResult::ER_NoSenderCardSelect;
    }

    ILAPI_CONTROL_EXPORT QFuture<quint16> LAPI_Stdcall UpgradeFuture()
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return i->upgradeFuture();
        }
        return QFuture<quint16>();
    }

    EResult LAPI_Stdcall UpgradeFile(quint16 fileType, QString fileName, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->upgradeFile(sync, msec, fileType, fileName);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall UpgradeFile(quint16 fileType, QString fileName, quint8 portIndex, quint16 moduleIndex, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->upgradeFile(sync, msec, fileType, fileName, portIndex, moduleIndex);
        }
        return EResult::ER_Success;
    }
    EResult LAPI_Stdcall UpgradeFile(quint16 fileType, QByteArray data, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->upgradeFile(sync, msec, fileType, data);
        }
        return EResult::ER_Success;
    }
    EResult LAPI_Stdcall UpgradeFile(quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList())
        {
            return (EResult)i->upgradeFile(sync, msec, fileType, data, portIndex, moduleIndex);
        }
        return EResult::ER_Success;
    }



    EResult LAPI_Stdcall ReadAndroidVersion(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()){
            return (EResult)i->readAndroidVersion(sync, msec);
        }
        return EResult::ER_Success;
    }

    QString LAPI_Stdcall GetAndroidVersion()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getAndroidVersion();
        }
        return QString();
    }

    EResult LAPI_Stdcall WriteKeyEvent(quint8 status, quint16 keyCode, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeKeyEvent(status, keyCode, sync, msec);
        }
        return EResult::ER_Success;
    }

    quint16 LAPI_Stdcall GetKeyEvent_Result()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getKeyEvent_Result();
        }
        return quint16();
    }

    EResult LAPI_Stdcall WriteDeviceName(QString name, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeDeviceName(name, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult LAPI_Stdcall ReadDeviceName(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readDeviceName(sync, msec);
        }
        return EResult::ER_Success;
    }

    QString LAPI_Stdcall GetDeviceName()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getDeviceName();
        }
        return QString();
    }

    EResult LAPI_Stdcall ReadNetDeviceOnlineStatus(QString ip, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readNetDeviceOnlineStatus(ip, sync, msec);
        }
        return EResult::ER_Success;
    }

    quint16 LAPI_Stdcall GetNetDevice_Status()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getNetDevice_Status();
        }
        return quint16();
    }

    QString LAPI_Stdcall GetNetDevice_IP()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getNetDevice_IP();
        }
        return QString();
    }

    EResult LAPI_Stdcall ReadSCEthLoopTestResult(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readSCEthLoopTestResult(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint16 LAPI_Stdcall GetSCEthLoopTest_Result()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getSCEthLoopTest_Result();
        }
        return quint16();
    }

    quint8 LAPI_Stdcall GetSCEthLoopTest_EffectiveEthCount()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getSCEthLoopTest_EffectiveEthCount();
        }
        return quint8();
    }

    QByteArray LAPI_Stdcall GetSCEthLoopTest_ReplyData()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getSCEthLoopTest_ReplyData();
        }
        return QByteArray();
    }

    QMap<quint8, float>LAPI_Stdcall GetSCEthLoopTest_BitErrRate()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getSCEthLoopTest_BitErrRate();
        }
        return QMap<quint8, float>();
    }

    EResult LAPI_Stdcall ReadUDiskMountingStatus(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readUDiskMountingStatus(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetUDiskMounting_Count()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getUDiskMounting_Count();
        }
        return quint8();
    }

    QStringList LAPI_Stdcall GetUDiskMounting_List()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getUDiskMounting_List();
        }
        return QStringList();
    }

    EResult LAPI_Stdcall WriteStartOSDTest(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeStartOSDTest(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetOSDTest_WhiteScreenTestResult()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getOSDTest_WhiteScreenTestResult();
        }
        return quint8();
    }

    quint8 LAPI_Stdcall GetOSDTest_BlackScreenTestResult()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getOSDTest_BlackScreenTestResult();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteRelaySwitc(quint8 status, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeRelaySwitc(status, sync, msec);
        }
        return EResult::ER_Success;
    }

    quint16 LAPI_Stdcall GetRelaySwitc_Result()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getRelaySwitc_Result();
        }
        return quint16();
    }

    quint8 LAPI_Stdcall GetRelaySwitc_Status()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getRelaySwitc_Status();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteEnterKeyTest(quint8 status, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeEnterKeyTest(status, sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetKeyTest_Result()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getKeyTest_Result();
        }
        return quint8();
    }

    EResult LAPI_Stdcall ReadKeyTestResult(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readKeyTestResult(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetKeyTestResult_Count()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getKeyTestResult_Count();
        }
        return quint8();
    }

    QList<quint16>LAPI_Stdcall GetKeyTestResult_List()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getKeyTestResult_List();
        }
        return QList<quint16>();
    }

    EResult LAPI_Stdcall ReadOpticalSensorParam(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readOpticalSensorParam(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint16 LAPI_Stdcall GetOpticalSensor_Param()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getOpticalSensor_Param();
        }
        return quint16();
    }

    EResult LAPI_Stdcall ReadRouterStatus(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readRouterStatus(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetRouter_5GWifiStatus()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getRouter_5GWifiStatus();
        }
        return quint8();
    }

    quint8 LAPI_Stdcall GetRouter_2_4GWifiStatus()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getRouter_2_4GWifiStatus();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeNetworkCardMACAddr(flage, mac, sync, msec);
        }
        return EResult::ER_Success;
    }

    quint16 LAPI_Stdcall GetNetworkCardMACAddr_Results()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getNetworkCardMACAddr_Results();
        }
        return quint16();
    }

    quint8 LAPI_Stdcall GetNetworkCardMACAddr_Flage()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getNetworkCardMACAddr_Flage();
        }
        return quint8();
    }

    QByteArray LAPI_Stdcall GetNetworkCardMACAddr_MAC()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getNetworkCardMACAddr_MAC();
        }
        return QByteArray();
    }

    EResult LAPI_Stdcall WritePlayTestSound_1KHZ(quint8 status, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writePlayTestSound_1KHZ(status, sync, msec);
        }
        return EResult::ER_Success;
    }

    quint16 LAPI_Stdcall GetPlayTestSound_Results()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getPlayTestSound_Results();
        }
        return quint16();
    }

    quint8 LAPI_Stdcall GetPlayTestSound_Status()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getPlayTestSound_Status();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteWIFIModuleScanTest(quint8 status, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeWIFIModuleScanTest(status, sync, msec);
        }
        return EResult::ER_Success;
    }

    quint16 LAPI_Stdcall GetWIFIModuleScanTest_Results()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getWIFIModuleScanTest_Results();
        }
        return quint16();
    }

    EResult LAPI_Stdcall ReadWIFIScanList(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readWIFIScanList(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetWIFIScanList_Count()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getWIFIScanList_Count();
        }
        return quint8();
    }

    EResult LAPI_Stdcall ReadLoadPowerAmplifierChipParam(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readLoadPowerAmplifierChipParam(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 LAPI_Stdcall GetPowerAmplifierChipParam_Results()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getPowerAmplifierChipParam_Results();
        }
        return quint8();
    }

    quint8 LAPI_Stdcall GetPowerAmplifierChipParam_30Results()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getPowerAmplifierChipParam_30Results();
        }
        return quint8();
    }

    quint8 LAPI_Stdcall GetPowerAmplifierChipParam_31Results()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getPowerAmplifierChipParam_31Results();
        }
        return quint8();
    }

    EResult ReadCOMLoopTestResult(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readCOMLoopTestResult(sync, msec);
        }
        return EResult::ER_Success;
    }

    quint8 GetCOMLoopTest_INResult()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getCOMLoopTest_INResult();
        }
        return quint8();
    }

    quint8 GetCOMLoopTest_OUTResult()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getCOMLoopTest_OUTResult();
        }
        return quint8();
    }

    EResult LAPI_Stdcall WriteEnterTestMode(QString key, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeEnterTestMode(key, sync, msec);
        }
        return EResult::ER_Success;
    }

    quint16 LAPI_Stdcall GetEnterTestMode_Results()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getEnterTestMode_Results();
        }
        return quint16();
    }

    EResult ReadHDMIInputSignalInfo(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readHDMIInputSignalInfo(sync, msec);
        }
        return EResult::ER_Success;
    }

    QString GetHDMIInputSignalInfo()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getHDMIInputSignalInfo();
        }
        return QString();
    }


    EResult ReadHDMIVersion(bool sync /*= false*/, int msec /*= LBL_Defalut_SyncTimeout*/)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readHDMIVersion(sync, msec);
        }
        return EResult::ER_Success;
    }

    QString GetHDMIVersion()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getHDMIVersion();
        }
        return QString();
    }

    EResult writeHDMIMultiScreenMode(const UI::EMultiScreenMode value, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeHDMIMultiScreenMode(value, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult readHDMIMultiScreenMode(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readHDMIMultiScreenMode(sync, msec);
        }
        return EResult::ER_Success;
    }

    UI::EMultiScreenMode getHDMIMultiScreenMode()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (UI::EMultiScreenMode)i->getHDMIMultiScreenMode();
        }
        return UI::EMultiScreenMode();
    }

    EResult WriteHDMIMultiScreenInputSource(const quint8 param, const UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeHDMIMultiScreenInputSource(param, channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult WriteHDMIMultiScreenInputSourceList(const QList<quint8>& values, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeHDMIMultiScreenInputSourceList(values, sync, msec);
        }
        return EResult::ER_Success;
    }

    EResult ReadHDMIMultiScreenInputSource(const UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readHDMIMultiScreenInputSource(channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    QList<quint8> GetHDMIMultiScreenInputSource(const UI::EHDMIChannel channel)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getHDMIMultiScreenInputSource(channel);
        }
        return QList<quint8>();
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ResetHDMISetting(bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->resetHDMISetting(sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDIMIWindowSize(QSize value, UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeHDIMIWindowSize(value, channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDIMIWindowSize(UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readHDIMIWindowSize(channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QSize LAPI_Stdcall GetHDIMIWindowSize()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getHDIMIWindowSize();
        }
        return QSize();
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDIMIWindowPos(QPoint value, UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeHDIMIWindowPos(value, channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDIMIWindowPos(UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readHDIMIWindowPos(channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT QPoint LAPI_Stdcall GetHDIMIWindowPos()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getHDIMIWindowPos();
        }
        return QPoint();
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDIMIWindowStatus(quint8 status, UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeHDIMIWindowStatus(status, channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDIMIWindowStatus(UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readHDIMIWindowStatus(channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetHDIMIWindowStatus()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getHDIMIWindowStatus();
        }
        return quint8();
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDIMIAudioSrc(quint8 param, UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->writeHDIMIAudioSrc(param, channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDIMIAudioSrc(UI::EHDMIChannel channel, bool sync, int msec)
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return (EResult)i->readHDIMIAudioSrc(channel, sync, msec);
        }
        return EResult::ER_Success;
    }

    ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetHDIMIAudioSrc()
    {
        for (auto i : gSCItemMgr->getUsingItemList()) {
            return i->getHDIMIAudioSrc();
        }
        return quint8();
    }

}
