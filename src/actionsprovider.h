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

#ifndef ACTIONSPROVIDER_H
#define ACTIONSPROVIDER_H

#include <QObject>
#include "actionsmodel.h"
#include "actionsprovider_application.h"

class Action;

/**
 * @brief The ActionsProvider class provides actions for GlobalLine gadget for requested line of text.
 *
 * Because methods of generating actions of different kinds are very different,
 * these actions are generated in additional classes like ApplicationActionsProvider, LinkActionsProvider etc.
 * Also, there is the additional class HistoryProvider, which isn't associated with any of action kinds,
 * but provides history of requests.
 *
 * "Action": see "action.h".
 */
class ActionsProvider : public QObject
{
    Q_OBJECT
public:
    explicit ActionsProvider(QObject *parent = 0);

    ActionsModel *getModel();

public slots:
    void requestPossibleActions(const QString &request);

private slots:
    void newActionsAvailable(const QList<ActionPointer> &actions);

private /*variables*/:
    ApplicationActionsProvider m_appsProvider;
    /***** Future
    HistoryProvider m_historyProvider;
    FileSystemEntryActionsProvider m_filesProvider;
    LinkActionsProvider m_linksProvider;
    InternetSearchActionsProvider m_searchesProvider;
    ToolActionsProvider m_toolsProvider;
    */

    ActionsModel m_actionsModel;
    /* Note:
     * To add a new action kind, you must:
     *
     * 1. Create a class derived from QObject with the interface:
     *
        class __KIND__ActionsProvider : public QObject
        {
            Q_OBJECT
        public:
            explicit __KIND__ActionsProvider(QObject *parent = 0);

        signals:
            void actionsAvailable(const QList<ActionPointer> &actions);

        public slots:
            void requestPossibleActions(const QString &request);
            void cancelCurrentRequest();
        };
     *
     * (Replace __KIND__ with the name of the kind.)
     *
     * 2. Add an object of this class to variables section of ActionsProvider class.
     * 3. In this class, connect "actionsAvailable()" signal of the object to "newActionsAvailable()" slot of this class.
     * 4. Add requesting to ActionsProvider::requestPossibleActions().
     */
};

#endif // ACTIONSPROVIDER_H
