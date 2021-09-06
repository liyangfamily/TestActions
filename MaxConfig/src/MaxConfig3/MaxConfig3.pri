INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LAPI_Control
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_SenderCardItem
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_CommunicatEngine
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_Control
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_Core
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE\LBL_Advanced

SOURCES += \
    $$PWD/ConnectionControl/arrowItem.cpp \
    $$PWD/ConnectionControl/connectionScene.cpp \
    $$PWD/ConnectionControl/connectionView.cpp \
    $$PWD/ConnectionControl/moduleItem.cpp \
    $$PWD/Core/icore.cpp \
    $$PWD/Core/mainwindow_new.cpp \
    $$PWD/Core/versiondialog.cpp \
    $$PWD/CustomWidget/flowlayout.cpp \
    $$PWD/CustomWidget/framelesswindow.cpp \
    $$PWD/CustomWidget/mccusfileupgradewidget.cpp \
    $$PWD/CustomWidget/mccusswitchbutton.cpp \
    $$PWD/CustomWidget/mcelevatedclass.cpp \
    $$PWD/CustomWidget/mcsclistitemwidget.cpp \
    $$PWD/Utils/appmainwindow.cpp \
    $$PWD/Utils/correctdatahelper.cpp \
    $$PWD/Utils/graphicstheme.cpp \
    $$PWD/Utils/testscreenhelper.cpp \
    $$PWD/app.cpp \
    $$PWD/mcconnection.cpp \
    $$PWD/mccorrect.cpp \
    $$PWD/mcmonitor.cpp \
    $$PWD/mcreceivecard.cpp \
    $$PWD/mcsendercard.cpp \
    $$PWD/mcupgrade.cpp \
    CustomWidget/mccussclistitemwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mcscreen.cpp

HEADERS += \
    $$PWD/ConnectionControl/arrowItem.h \
    $$PWD/ConnectionControl/connectionScene.h \
    $$PWD/ConnectionControl/connectionView.h \
    $$PWD/ConnectionControl/moduleItem.h \
    $$PWD/Core/app_version.h \
    $$PWD/Core/icore.h \
    $$PWD/Core/mainwindow_new.h \
    $$PWD/Core/versiondialog.h \
    $$PWD/CustomWidget/flowlayout.h \
    $$PWD/CustomWidget/framelesswindow.h \
    $$PWD/CustomWidget/mccusfileupgradewidget.h \
    $$PWD/CustomWidget/mccusswitchbutton.h \
    $$PWD/CustomWidget/mcelevatedclass.h \
    $$PWD/CustomWidget/mcsclistitemwidget.h \
    $$PWD/Utils/appmainwindow.h \
    $$PWD/Utils/correctdatahelper.h \
    $$PWD/Utils/graphicstheme.h \
    $$PWD/Utils/testscreenhelper.h \
    $$PWD/Utils/utilsfilefilter.h \
    $$PWD/app.h \
    $$PWD/mcconnection.h \
    $$PWD/mccorrect.h \
    $$PWD/mcmonitor.h \
    $$PWD/mcreceivecard.h \
    $$PWD/mcsendercard.h \
    $$PWD/mcupgrade.h \
    CustomWidget/mccussclistitemwidget.h \
    mainwindow.h \
    mcscreen.h

FORMS += \
    $$PWD/Core/mainwindow_new.ui \
    $$PWD/CustomWidget/mcsclistitemwidget.ui \
    $$PWD/mcconnection.ui \
    $$PWD/mccorrect.ui \
    $$PWD/mcmonitor.ui \
    $$PWD/mcreceivecard.ui \
    $$PWD/mcsendercard.ui \
    $$PWD/mcupgrade.ui \
    CustomWidget/mccussclistitemwidget.ui \
    mainwindow.ui \
    mcscreen.ui

TRANSLATIONS += \
    MaxConfig3_zh_CN.ts

DISTFILES += \
    $$PWD/Core/normal.css \
    default.css

RESOURCES += \
    MaxConfig3.qrc
