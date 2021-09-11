include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
TARGET = $$QTC_LIB_NAME

include(../MaxConfig.pri)

win32 {
    DLLDESTDIR = $$PRO_APP_PATH
}

DESTDIR = $$PRO_LIBRARY_PATH
TARGET = $$qtLibraryTargetName($$TARGET)

TEMPLATE = lib
CONFIG += shared dll


INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LAPI_Control)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_SenderCardItem)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_CommunicatEngine)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_Control)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_Core)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_Advanced)
