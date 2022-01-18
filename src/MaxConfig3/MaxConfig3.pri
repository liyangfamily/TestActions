
SOURCES += \
    $$PWD/ConnectionControl/arrowItem.cpp \
    $$PWD/ConnectionControl/connectionScene.cpp \
    $$PWD/ConnectionControl/connectionView.cpp \
    $$PWD/ConnectionControl/mcsplitwindowitem.cpp \
    $$PWD/ConnectionControl/moduleItem.cpp \
    $$PWD/Core/dialogs/restartdialog.cpp \
    $$PWD/Core/icore.cpp \
    $$PWD/Core/mainwindow_new.cpp \
    $$PWD/Core/versiondialog.cpp \
    $$PWD/CustomWidget/flowlayout.cpp \
    $$PWD/CustomWidget/framelesswindow.cpp \
    $$PWD/CustomWidget/mccusfileupgradewidget.cpp \
    $$PWD/CustomWidget/mccusswitchbutton.cpp \
    $$PWD/CustomWidget/mcdelegateclass.cpp \
    $$PWD/CustomWidget/mcelevatedclass.cpp \
    $$PWD/CustomWidget/mcprogressdialog.cpp \
    $$PWD/HDMIChip/mcms9570advsetting.cpp \
    $$PWD/HDMIChip/mcnt68400advsetting.cpp \
    $$PWD/Utils/appmainwindow.cpp \
    $$PWD/Utils/correctdatahelper.cpp \
    $$PWD/Utils/gammatablehelper.cpp \
    $$PWD/Utils/graphicstheme.cpp \
    $$PWD/Utils/testscreenhelper.cpp \
    $$PWD/app.cpp \
    $$PWD/mcconnection.cpp \
    $$PWD/mccorrect.cpp \
    $$PWD/mcgammatable.cpp \
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
    $$PWD/ConnectionControl/mcsplitwindowitem.h \
    $$PWD/ConnectionControl/moduleItem.h \
    $$PWD/Core/app_version.h \
    $$PWD/Core/dialogs/restartdialog.h \
    $$PWD/Core/icore.h \
    $$PWD/Core/mainwindow_new.h \
    $$PWD/Core/versiondialog.h \
    $$PWD/CustomWidget/flowlayout.h \
    $$PWD/CustomWidget/framelesswindow.h \
    $$PWD/CustomWidget/mccusfileupgradewidget.h \
    $$PWD/CustomWidget/mccusswitchbutton.h \
    $$PWD/CustomWidget/mcdelegateclass.h \
    $$PWD/CustomWidget/mcelevatedclass.h \
    $$PWD/CustomWidget/mcprogressdialog.h \
    $$PWD/HDMIChip/mcms9570advsetting.h \
    $$PWD/HDMIChip/mcnt68400advsetting.h \
    $$PWD/Utils/appmainwindow.h \
    $$PWD/Utils/correctdatahelper.h \
    $$PWD/Utils/gammatablehelper.h \
    $$PWD/Utils/graphicstheme.h \
    $$PWD/Utils/testscreenhelper.h \
    $$PWD/Utils/utilsfilefilter.h \
    $$PWD/app.h \
    $$PWD/mcconnection.h \
    $$PWD/mccorrect.h \
    $$PWD/mcgammatable.h \
    $$PWD/mcmonitor.h \
    $$PWD/mcreceivecard.h \
    $$PWD/mcsendercard.h \
    $$PWD/mcupgrade.h \
    CustomWidget/mccussclistitemwidget.h \
    mainwindow.h \
    mcscreen.h

FORMS += \
    $$PWD/Core/mainwindow_new.ui \
    $$PWD/HDMIChip/mcms9570advsetting.ui \
    $$PWD/HDMIChip/mcnt68400advsetting.ui \
    $$PWD/mcconnection.ui \
    $$PWD/mccorrect.ui \
    $$PWD/mcgammatable.ui \
    $$PWD/mcmonitor.ui \
    $$PWD/mcreceivecard.ui \
    $$PWD/mcsendercard.ui \
    $$PWD/mcupgrade.ui \
    CustomWidget/mccussclistitemwidget.ui \
    mainwindow.ui \
    mcscreen.ui

#TRANSLATIONS += \
#    MaxConfig3_zh_CN.ts

DISTFILES += \
    $$PWD/Core/normal.css \
    default.css

RESOURCES += \
    MaxConfig3.qrc
