#include "emailaction.h"

#include <QDesktopServices>

EmailAction::EmailAction()
    : Action()
{

}

/**
 * @brief Launches the application that is represented by this action.
 */
void EmailAction::launch() const
{
    QDesktopServices::openUrl(QUrl("mailto:" + m_address));
}

/**
 * @brief Returns an icon that represents the action.
 */
QIcon EmailAction::getIcon() const
{
    return QIcon(":/images/email.png");
}

/**
 * @brief Returns a text that represents the action.
 */
QString EmailAction::getText() const
{
    return m_address;
}

/**
 * @brief Returns a formatted text to display in GlobalLine completer.
 */
QString EmailAction::getFormattedText() const
{
    return getText();
}

/**
 * @brief Returns a kind of the action.
 */
Action::Kind EmailAction::getKind() const
{
    return Action::Kind::Kind_Email;
}
