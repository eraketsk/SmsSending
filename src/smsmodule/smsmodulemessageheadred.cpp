#include "smsmodulemessageheadred.h"
#include <QString>
#include <QObject>

SmsModuleMessageHeadred::SmsModuleMessageHeadred()
{

}

QString SmsModuleMessageHeadred::typeToString()
{
    switch (type)
    {
    case E_GTs5260:
        return QObject::tr("GT-S5260");
    default:
        return QObject::tr("UNKOWN");
    }
}

QString SmsModuleMessageHeadred::typeToString(const EModuleType& value)
{
    switch (value)
    {
    case E_GTs5260:
        return QObject::tr("GT-S5260");
    default:
        return QObject::tr("UNKOWN");
    }
}
