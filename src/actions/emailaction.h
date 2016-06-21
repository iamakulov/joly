#ifndef CALCULATORACTION_H
#define CALCULATORACTION_H

#include "action.h"

class EmailAction : public Action
{
public:
    EmailAction();

    virtual void launch() const;
    virtual QIcon getIcon() const;
    virtual QString getText() const;
    virtual QString getFormattedText() const;
    virtual Kind getKind() const;

    inline void setAddress(QString address)
    {
        m_address = address;
    }

private:
    QString m_address;
};

#endif // CALCULATORACTION_H
