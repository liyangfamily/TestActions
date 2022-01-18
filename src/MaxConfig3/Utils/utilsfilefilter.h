#pragma once
#include <QApplication>

namespace Utils {
	namespace FileFilter {
        //参数文件
        const char ALLPARAM_FILTER[] =		"AllParam File(9K)(*.bin)";
		const char MODULEPARAM_FILTER[] =		"ModuleParam File(*.bin)";
		const char DRIVEICPARAM_FILTER[] =		"DriveICParm File(*.bin)";
		const char DECODINGICPARAM_FILTER[] =	"DecodingIC File(*.bin)";
		const char GAMMAPARAM_FILTER[] =		"Gamma File(*.bin)";
        const char OLDGAMMAPARAM_FILTER[] =		"Old Gamma File(*.bin)";
        const char GAMDATGAMMAPARAM_FILTER[] =		"GamDat Gamma File(*.gamdat)";
		const char TRACINGTABLEPARAM_FILTER[] = "TracingTable File(*.bin)";
		const char BINPARAM_FILTER[] = "Register File(*.bin)";
		//模拟校正图片
		const char PICTURECORRECT_FILTER[] = "Picture Correction File(*.png *.jpg *.bmp)";
        const char CORRECT_FILTER[] = "Correction File(*.bin)";
        //升级文件
        const QString UPGRADE_FILTER = QApplication::tr("Upgrade File(*.qst *.bin)");
        //连线关系Json文件
        const QString CONNECTION_FILTER = QApplication::tr("Connection File(*.ct)");
	}
}
