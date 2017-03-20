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

#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QCoreApplication>

#include "src/lib/logging/log.h"
namespace logging
  {
  class ELogger : public QObject
    {
      Q_OBJECT
    public:
      enum ELoggingLevel
        {
        E_EMERGENCY = 0,
        E_ALERT = 1,
        E_CRITICAL = 2,
        E_ERROR = 3,
        E_WARNING = 4,
        E_NOTICE  = 5,
        E_INFORMATIONAL = 6,
        E_DEBUG = 7,
        };
      Q_ENUM(ELoggingLevel)

      ~ELogger();
      static ELogger* instance();
      void log(ELoggingLevel level, qint64 pid, Qt::HANDLE tid, QString className, QString msg, QString funcName,
               int lineNum);

    private:
      int logLevel = DEFAULT_LOG_LEVEL;
      QString dirPath = DEFAULT_LOG_PATH;

      QString getPath();
      ELogger(QObject* parent = 0);
      static ELogger* createInstance();
      bool writeToFile(QString msg);
      bool fileExists(QString path);
      bool dirExists(QString path);
      bool createDir(QString path);
      bool createFile(QString path);

    };
  }
#define LOGGER_INSTANCE logging::ELogger::instance()

#define LOG_EMERGENCY(msg) LOGGER_INSTANCE->log(logging::ELogger::ELoggingLevel::E_EMERGENCY, \
  QCoreApplication::applicationPid(), QThread::currentThreadId(), this->metaObject()->className(), msg, \
  QString(__FUNCTION__), (int)__LINE__)

#define LOG_ALERT(msg) LOGGER_INSTANCE->log(logging::ELogger::ELoggingLevel::E_ALERT, \
  QCoreApplication::applicationPid(), QThread::currentThreadId(), this->metaObject()->className(), msg, \
  QString(__FUNCTION__), (int)__LINE__)

#define LOG_CRITICAL(msg) LOGGER_INSTANCE->log(logging::ELogger::ELoggingLevel::E_CRITICAL, \
  QCoreApplication::applicationPid(), QThread::currentThreadId(), this->metaObject()->className(), msg, \
  QString(__FUNCTION__), (int)__LINE__)

#define LOG_ERROR(msg) LOGGER_INSTANCE->log(logging::ELogger::ELoggingLevel::E_ERROR, \
  QCoreApplication::applicationPid(), QThread::currentThreadId(), this->metaObject()->className(), msg, \
  QString(__FUNCTION__), (int)__LINE__)

#define LOG_WARNING(msg) LOGGER_INSTANCE->log(logging::ELogger::ELoggingLevel::E_WARNING, \
  QCoreApplication::applicationPid(), QThread::currentThreadId(), this->metaObject()->className(), msg, \
  QString(__FUNCTION__), (int)__LINE__)

#define LOG_NOTICE(msg) LOGGER_INSTANCE->log(logging::ELogger::ELoggingLevel::E_NOTICE, \
  QCoreApplication::applicationPid(), QThread::currentThreadId(), this->metaObject()->className(), msg, \
  QString(__FUNCTION__), (int)__LINE__)

#define LOG_INFORMATIONAL(msg) LOGGER_INSTANCE->log(logging::ELogger::ELoggingLevel::E_INFORMATIONAL, \
  QCoreApplication::applicationPid(), QThread::currentThreadId(), this->metaObject()->className(), msg, \
  QString(__FUNCTION__), (int)__LINE__)

#define LOG_DEBUG(msg) LOGGER_INSTANCE->log(logging::ELogger::ELoggingLevel::E_DEBUG, \
  QCoreApplication::applicationPid(), QThread::currentThreadId(), this->metaObject()->className(), msg, \
  QString(__FUNCTION__), (int)__LINE__)


#endif // LOGGER_H
