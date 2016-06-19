#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QScriptEngine>

class Calculator
{
public:    
    static double calculate(QString expression, bool *ok = nullptr);

private /* methods */:
    static QString composeEvaluationExpression(QString expression);
};

#endif // CALCULATOR_H
