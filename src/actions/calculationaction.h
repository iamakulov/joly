#ifndef CALCULATORACTION_H
#define CALCULATORACTION_H

#include "action.h"

class CalculationAction : public Action
{
public:
    CalculationAction();

    virtual void launch() const;
    virtual QIcon getIcon() const;
    virtual QString getText() const;
    virtual QString getFormattedText() const;
    virtual Kind getKind() const;

    inline void setResult(QString result)
    {
        m_result = result;
    }

private:
    QString m_result;
};

#endif // CALCULATORACTION_H
