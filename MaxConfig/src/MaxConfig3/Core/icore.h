#pragma once

#include <QList>
#include <QMainWindow>
#include <QObject>
#include <QRect>
#include <QSettings>

#include <functional>
#include <LAPIDef>
QT_BEGIN_NAMESPACE
class QStatusBar;
class QWidget;
QT_END_NAMESPACE

namespace Core
{
	namespace Internal { class MainWindow; }
	class ICore : public QObject
	{
		Q_OBJECT

		friend class Internal::MainWindow;

		explicit ICore(Internal::MainWindow *mw);
		~ICore()  override;

	public:
		static ICore *instance();
		static QMainWindow *mainWindow();
		static QStatusBar *statusBar();
		static void restart();
        static QWidget *dialogParent();
        static void raiseWindow(QWidget *widget);

        //about
        static QString versionString();


		static void showMessageLAPIResult(LAPI::EResult ret, int msec = 1000);
        static void showMessage(const QString& message,int msec=1000);

    public:
        /* internal use */

        static QString buildCompatibilityString();
	};

}
