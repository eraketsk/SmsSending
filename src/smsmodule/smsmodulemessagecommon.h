#ifndef SMSMODULEMESSAGECOMMON_H
#define SMSMODULEMESSAGECOMMON_H

#include <QObject>
#include <QList>

class SmsModuleMessageCommon : public QObject
{
    Q_OBJECT
public:
    explicit SmsModuleMessageCommon(QObject *parent = 0);
    virtual QList<QObject>* getData() = 0;
    virtual setData(QList<QObject>*) = 0;

private:
    QList<QObject> data;
};

#endif // SMSMODULEMESSAGECOMMON_H
