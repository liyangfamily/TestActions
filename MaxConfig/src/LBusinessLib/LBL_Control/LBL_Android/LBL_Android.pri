QT += core
CONFIG += c++11 qt

DEFINES += LBL_ANDROID_LIB

HEADERS += ./LBLAndroidCentralCtrl.h \
    ./LBLAndroidFactory.h \
    ./LBLAndroid_Global.h \
    ./LBLAndroidAbstract.h \
    ./LBLAndroidAbstract_p.h
SOURCES += ./LBLAndroidCentralCtrl.cpp \
    ./LBLAndroidAbstract.cpp
