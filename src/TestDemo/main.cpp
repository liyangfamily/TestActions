#include <LBL_Core/LBLDef>
#if(LBL_MemoryLeaksDetect)
#include <vld.h>
#endif

//#include "TestDemo.h"
#include "frmmain.h"
#include <QtWidgets/QApplication>
#include "quiwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QFont font;
	font.setFamily(QUIConfig::FontName);
	font.setPixelSize(QUIConfig::FontSize);
	a.setFont(font);

	QUIHelper::setCode();
	QUIHelper::initRand();

	App::Intervals << "1" << "10" << "20" << "50" << "100" << "200" << "300" << "500" << "1000" << "1500" << "2000" << "3000" << "5000" << "10000";
	App::ConfigFile = QString("%1/%2.ini").arg(QUIHelper::appPath()).arg(QUIHelper::appName());
	App::readConfig();
	App::readSendData();
	App::readDeviceData();

    /*TestDemo w1; 
	w1.setWindowTitle(QString("本机IP: %1 ").arg(QUIHelper::getLocalIP()));
    w1.show();*/

	frmMain w;
	w.setWindowTitle(QString("Test Demo 本机IP: %1 ").arg(QUIHelper::getLocalIP()));
	w.show();
    return a.exec();
}
