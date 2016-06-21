#include "tldretriever.h"
#include <QtNetwork>

QNetworkAccessManager TLDRetriever::m_networkManager;
QStringList TLDRetriever::m_domains;
const QUrl TLDRetriever::m_tldListUrl(QString("http://data.iana.org/TLD/tlds-alpha-by-domain.txt"));

void TLDRetriever::retrieve(std::function<void(QStringList)> callback)
{
    if (m_domains.length() > 0) {
        callback(m_domains);
        return;
    }

    QNetworkReply *reply = m_networkManager.get(QNetworkRequest(m_tldListUrl));
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        m_domains = parseDomains(QString(reply->readAll()));

        callback(m_domains);

        reply->deleteLater();
    });
}

QStringList TLDRetriever::parseDomains(QString data)
{
    QStringList result;

    for (const QString &rawLine : data.split("\n")) {
        QString line = rawLine.trimmed();

        // Empty line or comment
        if (line.isEmpty() || line.startsWith('#')) {
            continue;
        }

        result.append(line.toLower());
    }

    return result;
}
