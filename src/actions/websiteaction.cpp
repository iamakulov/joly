#include "websiteaction.h"

#include <QDesktopServices>

WebsiteAction::WebsiteAction()
    : Action()
{

}

/**
 * @brief Launches the application that is represented by this action.
 */
void WebsiteAction::launch() const
{
    QDesktopServices::openUrl(m_url);
}

/**
 * @brief Returns an icon that represents the action.
 */
QIcon WebsiteAction::getIcon() const
{
    return QIcon(":/images/website.png");
}

/**
 * @brief Returns a text that represents the action.
 */
QString WebsiteAction::getText() const
{
    return m_url.toString();
}

/**
 * @brief Returns a formatted text to display in GlobalLine completer.
 */
QString WebsiteAction::getFormattedText() const
{
    return getText();
}

/**
 * @brief Returns a kind of the action.
 */
Action::Kind WebsiteAction::getKind() const
{
    return Action::Kind::Kind_Website;
}
