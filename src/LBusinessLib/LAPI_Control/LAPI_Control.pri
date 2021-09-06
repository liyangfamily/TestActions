QT += core
CONFIG += c++11 qt

DEFINES += LAPI_CONTROL_LIB

SOURCES += ./LAPIControl.cpp

HEADERS += \
    $$PWD/../../../include/LBusinessLib/LAPI_Control/LAPIControl.h \
    $$PWD/../../../include/LBusinessLib/LAPI_Control/LAPIGlobal.h
