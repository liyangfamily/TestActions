include(../Advancedsetting.pri)

QT += widgets
QT -= gui

#TARGET = AdvancedSetting

#TEMPLATE = lib
DEFINES += ADVANCEDSETTING_LIBRARY

CONFIG += c++11 qt debug_and_release






SOURCES += \
    Advancedsetting/advancedcustom.cpp \
    advancedsetting/advancedotherpara.cpp \
    advancedsetting/advancedsetting.cpp \
    advancedsetting/currentgain.cpp \
    advancedsetting/datagroup.cpp \
    advancedsetting/flashsetting.cpp \
       advancedsetting/form.cpp \
    advancedsetting/grayfineprocessing.cpp \
    advancedsetting/icadvancedsetting.cpp \
    advancedsetting/iccfd435asetting.cpp \
    advancedsetting/iccfd455asetting.cpp \
    advancedsetting/mos5366config.cpp \
    advancedsetting/mos5957config.cpp \
    advancedsetting/moscfd2138.cpp \
    advancedsetting/rgbchange.cpp \
    advancedsetting/scanparamater.cpp \
    advancedsetting/smartsecondsetting.cpp \
    advancedsetting/smartsetting.cpp \
    advancedsetting/universalinterface.cpp \
       advancedsetting/smartsecondsettingxian.cpp

HEADERS += \
    Advancedsetting/advancedcustom.h \
    advancedsetting/AdvancedSetting_global.h \
    advancedsetting/advancedotherpara.h \
    advancedsetting/advancedsetting.h \
    advancedsetting/currentgain.h \
    advancedsetting/datagroup.h \
    advancedsetting/flashsetting.h \
       advancedsetting/form.h \
    advancedsetting/grayfineprocessing.h \
    advancedsetting/icadvancedsetting.h \
    advancedsetting/iccfd435asetting.h \
    advancedsetting/iccfd455asetting.h \
    advancedsetting/mos5366config.h \
    advancedsetting/mos5957config.h \
    advancedsetting/moscfd2138.h \
    advancedsetting/rgbchange.h \
    advancedsetting/scanparamater.h \
    advancedsetting/smartsecondsetting.h \
    advancedsetting/smartsetting.h \
    advancedsetting/universalinterface.h \
      advancedsetting/smartsecondsettingxian.h

## Default rules for deployment.
#unix {
#    target.path = /usr/lib
#     INSTALLS += target
#}
#!isEmpty(target.path): INSTALLS += target

FORMS += \
    Advancedsetting/advancedcustom.ui \
    advancedsetting/advancedotherpara.ui \
    advancedsetting/advancedsetting.ui \
    advancedsetting/currentgain.ui \
    advancedsetting/datagroup.ui \
    advancedsetting/flashsetting.ui \
        advancedsetting/form.ui \
    advancedsetting/grayfineprocessing.ui \
    advancedsetting/icadvancedsetting.ui \
    advancedsetting/iccfd435asetting.ui \
    advancedsetting/iccfd455asetting.ui \
    advancedsetting/mos5366config.ui \
    advancedsetting/mos5957config.ui \
    advancedsetting/moscfd2138.ui \
    advancedsetting/rgbchange.ui \
    advancedsetting/scanparamater.ui \
    advancedsetting/smartsecondsetting.ui \
    advancedsetting/smartsetting.ui \
      advancedsetting/smartsecondsettingxian.ui

INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LAPI_Control
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_SenderCardItem
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_CommunicatEngine
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_Control
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_Core
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_Advanced





