/*
  Copyright (c) 2010 Boris Moiseev (cyberbobs at gmail dot com)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1
  as published by the Free Software Foundation and appearing in the file
  LICENSE.LGPL included in the packaging of this file.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
*/
#ifndef FILEAPPENDER_H
#define FILEAPPENDER_H

// Logger
#include "CuteLogger_global.h"
#include <AbstractStringAppender.h>

// Qt
#include <QFile>
#include <QTextStream>


class CUTELOGGERSHARED_EXPORT FileAppender : public AbstractStringAppender
{
  public:
    FileAppender(const QString& fileName = QString());
    ~FileAppender();

    QString fileName() const;
    void setFileName(const QString&);

    //The default is 1.
    void setMaxBackupIndex(int maxBackupIndex);
    int maxBackupIndex() const;

    //The default is 10 MB (10 * 1024 * 1024).
    void setMaximumFileSize(qint64 maximumFileSize);
    qint64 maximumFileSize() const;

  protected:
    virtual void append(const QDateTime& timeStamp, Logger::LogLevel logLevel, const char* file, int line,
                        const char* function, const QString& category, const QString& message);
    bool openFile();
    void closeFile();
    bool removeFile(QFile &file) const;
    bool renameFile(QFile &file,const QString &fileName) const;
  private:
    void rollOver();
  private:
    QFile m_logFile;
    QTextStream m_logStream;
    int m_maxBackupIndex;
    qint64 m_maximumFileSize;
    mutable QMutex m_logFileMutex;
};

#endif // FILEAPPENDER_H
