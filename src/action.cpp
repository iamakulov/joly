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
#include <QHash>
#include <QMutex>

int g_availableId = 0;
QHash<int, ActionPointer> g_actionsMap;

QMutex getNewIdMutex;

/**
 * @brief Returns a new action id based on #g_availableId value.
 *
 * This function is thread-safe.
 */
int getNewId()
{
    getNewIdMutex.lock();

    int newId = g_availableId;
    ++g_availableId;

    getNewIdMutex.unlock();

    return newId;
}

Action::Action()
{
    m_id = getNewId();
    g_actionsMap.insert(m_id, ActionPointer(this));
}

Action::~Action()
{
    g_actionsMap.remove(m_id);
}

int Action::id()
{
    return m_id;
}

ActionPointer Action::byId(int id)
{
    return g_actionsMap.value(id, ActionPointer(nullptr));
}
