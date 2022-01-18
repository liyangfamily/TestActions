#include <LBL_Core/LBLDef>
#if(LBL_MemoryLeaksDetect)
#include <vld.h>
#endif
#include "app.h"
#include "Core/app_version.h"
#include "mainwindow.h"
#include "Core/mainwindow_new.h"
#include <Logger.h>
#include <FileAppender.h>
#include <ConsoleAppender.h>

#include <Core/qtsingleapplication/QtSingleApplication>
#include <QtWidgets/QApplication>

#include <QSerialPort>
#include <QHostInfo>
#include <QFile>
#include <QThread>
class Restarter
{
public:
    Restarter(int argc, char *argv[])
    {
        Q_UNUSED(argc)
        m_executable = QString::fromLocal8Bit(argv[0]);
        m_workingPath = QDir::currentPath();
    }

    void setArguments(const QStringList &args) { m_args = args; }

    QStringList arguments() const { return m_args; }

    int restartOrExit(int exitCode)
    {
        App::writeConfig();
        return qApp->property("restart").toBool() ? restart(exitCode) : exitCode;
    }

    int restart(int exitCode)
    {
        QtSingleApplication * app=static_cast<QtSingleApplication*>(qApp);
        if(app){
            app->unstallSys();
        }
        QProcess::startDetached(m_executable, m_args, m_workingPath);
        return exitCode;
    }

private:
    QString m_executable;
    QStringList m_args;
    QString m_workingPath;
};

int main(int argc, char *argv[])
{
    Restarter restarter(argc, argv);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QHostInfo host; //不添加这一行，vld就不工作

    QtSingleApplication a("MaxConfig3",argc, argv);
    if(a.isRunning()) //判断实例是否已经运行
    {
        qDebug()<<"this is already running";
        a.sendMessage("raise_window_noop", 4000); //4s后激活前个实例
        return EXIT_SUCCESS;
    }

    // Startup Config.
    App::ConfigFile = QString("%1/%2.ini").arg(LBLUIHelper::appConfigDataLocation()).arg(LBLUIHelper::appName());
    App::readConfig();
    App::writeConfig();

    // Startup logging.
    if(App::enableLog){
        QDir dir = LBLUIHelper::appLogDataLocation();
        LBLUIHelper::setEnableCommunicatLog(App::enableCommunicatLog);
        if (!dir.exists()) dir.mkpath(dir.path());
        const QString logFileName = dir.filePath("maxconfig-log.txt");
        //QFile::remove(logFileName);
        FileAppender* fileAppender = new FileAppender(logFileName);
        fileAppender->setFormat("[%{type:-7}]<%{time}> %{message}\n");
        cuteLogger->registerAppender(fileAppender);
    }

    //#ifndef NDEBUG
    // Only log to console in dev debug builds.
    ConsoleAppender* consoleAppender = new ConsoleAppender();
    consoleAppender->setFormat("[%{type:-7}]<%{time}> <%{function}> %{message}\n");
    cuteLogger->registerAppender(consoleAppender);
    //#endif

    // Log some basic info.
    LOG_INFO() << "Starting MaxConfig version" << Core::Constants::IDE_VERSION_DISPLAY;
#if defined (Q_OS_WIN)
    LOG_INFO() << "Windows version" << QSysInfo::windowsVersion();
#elif defined(Q_OS_MAC)
    LOG_INFO() << "macOS version" << QSysInfo::macVersion();
#else
    LOG_INFO() << "Linux version";
#endif
    LOG_INFO() << "number of logical cores =" << QThread::idealThreadCount();
    LOG_INFO() << "locale =" << QLocale();
    LOG_INFO() << "install dir =" <<  a.applicationDirPath();
    LOG_INFO() << "device pixel ratio =" << a.devicePixelRatio();

    QFont font;
    //你想设置的字体
    font.setFamily("Microsoft YaHei");
    a.setFont(font);

    QFile qss(":/css/Core/normal.css");
    //QFile qss(":/css/default.css");
    if (qss.open(QFile::ReadOnly)) {
        qDebug("normal.css Open success");
        QString style = qss.readAll();
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("default.css Open failed");
    }


    QTranslator translator;
    QTranslator qtTranslator;
    QStringList uiLanguages = QLocale::system().uiLanguages();
    if(App::lastLanguage.isEmpty()){
        App::lastLanguage=QLocale(uiLanguages.first()).name();
        App::writeConfig();
    }
    QString overrideLanguage = App::lastLanguage;
    if (!overrideLanguage.isEmpty())
        uiLanguages.prepend(overrideLanguage);
    const QString &appTrPath = LBLUIHelper::appLocalsLocation();
    for (QString locale : qAsConst(uiLanguages)) {
        locale = QLocale(locale).name();
        const QString &appTrFile = QLatin1String("MaxConfig3_") + locale;
        const QString &qtTrFile = QLatin1String("qt_") + locale;
        if (translator.load(appTrFile, appTrPath)){
            a.installTranslator(&translator);
            if(qtTranslator.load(qtTrFile, appTrPath)) {
                a.installTranslator(&qtTranslator);
            }
            a.setProperty("app_locale", locale);
            break;
        }
        translator.load(QString()); // unload()
    }

    Core::Internal::MainWindow w;
    a.setActivationWindow(&w,1); //如果是第一个实例,则绑定,方便下次调用
    //MainWindow_New w;
    w.show();
    return restarter.restartOrExit(a.exec());
}
