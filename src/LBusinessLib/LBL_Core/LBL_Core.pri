QT += core
CONFIG += c++11 qt

DEFINES += LBL_CORE_LIB

SOURCES += \
    $$PWD/LBLFileTransferChecker.cpp \
    LBLConnection.cpp \
    LBLSignalWaiter.cpp \
    LBLUIHelper.cpp \
    LBLJsonHelper.cpp \
    LBLJsonConnection.cpp

HEADERS += \
    ../../../include/LBusinessLib/LBL_Core/LBLFileTransferChecker.h \
    ../../../include/LBusinessLib/LBL_Core/LAPIDef.h \
    ../../../include/LBusinessLib/LBL_Core/LAPIDefResult.h \
    ../../../include/LBusinessLib/LBL_Core/LAPIDefUI.h \
    ../../../include/LBusinessLib/LBL_Core/LBLConnection.h \
    ../../../include/LBusinessLib/LBL_Core/LBLCoreGlobal.h \
    ../../../include/LBusinessLib/LBL_Core/LBLDef.h \
    ../../../include/LBusinessLib/LBL_Core/LBLSignalWaiter.h \
    ../../../include/LBusinessLib/LBL_Core/LBLUIHelper.h \
    ../../../include/LBusinessLib/LBL_Core/LBLJsonHelper.h \
    ../../../include/LBusinessLib/LBL_Core/LBLJsonConnection.h
