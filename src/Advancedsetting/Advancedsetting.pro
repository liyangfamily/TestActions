include(../Advancedsetting.pri)

QT += widgets
QT -= gui

#TARGET = Advancedsetting

#TEMPLATE = lib
DEFINES += ADVANCEDSETTING_LIBRARY

CONFIG += c++11 qt debug_and_release

SOURCES += \
    Advancedsetting/advancedcustom.cpp \
    Advancedsetting/advancedotherpara.cpp \
    Advancedsetting/advancedsetting.cpp \
    Advancedsetting/currentgain.cpp \
    Advancedsetting/datagroup.cpp \
    Advancedsetting/flashsetting.cpp \
       Advancedsetting/form.cpp \
    Advancedsetting/grayfineprocessing.cpp \
    Advancedsetting/icadvancedsetting.cpp \
    Advancedsetting/iccfd435asetting.cpp \
    Advancedsetting/iccfd455asetting.cpp \
    Advancedsetting/mos5366config.cpp \
    Advancedsetting/mos5957config.cpp \
    Advancedsetting/moscfd2138.cpp \
    Advancedsetting/rgbchange.cpp \
    Advancedsetting/scanparamater.cpp \
    Advancedsetting/smartsecondsetting.cpp \
    Advancedsetting/smartsetting.cpp \
    Advancedsetting/universalinterface.cpp \
       Advancedsetting/smartsecondsettingxian.cpp

HEADERS += \
    Advancedsetting/advancedcustom.h \
    Advancedsetting/AdvancedSetting_global.h \
    Advancedsetting/advancedotherpara.h \
    Advancedsetting/advancedsetting.h \
    Advancedsetting/currentgain.h \
    Advancedsetting/datagroup.h \
    Advancedsetting/flashsetting.h \
       Advancedsetting/form.h \
    Advancedsetting/grayfineprocessing.h \
    Advancedsetting/icadvancedsetting.h \
    Advancedsetting/iccfd435asetting.h \
    Advancedsetting/iccfd455asetting.h \
    Advancedsetting/mos5366config.h \
    Advancedsetting/mos5957config.h \
    Advancedsetting/moscfd2138.h \
    Advancedsetting/rgbchange.h \
    Advancedsetting/scanparamater.h \
    Advancedsetting/smartsecondsetting.h \
    Advancedsetting/smartsetting.h \
    Advancedsetting/universalinterface.h \
      Advancedsetting/smartsecondsettingxian.h

## Default rules for deployment.
#unix {
#    target.path = /usr/lib
#     INSTALLS += target
#}
#!isEmpty(target.path): INSTALLS += target

FORMS += \
    Advancedsetting/advancedcustom.ui \
    Advancedsetting/advancedotherpara.ui \
    Advancedsetting/advancedsetting.ui \
    Advancedsetting/currentgain.ui \
    Advancedsetting/datagroup.ui \
    Advancedsetting/flashsetting.ui \
        Advancedsetting/form.ui \
    Advancedsetting/grayfineprocessing.ui \
    Advancedsetting/icadvancedsetting.ui \
    Advancedsetting/iccfd435asetting.ui \
    Advancedsetting/iccfd455asetting.ui \
    Advancedsetting/mos5366config.ui \
    Advancedsetting/mos5957config.ui \
    Advancedsetting/moscfd2138.ui \
    Advancedsetting/rgbchange.ui \
    Advancedsetting/scanparamater.ui \
    Advancedsetting/smartsecondsetting.ui \
    Advancedsetting/smartsetting.ui \
      Advancedsetting/smartsecondsettingxian.ui





