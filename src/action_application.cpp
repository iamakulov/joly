/***************************************
 * Joly. Connect your web and your computer in the one place.
 * Copyright (C) 2012-2013 Ivan Akulov <gxoptg@gmail.com>
 *
 * This file is the part of Joly.
 *
 * Joly is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Joly is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Joly. If not, see <http://www.gnu.org/licenses/>.
 **************************************/

#include "action.h"
#include "appsinterface.h"
#include "appinfo.h"

/*
 * Class declaration is located in "action.h" file.
 */

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
