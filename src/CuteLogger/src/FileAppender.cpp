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
// Local
#include "FileAppender.h"
#include <Logger.h>

// STL
#include <iostream>

/**
 * \class FileAppender
 *
 * \brief Simple appender that writes the log records to the plain text file.
 */


//! Constructs the new file appender assigned to file with the given name.
FileAppender::FileAppender(const QString& fileName):
    m_maxBackupIndex(1),
    m_maximumFileSize(10 * 1024 * 1024)
{
  setFileName(fileName);
}


FileAppender::~FileAppender()
{
  closeFile();
}


//! Returns the name set by setFileName() or to the FileAppender constructor.
/**
 * \sa setFileName()
 */
QString FileAppender::fileName() const
{
  QMutexLocker locker(&m_logFileMutex);
  return m_logFile.fileName();
}


//! Sets the name of the file. The name can have no path, a relative path, or an absolute path.
/**
 * \sa fileName()
 */
void FileAppender::setFileName(const QString& s)
{
  QMutexLocker locker(&m_logFileMutex);
  if (m_logFile.isOpen())
    m_logFile.close();

  m_logFile.setFileName(s);
}

void FileAppender::setMaxBackupIndex(int maxBackupIndex)
{
    QMutexLocker locker(&m_logFileMutex);
    m_maxBackupIndex = maxBackupIndex;
}

int FileAppender::maxBackupIndex() const
{
    QMutexLocker locker(&m_logFileMutex);
    return m_maxBackupIndex;
}

void FileAppender::setMaximumFileSize(qint64 maximumFileSize)
{
    QMutexLocker locker(&m_logFileMutex);
    m_maximumFileSize = maximumFileSize;
}

qint64 FileAppender::maximumFileSize() const
{
    QMutexLocker locker(&m_logFileMutex);
    return m_maximumFileSize;
}


bool FileAppender::openFile()
{
  bool isOpen = m_logFile.isOpen();
  if (!isOpen)
  {
    isOpen = m_logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    if (isOpen)
      m_logStream.setDevice(&m_logFile);
    else
      std::cerr << "<FileAppender::append> Cannot open the log file " << qPrintable(m_logFile.fileName()) << std::endl;
  }
  return isOpen;
}


//! Write the log record to the file.
/**
 * \sa fileName()
 * \sa AbstractStringAppender::format()
 */
void FileAppender::append(const QDateTime& timeStamp, Logger::LogLevel logLevel, const char* file, int line,
                          const char* function, const QString& category, const QString& message)
{
  QMutexLocker locker(&m_logFileMutex);

  if (openFile())
  {
      m_logStream << formattedString(timeStamp, logLevel, file, line, function, category, message);
      m_logStream.flush();
      m_logFile.flush();
  }
  locker.unlock();
  if (m_logStream.device()->size() > this->m_maximumFileSize){
      //qDebug()<<(QStringLiteral("Rolling over with maxBackupIndex = %1"), m_maxBackupIndex);
      rollOver();
  }
}


void FileAppender::closeFile()
{
  m_logFile.close();
}

bool FileAppender::removeFile(QFile &file) const
{
    if (file.remove())
        return true;
    //qDebug()<<(QStringLiteral("Unable to remove file '%1' for appender 'FileAppender'"),file.fileName());
    return false;
}

bool FileAppender::renameFile(QFile &file, const QString &fileName) const
{
    //qDebug()<<(QStringLiteral("Renaming file '%1' to '%2'"), file.fileName(), fileName);
    if (file.rename(fileName))
        return true;

    //qDebug()<<(QStringLiteral("Unable to rename file '%1' to '%2' for appender 'FileAppender'"),file.fileName(),fileName);
    return false;
}

void FileAppender::rollOver()
{
    //qDebug()<<(QStringLiteral("Rolling over with maxBackupIndex = %1"), m_maxBackupIndex);

    closeFile();

    QFile f;
    f.setFileName(fileName() + QLatin1Char('.') + QString::number(m_maxBackupIndex));
    if (f.exists() && !removeFile(f))
        return;

    for (int i = m_maxBackupIndex - 1; i >= 1; i--)
    {
        f.setFileName(fileName() + QLatin1Char('.') + QString::number(i));
        if (f.exists())
        {
            const QString target_file_name = fileName() + QLatin1Char('.') + QString::number(i + 1);
            if (!renameFile(f, target_file_name))
                return;
        }
    }

    f.setFileName(fileName());
    // it may not exist on first startup, don't output a warning in this case
    if (f.exists())
    {
        const QString target_file_name = fileName() + QStringLiteral(".1");
        if (!renameFile(f, target_file_name))
            return;
    }

    FileAppender::openFile();
}
