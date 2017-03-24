#ifndef ISMSMODULE_H
#define ISMSMODULE_H

#include "smsmodulemessageheadred.h"
#include "smsmodulemessagecommon.h"

class ISMSModule {
public:
    // this should be the signal known to others
    virtual void stateChanged(SmsModuleMessageHeadred header, SmsModuleMessageCommon *msg) = 0;
    virtual void sendSMS(SmsModuleMessageHeadred header, SmsModuleMessageCommon *msg) = 0;
};

#endif // ISMSMODULE_H
