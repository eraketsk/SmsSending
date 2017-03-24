#include "gts5260smsmodule.h"
#include "src/logger/logger.h"

Gts5260SmsModule::Gts5260SmsModule(QObject *parent) : QObject(parent)
{

}

void Gts5260SmsModule::sendSMS(SmsModuleMessageHeadred header, SmsModuleMessageCommon *msg)
{
    messageDump(header, msg);
}

void Gts5260SmsModule::messageDump(SmsModuleMessageHeadred header, SmsModuleMessageCommon *msg)
{
    QString logMessage = "";
    logMessage += tr("A message was received. Type ") + header.typeToString() + tr(".");
    if (header.getType() != SmsModuleMessageHeadred::E_GTs5260)
    {
        LOG_DEBUG(logMessage);
        LOG_WARNING("Received message type is not expected!");
        return;
    }

    LOG_DEBUG(logMessage);
}
