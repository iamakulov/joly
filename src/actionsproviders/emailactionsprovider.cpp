#include "emailactionsprovider.h"
#include "../calculator.h"

CalculationActionsProvider::CalculationActionsProvider(QObject *parent) : QObject(parent)
{

}

void CalculationActionsProvider::requestPossibleActions(const QString &request)
{
    bool isCalculationSuccessful = false;
    double value = Calculator::calculate(request, &isCalculationSuccessful);

    bool isRequestANumber;
    // Ignore the returned parsed value and use just the correctness flag
    request.toDouble(&isRequestANumber);

    if (isCalculationSuccessful && !isRequestANumber) {
        CalculationAction *action = new CalculationAction;
        action->setResult(QString::number(value));
        emit actionsAvailable(QList<ActionPointer> { ActionPointer(action) });
    }
}

void CalculationActionsProvider::cancelCurrentRequest()
{
    // Do nothing
}
