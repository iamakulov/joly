#include "emailactionsprovider.h"
#include "tldretriever.h"

EmailActionsProvider::EmailActionsProvider(QObject *parent) : QObject(parent)
{
    TLDRetriever::retrieve([this](QStringList domains) {
        m_topLevelDomains = domains;
    });
}

void EmailActionsProvider::requestPossibleActions(const QString &request)
{
    QString normalizedEmail = request.trimmed().toLower();
    bool isEmailValid = validateEmail(normalizedEmail);

    if (isEmailValid) {
        EmailAction *action = new EmailAction;
        action->setAddress(normalizedEmail);
        emit actionsAvailable(QList<ActionPointer> { ActionPointer(action) });
    }
}

void EmailActionsProvider::cancelCurrentRequest()
{
    // Do nothing
}

bool EmailActionsProvider::validateEmail(const QString &email)
{
    if (!QUrl(email).scheme().isEmpty()) {
        return false;
    }

    // Append HTTP scheme to make QUrl parse the email as HTTP URL
    // and therefore split it to username, domain, etc.
    QUrl emailUrl("http://" + email);

    if (!emailUrl.isValid()) {
        return false;
    }

    if (emailUrl.userName().isEmpty() || emailUrl.host().isEmpty()) {
        return false;
    }

    if ( !(emailUrl.password().isEmpty() ||
          emailUrl.path().isEmpty() ||
          emailUrl.query().isEmpty() ||
          emailUrl.fragment().isEmpty()) ) {
        return false;
    }

    QStringList domains = emailUrl.host().split('.', QString::SkipEmptyParts);
    if (domains.length() < 2) {
        // Don’t accept emails with the host consisting of only one domain
        return false;
    }

    if (!m_topLevelDomains.contains(domains.constLast())) {
        // The TLD is absent in the approved list, it’s not an URL
        return false;
    }

    return true;
}
