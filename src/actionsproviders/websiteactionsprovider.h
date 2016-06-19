#ifndef WEBSITEACTIONSPROVIDER_H
#define WEBSITEACTIONSPROVIDER_H

#include <QObject>
#include "../actions/websiteaction.h"

class WebsiteActionsProvider : public QObject
{
    Q_OBJECT
public:
    explicit WebsiteActionsProvider(QObject *parent = 0);

signals:
    void actionsAvailable(const QList<ActionPointer> &actions);

public slots:
    void requestPossibleActions(const QString &request);
    void cancelCurrentRequest();

private /* methods */:
    QUrl convertToUrl(QString rawUrl) const;
    bool isUrlAppropriate(QUrl url) const;

private /* members */:
    QStringList m_topLevelDomains;
};

#endif // WEBSITEACTIONSPROVIDER_H
