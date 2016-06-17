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

#include "appscontainer.h"

AppsContainer::AppsContainer(QObject *parent) :
    QObject(parent)
{
}

QList<AppInfo> AppsContainer::apps() const
{
    return m_appsByName.values();
}

QList<AppInfo> AppsContainer::getByName(const QString &name) const
{
    return m_appsByName.values(name);
}

AppInfo AppsContainer::getByFile(const QString &fileName) const
{
    auto iterator = m_appsByFile.value(fileName);
    return iterator.value();
}

bool AppsContainer::containsName(const QString &name) const
{
    return m_appsByName.contains(name);
}

bool AppsContainer::containsFile(const QString &fileName) const
{
    return m_appsByFile.contains(fileName);
}

bool AppsContainer::add(const QString &fileName, const AppInfo &app)
{
    if (m_appsByFile.contains(fileName))
        return false;

    auto iterator = m_appsByName.insertMulti(app.getName(), app);
    m_appsByFile.insert(fileName, iterator);
    return true;
}

void AppsContainer::set(const QString &fileName, const AppInfo &app)
{
    remove(fileName);
    add(fileName, app);
}

bool AppsContainer::remove(const QString &fileName)
{
    if (!m_appsByFile.contains(fileName))
        return false;

    auto iterator = m_appsByFile.value(fileName);
    m_appsByName.erase(iterator);
    m_appsByFile.remove(fileName);
    return true;
}

bool AppsContainer::removeByRegExp(const QRegExp &regExp)
{
    bool foundMatch = false;

    for (auto it = m_appsByFile.begin(); it != m_appsByFile.end(); ++it) {
        QString fileName = it.key();
        if (regExp.exactMatch(fileName)) {
            foundMatch = true;

            m_appsByName.erase(it.value());
            m_appsByFile.erase(it);
        }
    }

    return foundMatch;
}
