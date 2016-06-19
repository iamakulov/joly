#include "applicationaction.h"
#include "appsinterface.h"
#include "appinfo.h"

ApplicationAction::ApplicationAction()
    : Action()
{

}

/**
 * @brief Launches the application that is represented by this action.
 */
void ApplicationAction::launch() const
{
    AppsInterface *appsInterface = AppsInterface::instance();
    appsInterface->open(m_info);
}

/**
 * @brief Returns an icon that represents the action.
 */
QIcon ApplicationAction::getIcon() const
{
    QIcon icon = m_info.getIcon();

    if (icon.isNull()) {
        // TODO: set default application icon
    }

    return icon;
}

/**
 * @brief Returns a text that represents the action.
 */
QString ApplicationAction::getText() const
{
    return m_info.getName();
}

/**
 * @brief Returns a formatted text to display in GlobalLine completer.
 */
QString ApplicationAction::getFormattedText() const
{
    return getText();
}

/**
 * @brief Returns a kind of the action.
 */
Action::Kind ApplicationAction::getKind() const
{
    return Action::Kind::Kind_Application;
}
