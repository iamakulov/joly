#include "calculator.h"

double Calculator::calculate(QString expression, bool *ok)
{
    // Static variable instead of a static member
    // because QScriptEngine must be constructed after QApplication
    static QScriptEngine engine;

    QScriptValue value = engine.evaluate(composeEvaluationExpression(expression));

    if (value.isNumber()) {
        if (ok) {
            *ok = true;
        }
        return value.toNumber();
    } else {
        if (ok) {
            *ok = false;
        }
        return 0;
    }
}

QString Calculator::composeEvaluationExpression(QString expression)
{
    return "(function () { \
        var pi = Math.PI; \
        var e = Math.E; \
        with (Math) { \
            return (" + expression + "); \
        } \
    }())";
}
