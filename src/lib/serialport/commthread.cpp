#include "commthread.h"
//#include "log/debug.h"
#include <QStringList>
#include "src/logger/logger.h"

CommThread::CommThread(QObject *parent) :
  QThread(parent)
  {
    repeat = false;
    msgSeparator = '\xd';
  }

void CommThread::setSeparator(const char& sep)
  {
    msgSeparator = sep;
  }

CommThread::~CommThread() {
  }

bool CommThread::openPort(const QString &portName, const int &baudRate, const int &byteSize, serial::SerialListener::Parity parity, serial::SerialListener::StopBits bits) {

    if(!comm.open(portName.toStdWString(), baudRate, byteSize, parity, bits)) {
        LOG_ERROR(tr("Open comm port failure") + "(" + portName + ")");
        return false;
      }

    return true;
  }

void CommThread::closePort() {
    comm.close();
  }

void CommThread::run() {

    if(!comm.isOpened()) {
        LOG_INFORMATIONAL(tr("Open serial port before run CommThread"));
        return;
      }

    QString msg;
    QString buff;

    while(comm.isOpened() && isRunning()) {

        msg = comm.read().c_str();

        if(!msg.isEmpty()) {
            buff += msg;

            if(msg.indexOf(msgSeparator) != -1) {
                emit received_data(buff);
                buff.clear();
              }
          }

        if(!msgQueue.isEmpty()) {
            QString msg = msgQueue.first();


            if(comm.write(msg.toStdString())) {
                msgQueue.pop_front();
              }
            else {
                /*LOG_ERROR(QString("Failed to send data to serail port (") + QString::fromWCharArray(comm.portName().c_str()) + QString(")"));*/

                if(!repeat) {
                    msgQueue.pop_front();
                  }
              }

          }

        msleep(40);
      }
  }


void CommThread::send(QString msg) {
    msgQueue.push_back(msg);
  }


void CommThread::directWrite(QString msg) {
    if(isOpenned()) {
        comm.write(msg.toStdString());
      }
  }
