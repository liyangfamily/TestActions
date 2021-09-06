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
    static char ConvertHexChar(char ch);
    static QByteArray ReadcsvContent(std::string ICorMOS,QString calibrationDir);
    static QString GetICFilename(quint16 ICNumber);
    static QString GetMOSFilename(uchar ICNumber);


};

#endif // UNIVERSALINTERFACE_H
