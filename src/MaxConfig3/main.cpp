#include <LBL_Core/LBLDef>
#if(LBL_MemoryLeaksDetect)
#include <vld.h>
#endif
#include "app.h"
#include "mainwindow.h"
#include "Core/mainwindow_new.h"

#include <QtWidgets/QApplication>

#include <QSerialPort>
#include <QHostInfo>
#include <QFile>
int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
	QHostInfo host; //不添加这一行，vld就不工作
    QApplication a(argc, argv);
    QFile qss(":/css/Core/normal.css");
    //QFile qss(":/css/default.css");
    if (qss.open(QFile::ReadOnly)) {
        qDebug("default.css Open success");
        QString style = qss.readAll();
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("default.css Open failed");
    }
    QFont font;
    //你想设置的字体
    font.setFamily("Microsoft YaHei");
    a.setFont(font);

	App::ConfigFile = QString("%1/%2.ini").arg(LBLUIHelper::appPath()).arg(LBLUIHelper::appName());
	App::readConfig();

    QTranslator translator;
    QStringList uiLanguages = QLocale::system().uiLanguages();
    if(App::lastLanguage.isEmpty()){
        App::lastLanguage=uiLanguages.first();
        App::writeConfig();
    }
    QString overrideLanguage = App::lastLanguage;
    if (!overrideLanguage.isEmpty())
        uiLanguages.prepend(overrideLanguage);
    const QString &appTrPath = LBLUIHelper::appLocalsLocation();
    for (QString locale : qAsConst(uiLanguages)) {
        locale = QLocale(locale).name();
        if (translator.load("maxconfig3_" + locale, appTrPath)) {
            a.installTranslator(&translator);
            break;
        }
    }
    
    Core::Internal::MainWindow w;
    //MainWindow_New w;
	w.show();
    return a.exec();
}
