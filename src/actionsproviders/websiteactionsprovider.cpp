#include "websiteactionsprovider.h"
#include <QtNetwork>
#include "tldretriever.h"

WebsiteActionsProvider::WebsiteActionsProvider(QObject *parent) : QObject(parent)
{
    TLDRetriever::retrieve([this](QStringList domains) {
        m_topLevelDomains = domains;
    });
}

void WebsiteActionsProvider::requestPossibleActions(const QString &request)
{
    bool isConversionSuccessful = true;
    QUrl url = convertToUrl(request, &isConversionSuccessful);
    if (isConversionSuccessful) {
        WebsiteAction *action = new WebsiteAction;
        action->setUrl(url);
        emit actionsAvailable(QList<ActionPointer> { ActionPointer(action) });
    }
}

void WebsiteActionsProvider::cancelCurrentRequest()
{
    // Do nothing
}

QUrl WebsiteActionsProvider::convertToUrl(QString rawUrl, bool *ok) const
{
    QString normalizedUrlString = rawUrl.trimmed().toLower();
    bool urlStringHasScheme = QUrl(normalizedUrlString).scheme().length() > 0;

    QString fullUrlString = urlStringHasScheme ? normalizedUrlString : "http://" + normalizedUrlString;
    QUrl convertedUrl(fullUrlString);

    // If the raw URL has scheme, it’s always OK
    bool isUrlOK = urlStringHasScheme || isUrlAppropriate(convertedUrl);
    if (isUrlOK) {
        if (ok) {
            *ok = true;
        }

        return convertedUrl;
    } else {
        if (ok) {
            *ok = false;
        }

        return QUrl();
    }
}

bool WebsiteActionsProvider::isUrlAppropriate(QUrl url) const
{
    if (!url.isValid()) {
        return false;
    }

    if (!url.userName().isEmpty() && url.password().isEmpty()) {
        // Most likely it’s an email (username@domain.com)
        return false;
    }

    QStringList domains = url.host().split('.', QString::SkipEmptyParts);
    if (domains.length() < 2) {
        // A single TLD shouldn’t be a valid URL
        return false;
    }

    if (!m_topLevelDomains.contains(domains.last())) {
        // The TLD is absent in the approved list, it’s not an URL
        return false;
    }

    return true;
}
