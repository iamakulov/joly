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

#include "actionsprovider.h"
#include "appinfo.h"

ActionsProvider::ActionsProvider(QObject *parent) :
    QObject(parent)
{
    connect(&m_calculationProvider, SIGNAL(actionsAvailable(QList<ActionPointer>)), SLOT(newActionsAvailable(QList<ActionPointer>)));
    connect(&m_websiteProvider, SIGNAL(actionsAvailable(QList<ActionPointer>)), SLOT(newActionsAvailable(QList<ActionPointer>)));
    connect(&m_emailProvider, SIGNAL(actionsAvailable(QList<ActionPointer>)), SLOT(newActionsAvailable(QList<ActionPointer>)));
    connect(&m_appsProvider, SIGNAL(actionsAvailable(QList<ActionPointer>)), SLOT(newActionsAvailable(QList<ActionPointer>)));
}

/**
 * @brief Returns a pointer to the actions model.
 */
ActionsModel *ActionsProvider::getModel()
{
    return &m_actionsModel;
}

/**
 * @brief Requests all actions that are possible for string #request.
 */
void ActionsProvider::requestPossibleActions(const QString &request)
{
    m_actionsModel.clear();

    if (!request.isEmpty()) {
        // Calculation provider
        m_calculationProvider.cancelCurrentRequest();
        m_calculationProvider.requestPossibleActions(request);

        // Website provider
        m_websiteProvider.cancelCurrentRequest();
        m_websiteProvider.requestPossibleActions(request);

        // Email provider
        m_emailProvider.cancelCurrentRequest();
        m_emailProvider.requestPossibleActions(request);

        // Apps provider
        m_appsProvider.cancelCurrentRequest();
        m_appsProvider.requestPossibleActions(request);
    }
}

/**
 * @brief Handles new #actions emitted by specific action providers.
 */
void ActionsProvider::newActionsAvailable(const QList<ActionPointer> &actions)
{
    Q_ASSERT(actions.length() != 0);
    if (actions.length() == 0)
        return;

    m_actionsModel.addSection(actions.first()->getKind(), actions);
}
