#ifndef UNIVERSALINTERFACE_H
#define UNIVERSALINTERFACE_H

#include <QAbstractItemModel>
#include <LAPIControl>


class UniversalInterface
{


//public:
//    static UniversalInterface& GetInstance(void);

public:
    explicit UniversalInterface(QObject *parent = nullptr);


public:
    static QByteArray Readbin(QString path);
    static bool Writebin(QString path, QByteArray bytes);
    static void MessageBoxShow(QString title,QString str);
    //QByteArray ModulePara;
    static bool SendALLPara();
    static bool ReadALLPara();


//public:
//    void SetModulepara(QByteArray para);


//public:
//    QByteArray GetModulepara(void);



};

#endif // UNIVERSALINTERFACE_H
