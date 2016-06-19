#ifndef CALCULATIONACTIONSPROVIDER_H
#define CALCULATIONACTIONSPROVIDER_H

#include <QObject>
#include "../actions/calculationaction.h"

class CalculationActionsProvider : public QObject
{
    Q_OBJECT
public:
    explicit CalculationActionsProvider(QObject *parent = 0);

signals:
    void actionsAvailable(const QList<ActionPointer> &actions);

public slots:
    void requestPossibleActions(const QString &request);
    void cancelCurrentRequest();
};

#endif // CALCULATIONACTIONSPROVIDER_H
