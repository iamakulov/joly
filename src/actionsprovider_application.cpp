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

#include "actionsprovider_application.h"
#include <QtCore>
#include <QDebug>
#include "appinfo.h"
#include "appsinterface.h"

ApplicationActionsProvider::ApplicationActionsProvider(QObject *parent) :
    QObject(parent)
{
    m_appsInterface = AppsInterface::instance();
}

/**
 * @brief Requests AppInfo objects from AppsInterface filtered by the string #request.
 */
void ApplicationActionsProvider::requestPossibleActions(const QString &request)
{
    QList<AppInfo> appsList = m_appsInterface->getFilteredList(request);

    QList<ActionPointer> actions;
    for (auto app : appsList) {
        actions.append( convertAppInfoToAction(app) );
    }

    if (actions.length() != 0)
        emit actionsAvailable(actions);
}

/**
 * @brief Cancels current request.
 *
 * In fact, it does nothing, because the request to retrieve applications is made synchroniously,
 * therefore it can't be cancelled.
 */
void ApplicationActionsProvider::cancelCurrentRequest()
{
    return;
}

/**
 * @brief Converts AppInfo object to Action.
 * @param app AppInfo object to convert.
 * @return Pointer to converted Action.
 */
ActionPointer ApplicationActionsProvider::convertAppInfoToAction(const AppInfo &appInfo)
{
    ApplicationAction *appAction = new ApplicationAction;
    appAction->setInfo(appInfo);
    return ActionPointer((Action*)appAction);
}
