/*
 * Copyright (C) <2017>  <Yehor Raketskyi(egormilo@gmail.com)>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "logger.h"

#include <QObject>
#include <QMetaEnum>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>

QMutex mutex;

#include "src/lib/singletone/singleton.h"
using namespace logging;

#define LOGGER_ERROR_Q_DEBUG() qDebug().noquote().nospace() << "LOGGER ERROR [" << this->metaObject()->className() \
  << "::" << __FUNCTION__ << ":" << __LINE__ << "] "

#define LOGGER_INFO_Q_DEBUG() qDebug().noquote().nospace() << "LOGGER INFO [" << this->metaObject()->className() \
  << "::" << __FUNCTION__ << ":" << __LINE__ << "] "

ELogger::ELogger(QObject* parent):
  QObject(parent)
  {
  }

ELogger* ELogger::createInstance()
  {
    return new ELogger();
  }

ELogger::~ELogger()
  {
  }

ELogger* ELogger::instance()
  {
    return Singleton<ELogger>::instance(ELogger::createInstance);
  }

void ELogger::log(ELoggingLevel level, qint64 pid, Qt::HANDLE tid, QString className, QString msg, QString funcName,
                  int lineNum)
  {
    if (level > logLevel)
      return;
    QMutexLocker loker(&mutex);
    QMetaEnum metaEnum = QMetaEnum::fromType<ELogger::ELoggingLevel>();
    QString line = "";
    line.append("[");
    line.append(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz"));
    line.append("] [");
    line.append(QString::number(pid));
    line.append("][0x");
    line.append(QString::number((long long)tid, 16));
    line.append("] [");
    line.append(QString(metaEnum.valueToKey(level)));
    line.append("] ");
    switch (level)
      {
      case E_EMERGENCY:
      case E_ALERT:
      case E_CRITICAL:
      case E_ERROR:
      case E_WARNING:
      case E_DEBUG:
        line.append("[");
        line.append(className);
        line.append("::");
        line.append(funcName);
        line.append(":");
        line.append(QString::number(lineNum));
        line.append("] ");
        break;
      case E_NOTICE:
      case E_INFORMATIONAL:
        break;
      default:
        break;
      }
    line.append(msg);
    qDebug().noquote().nospace() << line;
    if (!writeToFile(line))
      LOGGER_ERROR_Q_DEBUG() << "The message, which is specified below, wasn't written: \"" << line << "\"";
  }

bool ELogger::writeToFile(QString msg)
  {
    QString path = getPath();
    if (path.isEmpty())
      return false;

    QFile file(path);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << msg << endl;
        file.close();
        return true;
      }

    return false;
  }

QString ELogger::getPath()
  {
    QDateTime dateTime = QDateTime::currentDateTime();
    QDate date = dateTime.date();
    QString dirPath = this->dirPath;
    QString fileName = date.toString("yyyy_MM_dd").append(".log");
    if (fileExists(dirPath + "/" + fileName))
      return dirPath + "/" + fileName;

    QString path = "";
    foreach (QString entry, this->dirPath.split("/", QString::SkipEmptyParts))
      {
        if (!entry.isNull())
          {
            if (path.isEmpty())
              path.append(entry);
            else
              path.append("/").append(entry);
            if ((!dirExists(path)) && !createDir(path))
              {
                LOGGER_ERROR_Q_DEBUG() << "Cannot create dir:\"" << path << "\"";
                return "";
              }
          }
      }
    if (!createFile(dirPath + "/" + fileName))
      {
        LOGGER_ERROR_Q_DEBUG() << "Cannot create file:\"" << dirPath + "/" + fileName << "\"";
        return "";
      }
    return dirPath + "/" + fileName;
  }

bool ELogger::fileExists(QString path)
  {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    return check_file.exists() && check_file.isFile();
  }

bool ELogger::dirExists(QString path)
  {
    QFileInfo check_file(path);
    // check if dir exists and if yes: Is it really a file and no directory?
    return check_file.exists() && check_file.isDir();
  }

bool ELogger::createDir(QString path)
  {
    QDir dir(path);
    if (dir.mkpath("."))
      {
        LOGGER_INFO_Q_DEBUG() << "The directory was created : \"" << path << "\"";
        return true;
      }
    return false;
  }

bool ELogger::createFile(QString path)
  {
    QFile file(path);
    if (file.open(QIODevice::ReadWrite))
      {
        LOGGER_INFO_Q_DEBUG() << "The file was created : \"" << path << "\"";
        file.close();
        return true;
      }
    return false;
  }
