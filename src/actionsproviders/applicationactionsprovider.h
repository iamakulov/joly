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

#ifndef ACTIONSPROVIDER_APPLICATION_H
#define ACTIONSPROVIDER_APPLICATION_H

#include <QObject>
#include "../actions/applicationaction.h"

class AppsInterface;

/**
 * @brief The ApplicationActionsProvider class provides actions of Application kind for requested string.
 *
 * See "actionsprovider.h" for more documentation.
 */
class ApplicationActionsProvider : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationActionsProvider(QObject *parent = 0);

signals:
    void actionsAvailable(const QList<ActionPointer> &actions);

public slots:
    void requestPossibleActions(const QString &request);
    void cancelCurrentRequest();

private /*methods*/:
    QList<AppInfo> findRelevantApps(const QList<AppInfo> &apps, QString request) const;
    QList<AppInfo> filterApps(const QList<AppInfo> &apps, QString request) const;
    QList<QPair<AppInfo, int>> assignAppRelevance(const QList<AppInfo> &apps, QString request) const;
    QList<AppInfo> getAppsSortedByRelevance(const QList<QPair<AppInfo, int>> &apps) const;
    ActionPointer convertAppInfoToAction(const AppInfo &appInfo);

private /*variables*/:
    AppsInterface *m_appsInterface;
};

#endif // ACTIONSPROVIDER_APPLICATION_H
