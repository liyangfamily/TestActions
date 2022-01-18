include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
include(../../MaxConfig.pri)
include(MaxConfig3.pri)
include(Core/qtsingleapplication/qtsingleapplication.pri)

QT += core gui serialport network opengl openglextensions printsupport
QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += c++11
win32:RC_ICONS = Resources/Normal/MaxConfig.ico
osx:ICON = Resources/Normal/MaxConfig.icns
TARGET = $$PRO_APP_TARGET
DESTDIR = $$PRO_APP_PATH

INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LAPI_Control)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_SenderCardItem)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_CommunicatEngine)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_Control)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_Core)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_Advanced)
INCLUDEPATH += $$nativePath(../CuteLogger/include)

exists (../../../.git) {
    GIT_BRANCH   = $$system(git rev-parse --abbrev-ref HEAD)
    GIT_SHA      = $$system(git rev-parse --short=8 HEAD)
    GIT_TIME     = $$system(git log --pretty=format:\"%cd\" --date=format:\"%Y%m%d-%H%M%S\" -1 HEAD)

    GIT_BUILD_INFO = "$${GIT_SHA}-$${GIT_TIME}"
} else {
    GIT_BRANCH         = --
    GIT_SHA            = --
    GIT_TIME           = --
    GIT_BUILD_INFO     = --
}
message(git time = $$GIT_TIME)
message(git sha = $$GIT_SHA)

DEFINES += GIT_BUILD_SHA=\"\\\"$$GIT_SHA\\\"\"
DEFINES += GIT_BUILD_TIME=\"\\\"$$GIT_TIME\\\"\"

#Param Path Copy
include(../../shard/function.prf)

ParamSrcFilePath += \
    $$PRO_SOURCE_SHARD/Parameter \
    $$PRO_SOURCE_SHARD/Locals \

# Copy runtime File
win32{
    system(xcopy /y $$nativePath($$PRO_SOURCE_SHARD/translations/*.qm) $$nativePath($$PRO_BIN_PATH/Locals/))
    system(xcopy $$nativePath($$PRO_SOURCE_SHARD/Parameter) $$nativePath($$PRO_BIN_PATH/Parameter/) /y /s)
    system(xcopy /y $$nativePath($$PRO_SOURCE_SHARD/doc) $$nativePath($$PRO_BIN_PATH/doc/)))
    system(xcopy /y $$nativePath($$PRO_SOURCE_SHARD/script) $$nativePath($$PRO_BIN_PATH/script/)))
}else {
    system(mkdir -p $$nativePath($$PRO_BIN_PATH/Locals))
    exists($$nativePath($$PRO_BIN_PATH/Locals)){
        system(cp -f -R $$nativePath($$PRO_SOURCE_SHARD/translations/*.qm) $$nativePath($$PRO_BIN_PATH/Locals))
    }
    system(cp -f -R $$nativePath($$PRO_SOURCE_SHARD/doc) $$nativePath($$PRO_BIN_PATH/doc/))
    system(cp -f -R $$nativePath($$PRO_SOURCE_SHARD/script) $$nativePath($$PRO_BIN_PATH/script/))
    system(cp -f -R $$nativePath($$PRO_SOURCE_SHARD/Parameter) $$nativePath($$PRO_BIN_PATH/Parameter/))
}


# macOS lib depend set shell script
#osx{
#    CONFIG(release, debug|release) {
#        QMAKE_POST_LINK += chmod +x $$PRO_SOURCE_SCRIPTS/macoslibdepend.sh &&
#        QMAKE_POST_LINK += $$PRO_SOURCE_SCRIPTS/macoslibdepend.sh $$PRO_APP_PATH $$PRO_APP_TARGET
#        }
#}
#win32{
#    CONFIG(release, debug|release) {
#        QMAKE_POST_LINK += PowerShell -Command $$PRO_SOURCE_SCRIPTS/windows-publish.ps1 $$[QT_INSTALL_BINS] $$PRO_APP_PATH $$PRO_APP_TARGET $$MAXCONFIG_VERSION
#        }
#}
