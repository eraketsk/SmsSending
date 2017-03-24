#include "gts5260smsentry.h"
#include <QVariant>

Gts5260SmsEntry::Gts5260SmsEntry(QObject *parent) : QObject(parent)
{
    this->setProperty("sendingStarted", false);
    this->setProperty("wasSent", false);
    this->setProperty("sendingReportWasRecieved", false);
    this->setProperty("deliveringReportWasRecieved", false);
}
