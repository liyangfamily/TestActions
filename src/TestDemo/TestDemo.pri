# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

# This is a reminder that you are using a generated .pro file.
# Remove it when you are finished editing this file.
message("You are running qmake on a generated .pro file. This may not work!")

include(../common.pri)

HEADERS += ./LBLEnginePackage.h \
    $$PWD/frmandroidtest.h \
    $$PWD/progressmanager/TestRunable.h \
    $$PWD/progressmanager/algorithm.h \
    $$PWD/progressmanager/futureprogress.h \
    $$PWD/progressmanager/id.h \
    $$PWD/progressmanager/progressbar.h \
    $$PWD/progressmanager/progressmanager.h \
    $$PWD/progressmanager/progressmanager_p.h \
    $$PWD/progressmanager/progressview.h \
    ./head.h \
    ./frmmain.h \
    ./frmudpserver.h \
    ./frmudpclient.h \
    ./frmtcpserver.h \
    ./frmtcpclient.h \
    ./app.h \
    ./tcpserver.h \
    ./quiwidget.h
SOURCES += ./frmmain.cpp \
    $$PWD/frmandroidtest.cpp \
    $$PWD/progressmanager/TestRunable.cpp \
    $$PWD/progressmanager/futureprogress.cpp \
    $$PWD/progressmanager/id.cpp \
    $$PWD/progressmanager/progressbar.cpp \
    $$PWD/progressmanager/progressmanager.cpp \
    $$PWD/progressmanager/progressmanager_win.cpp \
    $$PWD/progressmanager/progressview.cpp \
    ./frmtcpclient.cpp \
    ./frmtcpserver.cpp \
    ./frmudpclient.cpp \
    ./frmudpserver.cpp \
    ./main.cpp \
    ./app.cpp \
    ./quiwidget.cpp \
    ./tcpserver.cpp
FORMS += ./TestDemo.ui \
    $$PWD/frmandroidtest.ui \
    ./frmmain.ui \
    ./frmtcpclient.ui \
    ./frmtcpserver.ui \
    ./frmudpclient.ui \
    ./frmudpserver.ui
RESOURCES += TestDemo.qrc