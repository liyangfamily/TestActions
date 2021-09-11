include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
TARGET = $$QTC_LIB_NAME

include(../../MaxConfig.pri)

win32 {
    DLLDESTDIR = $$PRO_APP_PATH
}

osx {

}

DESTDIR = $$PRO_LIBRARY_PATH

TARGET = $$qtLibraryTargetName($$TARGET)

TEMPLATE = lib
CONFIG += shared dll
