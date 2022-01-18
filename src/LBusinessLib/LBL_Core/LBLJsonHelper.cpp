#include "LBL_Core/LBLJsonHelper.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

/**
 * LBLJsonHelper
 *
 */

bool LBLJsonHelper::isJsonHelperVaild()
{
    if (m_path.isEmpty())
    {
        qDebug() << "file path is Empty.";
        return false;
    }
    if (m_doc.isEmpty())
    {
        qDebug() << "jsonDocument is Empty.";
        return false;
    }
    return true;
}

bool LBLJsonHelper::saveJson(const qint8 version)
{
    return saveJsonAs(m_path,version);
}

bool LBLJsonHelper::saveJsonAs(const QString &path ,const qint8 version)
{
    if (!buildJson(m_doc,version))
    {
        qDebug() << "json build faild.";
        return false;
    }

    if (!isJsonHelperVaild())
    {
        qDebug() << "json is not vaild.";
        return false;
    }

    if (!write(path, m_doc))
    {
        qDebug() << "json file write faild.";
        return false;
    }
    return true;
}

bool LBLJsonHelper::readJson(const qint8 version)
{
    return readJsonFrom(m_path,version);
}

bool LBLJsonHelper::readJsonFrom(const QString &path ,const qint8 version)
{
    if (!read(path, m_doc))
    {
        qDebug() << "json file read faild.";
        return false;
    }

    if (!isJsonHelperVaild())
    {
        qDebug() << "json is not vaild.";
        return false;
    }

    if (!parseJson(m_doc,version))
    {
        qDebug() << "json parse faild.";
        return false;
    }
    return true;
}

bool LBLJsonHelper::write(const QString &path, const QJsonDocument &doc)
{
    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug() << "json file open faild.";
        return false;
    }
    file.write(doc.toJson());
    file.flush();
    file.close();
    return true;
}

bool LBLJsonHelper::read(const QString &path, QJsonDocument &doc)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "json file open faild.";
        return false;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError error;
    doc = QJsonDocument::fromJson(data, &error);
    if (doc.isEmpty())
    {
        qDebug() << error.errorString();
    }
    return true;
}
