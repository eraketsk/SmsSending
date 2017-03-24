#ifndef SMSENTRY_H
#define SMSENTRY_H

#include <QObject>
#include <QString>
#include <QDateTime>

class Gts5260SmsEntry  : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(int customerId MEMBER m_customerId)
    Q_PROPERTY(QString customerName MEMBER m_customerName)
    Q_PROPERTY(QString customerCellNumber MEMBER m_customerCellNumber)
    Q_PROPERTY(QString messageText MEMBER m_messageText)
    Q_PROPERTY(QDateTime sendingStartedDateTime MEMBER m_sendingStartedDateTime)
    Q_PROPERTY(bool sendingStarted MEMBER m_sendingStarted NOTIFY sendingStarted)
    Q_PROPERTY(QDateTime sentDateTime MEMBER m_sentDateTime)
    Q_PROPERTY(bool wasSent MEMBER m_wasSent NOTIFY wasSent)
    Q_PROPERTY(QDateTime sendingReportDateTime MEMBER m_sendingReportDateTime)
    Q_PROPERTY(bool sendingReportWasRecieved MEMBER m_sendingReportWasRecieved NOTIFY sendingReportWasRecieved)
    Q_PROPERTY(QDateTime deliveringReportDateTime MEMBER m_deliveringReportDateTime)
    Q_PROPERTY(bool deliveringReportWasRecieved MEMBER m_deliveringReportWasRecieved NOTIFY deliveringReportWasRecieved)
    Q_PROPERTY(int smsId MEMBER m_smsId NOTIFY smsIdWasSet)

    explicit Gts5260SmsEntry(QObject *parent = 0);
signals:
    void sendingStarted(const bool &newState);
    void wasSent(const bool &newState);
    void sendingReportWasRecieved(const bool &newState);
    void deliveringReportWasRecieved(const bool &newState);
    void smsIdWasSet(const int &newState);
private:
    int m_customerId = 0;
    QString m_customerName = "";
    QString m_customerCellNumber = "";
    QString m_messageText = "";
    QDateTime m_sendingStartedDateTime;
    bool m_sendingStarted = false;
    QDateTime m_sentDateTime;
    bool m_wasSent = false;
    QDateTime m_sendingReportDateTime;
    bool m_sendingReportWasRecieved = false;
    QDateTime m_deliveringReportDateTime;
    bool m_deliveringReportWasRecieved = false;
    int m_smsId = -1;
};

#endif // SMSENTRY_H
