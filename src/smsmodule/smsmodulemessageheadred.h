#ifndef SMSMODULEMESSAGEHEADRED_H
#define SMSMODULEMESSAGEHEADRED_H

#include <QString>

class SmsModuleMessageHeadred
{
public:
    enum EModuleType
      {
        E_GTs5260,
        UNKNOWN
      };

    SmsModuleMessageHeadred();
    EModuleType getType() {return this->type;}
    void setType(const EModuleType& newValue) {this->type = newValue;}
    static QString typeToString(const EModuleType& value);
    QString typeToString();
private:
    EModuleType type = UNKNOWN;
};

#endif // SMSMODULEMESSAGEHEADRED_H
