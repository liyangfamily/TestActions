include(../MaxConfig.pri)

DISTFILES += \
    windows/bin/archivegen.exe \
    windows/bin/binarycreator.exe \
    windows/bin/devtool.exe \
    windows/bin/installerbase.exe \
    windows/bin/repogen.exe \
    windows/config/MaxConfig.icns \
    windows/config/MaxConfig.ico \
    windows/config/MaxConfig16.ico \
    windows/config/MaxConfig16.png \
    windows/config/MaxConfig64.ico \
    windows/config/MaxConfig64.png \
    windows/config/config.xml \
    windows/packages/org.qstech.maxconfig/meta/installscript.qs \
    windows/packages/org.qstech.maxconfig/meta/package.xml

FORMS += \
    windows/packages/org.qstech.maxconfig/meta/targetwidget.ui

TEMPLATE = app
TARGET = phony_target
CONFIG -= qt sdk separate_debug_info gdb_dwarf_index
QT =
LIBS =
QMAKE_LINK = @: IGNORE THIS LINE

osx{
    CONFIG(release, debug|release) {
        QMAKE_POST_LINK += chmod +x $$PRO_SOURCE_SCRIPTS/macoslibdepend.sh &&
        QMAKE_POST_LINK += $$PRO_SOURCE_SCRIPTS/macoslibdepend.sh $$PRO_APP_PATH $$PRO_APP_TARGET
        }
}
win32{
    CONFIG(release, debug|release) {
        QMAKE_POST_LINK += PowerShell -Command $$PRO_SOURCE_SCRIPTS/windows-publish.ps1 $$[QT_INSTALL_BINS] $$PRO_APP_PATH $$PRO_APP_TARGET $$MAXCONFIG_VERSION &&
        QMAKE_POST_LINK += PowerShell -Command $$PRO_SOURCE_SCRIPTS/windows-packaging.ps1 $$PRO_APP_PATH $$PRO_APP_TARGET $$MAXCONFIG_VERSION
        }
}
