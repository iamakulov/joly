#ifndef EMAILACTIONSPROVIDER_H
#define EMAILACTIONSPROVIDER_H

#include <QObject>
#include "../actions/emailaction.h"

class EmailActionsProvider : public QObject
{
    Q_OBJECT
public:
    explicit EmailActionsProvider(QObject *parent = 0);

signals:
    void actionsAvailable(const QList<ActionPointer> &actions);

public slots:
    void requestPossibleActions(const QString &request);
    void cancelCurrentRequest();

private /* methods */:
    bool validateEmail(const QString &email);

private /* members */:
    QStringList m_topLevelDomains;
};

#endif // EMAILACTIONSPROVIDER_H
