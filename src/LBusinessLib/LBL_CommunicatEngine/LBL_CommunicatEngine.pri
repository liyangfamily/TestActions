QT += core network serialport
CONFIG += c++11 qt

DEFINES += LBL_COMMUNICATENGINE_LIB

HEADERS += \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLCluster.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLClusterProxy.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLCommunicatEngineDef.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLCommunicatEngineGlobal.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLEnginePackage.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLFileTransferPackage.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLInteCtrlAndroidPackage.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLInteCtrlPackage.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLInteCtrlPackageStruct.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLInteCtrlReceiveCardPackage.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLInteCtrlSenderCardPackage.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLInteCtrlVideoSourcePackage.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLPackage.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLPackageDispatcher.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLPackageEvent.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLPackageManager.h \
    ../../../include/LBusinessLib/LBL_CommunicatEngine/LBLSocketLock.h \
    Cluster/LBL_TaskEngine_IntegratedCtrlTask.h \
    NetEngine/LBLEnginePackage_p.h \
    NetEngine/LBL_NetEngine.h \
    NetEngine/LBL_NetEngine_COMTransThread.h \
    NetEngine/LBL_NetEngine_TransThread.h \
    NetEngine/LBL_NetEngine_UDPTransThread.h \
    TaskEngine/LBL_TaskEngine.h \
    TaskEngine/LBL_TaskEngine_TaskBase.h \
    TaskEngine/LBL_TaskEngine_WorkingThread.h

SOURCES += \
    Cluster/LBLCluster.cpp \
    Cluster/LBL_TaskEngine_IntegratedCtrlTask.cpp \
    NetEngine/LBLEnginePackage.cpp \
    NetEngine/LBL_NetEngine.cpp \
    NetEngine/LBL_NetEngine_COMTransThread.cpp \
    NetEngine/LBL_NetEngine_TransThread.cpp \
    NetEngine/LBL_NetEngine_UDPTransThread.cpp \
    Protocol/FileTransfer/LBLFileTransferPackage.cpp \
    Protocol/IntegratedCtrl/LBLInteCtrlAndroidPackage.cpp \
    Protocol/IntegratedCtrl/LBLInteCtrlPackage.cpp \
    Protocol/IntegratedCtrl/LBLInteCtrlReceiveCardPackage.cpp \
    Protocol/IntegratedCtrl/LBLInteCtrlSenderCardPackage.cpp \
    Protocol/IntegratedCtrl/LBLInteCtrlVideoSourcePackage.cpp \
    Protocol/LBLPackage.cpp \
    Protocol/LBLPackageManager.cpp \
    TaskEngine/LBL_TaskEngine.cpp \
    TaskEngine/LBL_TaskEngine_TaskBase.cpp \
    TaskEngine/LBL_TaskEngine_WorkingThread.cpp \
    Tools/LBLClusterProxy.cpp \
    Tools/LBLPackageDispatcher.cpp \
    Tools/LBLPackageEvent.cpp \
    Tools/LBLSocketLock.cpp
