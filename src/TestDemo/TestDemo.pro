# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
QT += core gui network serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += c++11 qt debug_and_release
TARGET = TestDemo
include(../common.pri)
include(TestDemo.pri)

CONFIG(debug, debug|release){
    contains(QT_ARCH, i386) {
        DESTDIR = $$LBUSINESSLIB_BINDIR/Debug_Win32
        LIBS += -L$$LBUSINESSLIB_LIBDIR/Debug_Win32  \
        -lLBL_Cored \
        -lLAPI_Controld \
        -lLBL_CommunicatEngined \
        -lLBL_SenderCardItemd
    } else {
        DESTDIR = $$LBUSINESSLIB_BINDIR/Debug_x64
        LIBS += -L$$LBUSINESSLIB_LIBDIR/Debug_x64  \
        -lLBL_Cored \
        -lLAPI_Controld \
        -lLBL_CommunicatEngined \
        -lLBL_SenderCardItemd
    }

} else {
    contains(QT_ARCH, i386) {
        DESTDIR = $$LBUSINESSLIB_BINDIR/Release_Win32
        LIBS += -L$$LBUSINESSLIB_LIBDIR/Release_Win32 \
        -lLBL_Core \
        -lLAPI_Control \
        -lLBL_CommunicatEngine \
        -lLBL_SenderCardItem
    } else {
        DESTDIR = $$LBUSINESSLIB_BINDIR/Release_x64
        LIBS += -L$$LBUSINESSLIB_LIBDIR/Release_x64  \
        -lLBL_Core \
        -lLAPI_Control \
        -lLBL_CommunicatEngine \
        -lLBL_SenderCardItem
    }
}
