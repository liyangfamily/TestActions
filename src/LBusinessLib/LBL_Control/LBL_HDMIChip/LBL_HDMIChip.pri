QT += core
CONFIG += c++11 qt

DEFINES += LBL_HDMICHIP_LIB

HEADERS += ./LBLHDMIChipCentralCtrl.h \
    $$PWD/NT68400/LBLNT68400Struct.h \
    ./LBLHDMIChipFactory.h \
    ./LBLHDMIChipGlobal.h \
    ./LBLHDMIChipAbstract.h \
    ./LBLHDMIChipAbstract_p.h \
    ./MS9570/LBLMS9570Abstract.h \
    ./MS9570/LBLMS9570CentralCtrl.h \
    ./MS9570/LBLMS9570DataOperat.h \
    ./MS9570/LBL_MS9570_Factory.h \
    ./MS9570/LBL_MS9570_Struct.h \
    ./MS9570/LBLMS9570Abstract_p.h \
    ./NT68400/LBLNT68400Abstract.h \
    ./NT68400/LBLNT68400CentralCtrl.h \
    ./NT68400/LBLNT68400Factory.h \
    ./NT68400/LBLNT68400Abstract_p.h
SOURCES += ./LBLHDMIChipCentralCtrl.cpp \
    ./LBLHDMIChipAbstract.cpp \
    ./MS9570/LBLMS9570Abstract.cpp \
    ./MS9570/LBLMS9570CentralCtrl.cpp \
    ./MS9570/LBLMS9570DataOperat.cpp \
    ./NT68400/LBLNT68400Abstract.cpp \
    ./NT68400/LBLNT68400CentralCtrl.cpp
