#ifndef TLDRETRIEVER_H
#define TLDRETRIEVER_H

#include <QNetworkAccessManager>
#include <QObject>
#include <functional>

class TLDRetriever
{
public:
    static void retrieve(std::function<void(QStringList)> callback);

private /* methods */:
    static QStringList parseDomains(QString data);

private /* members */:
    static QNetworkAccessManager m_networkManager;
    static QStringList m_domains;
    static const QUrl m_tldListUrl;
};

#endif // TLDRETRIEVER_H
