#ifndef COMMTHREAD_H
#define COMMTHREAD_H
#include <QThread>
#include <QStringList>
#include "src/lib/serialport/seriallistener.h"

class CommThread : public QThread
{
    Q_OBJECT
public:
    explicit CommThread(QObject *parent = 0);

    ~CommThread();

    void setSeparator(const char &sep);
    char separotor() const;

    bool openPort(const QString &portName,
                  const int     &baudRate = 115200,
                  const int     &byteSize = 8,
                  serial::SerialListener::Parity    parity = serial::SerialListener::None,
                  serial::SerialListener::StopBits  bits   = serial::SerialListener::Sb_One);

    void repeatFailed(bool repeat);
    bool isRepeatsFailed() const;

    void closePort();

    bool hasMsgInQueue() const { return !msgQueue.isEmpty(); }
    void directWrite(QString msg);
    bool isOpenned() const { return comm.isOpened(); }
protected:

    void run();


signals:
    /*! Signal emitted when received some data from serial port*/
    void received_data(QString msg);
    /*! This signal emitted when port is closed or no longer available */
    void lost_port();
public slots:

    /*! Send message to serial port */
    void send(QString msg);
private:
    serial::SerialListener      comm;           //! The object of a com port
    QStringList                 msgQueue;       //! Queue of messages for send to comm
    bool                        repeat;         //! Repeat message if send failed
    char                        msgSeparator;   //! Separator of messages
};

#endif // COMMTHREAD_H
