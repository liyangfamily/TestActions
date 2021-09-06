QT += core
CONFIG += c++11 qt

DEFINES += LBL_SENDERCARD_LIB

HEADERS += ./LBLSenderCardCentralCtrl.h \
    $$PWD/../../../../include/LBusinessLib/LBL_Control/LBLGZSenderCardStruct.h \
    $$PWD/../../../../include/LBusinessLib/LBL_Control/LBLSenderCardStruct.h \
    ./LBLSenderCardCentralCtrl_COM.h \
    ./LBLSenderCardFactory.h \
    ./LBLSenderCardGlobal.h \
    ./LBLSenderCardAbstract.h \
    ./LBLSenderCardAbstract_p.h

SOURCES += ./LBLSenderCardCentralCtrl.cpp \
    ./LBLSenderCardCentralCtrl_COM.cpp \
    ./LBLSenderCardAbstract.cpp
