QT += core
CONFIG += c++11 qt

DEFINES += LBL_FILETRANSFER_LIB

HEADERS += ./LBLFileTransferCentralCtrl_COM.h \
    ./LBLFiletransferGlobal.h \
    ./LBLFileTransferAbstract.h \
    ./LBLFileTransferCentralCtrl.h \
    ./LBLFileTransferFactory.h \
    ./LBLFileTransferAbstract_p.h
SOURCES += ./LBLFileTransferAbstract.cpp \
    ./LBLFileTransferCentralCtrl.cpp \
    ./LBLFileTransferCentralCtrl_COM.cpp
