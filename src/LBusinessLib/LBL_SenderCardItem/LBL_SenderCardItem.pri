QT += core network serialport
CONFIG += c++11 qt

DEFINES += LBL_SENDERCARDITEM_LIB

HEADERS += \
    $$PWD/../../../include/LBusinessLib/LBL_SenderCardItem/LBLAbstractSCItem.h \
    $$PWD/../../../include/LBusinessLib/LBL_SenderCardItem/LBLSCItemGlobal.h \
    $$PWD/../../../include/LBusinessLib/LBL_SenderCardItem/LBLSCItemManager.h \
    $$PWD/../../../include/LBusinessLib/LBL_SenderCardItem/LBLSCItemStructGlobal.h \
    $$PWD/../../../include/LBusinessLib/LBL_SenderCardItem/LBLSCItemStruct_BaseDef.h \
    ./LBL_SCItem_Factory.h \
    ./LBL_SCItem_2nd.h \
    ./LBL_SCItem_2ndPlus.h \
    ./LBL_SCItem_PCON600.h \
    ./LBL_SCItem_2nd_GZ.h \
    ./LBL_SCItem_PCON600_p.h \
    ./LBL_SCItem_2ndPlus_p.h \
    ./LBL_SCItem_2nd_GZ_p.h \
    ./LBL_SCItem_2nd_p.h \
    ./LBL_SCItem_Abstract_p.h \
    ./DetectServer/LBLDetectServer.h

SOURCES += ./LBLAbstractSCItem.cpp \
    ./LBL_SCItem_2nd.cpp \
    ./LBL_SCItem_2ndPlus.cpp \
    ./LBL_SCItem_PCON600.cpp \
    ./LBL_SCItem_2nd_GZ.cpp \
    ./LBLSCItemManager.cpp \
    ./DetectServer/LBLDetectServer.cpp
