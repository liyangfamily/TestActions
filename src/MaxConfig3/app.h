﻿#ifndef APP_H
#define APP_H
#include <QtCore>
#include "Utils/utilsfilefilter.h"

typedef enum{
    UI_ZH,
    UI_EN
}LANGUAGE;

Q_DECLARE_METATYPE(LANGUAGE)

class App
{
public:
    static QString ConfigFile;          //配置文件路径

	//UI Param
	static QString lastOpenPath;         //上次打开的路径
    static QString lastLanguage;         //上次使用的语言

    //读写配置参数及其他操作
    static void readConfig();           //读取配置参数
    static void writeConfig();          //写入配置参数
    static void newConfig();            //以初始值新建配置文件
    static bool checkConfig();          //校验配置文件
};

#endif // APP_H
