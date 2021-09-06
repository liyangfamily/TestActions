QT += core
CONFIG += c++11 qt

DEFINES += LBL_RECEIVECARD_LIB

HEADERS += ./LBLReceiveCardCentralCtrl.h \
    ./LBLReceiveCardFactory.h \
    ./LBLReceiveCardGlobal.h \
    ./LBLReceiveCardAbstract.h \
    ./LBLReceiveCardAbstract_p.h \
    $$PWD/../../../../include/LBusinessLib/LBL_Control/LBLGZReceiveCardStruct.h \
    $$PWD/../../../../include/LBusinessLib/LBL_Control/LBLReceiveCardStruct.h

SOURCES += ./LBLReceiveCardCentralCtrl.cpp \
    ./LBLReceiveCardAbstract.cpp
