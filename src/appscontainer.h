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

#ifndef APPSCONTAINER_H
#define APPSCONTAINER_H

#include <QObject>
#include "appinfo.h"

class AppsContainer : public QObject
{
    Q_OBJECT
public:
    explicit AppsContainer(QObject *parent = 0);

    QList<AppInfo> apps() const;

    QList<AppInfo> getByName(const QString &name) const;
    AppInfo getByFile(const QString &fileName) const;
    bool containsName(const QString &name) const;
    bool containsFile(const QString &fileName) const;

    bool add(const QString &fileName, const AppInfo& app);
    void set(const QString &fileName, const AppInfo& app);
    bool remove(const QString &fileName);
    bool removeByRegExp(const QRegExp &regExp);

signals:

public slots:

private /*methods*/:

private /*variables*/:
    QHash<QString, AppInfo> m_appsByName;
    QHash<QString, QHash<QString, AppInfo>::Iterator> m_appsByFile;
};

#endif // APPSCONTAINER_H
