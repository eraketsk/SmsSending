#ifndef GTS5260SMSMODULE_H
#define GTS5260SMSMODULE_H

#include <QObject>
#include "src/smsmodule/ismsmodule.h"

class Gts5260SmsModule : public QObject, public ISMSModule
{
    Q_OBJECT
public:
    explicit Gts5260SmsModule(QObject *parent = 0);

signals:
     void stateChanged(SmsModuleMessageHeadred header, SmsModuleMessageCommon *msg);
public slots:
     void sendSMS(SmsModuleMessageHeadred header, SmsModuleMessageCommon *msg);

private:
     void messageDump(SmsModuleMessageHeadred header, SmsModuleMessageCommon *msg);
};

#endif // GTS5260SMSMODULE_H
