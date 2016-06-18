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
    QList<AppInfo> appsList = m_appsInterface->getApps();
    QList<AppInfo> filteredList = findRelevantApps(appsList, request);

    QList<ActionPointer> actions;
    for (auto app : filteredList) {
        actions.append( convertAppInfoToAction(app) );
    }

    if (actions.length() != 0) {
        emit actionsAvailable(actions);
    }
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

QList<AppInfo> ApplicationActionsProvider::findRelevantApps(const QList<AppInfo> &apps, QString request) const
{
    if (request.isEmpty()) {
        return apps;
    }

    QList<AppInfo> filteredApps = filterApps(apps, request);
    QList<QPair<AppInfo, int>> appsWithRelevance = assignAppRelevance(filteredApps, request);
    QList<AppInfo> sortedApps = getAppsSortedByRelevance(appsWithRelevance);

    return sortedApps;
}

QList<AppInfo> ApplicationActionsProvider::filterApps(const QList<AppInfo> &apps, QString request) const
{
    QList<AppInfo> result;

    for (const AppInfo &appInfo : apps) {
        QString joinedKeywords = appInfo.getKeywords().join("");
        if (appInfo.getName().contains(request, Qt::CaseInsensitive) ||
                appInfo.getGenericName().contains(request, Qt::CaseInsensitive) ||
                joinedKeywords.contains(request, Qt::CaseInsensitive)) {
            result.append(appInfo);
        }
    }

    return result;
}

QList<QPair<AppInfo, int>> ApplicationActionsProvider::assignAppRelevance(const QList<AppInfo> &apps, QString request) const
{
    QList<QPair<AppInfo, int>> result;

    for (const AppInfo &appInfo : apps) {
        int relevance = 0;

        // 1
        if (appInfo.getName().contains(request, Qt::CaseInsensitive)) {
            relevance += 5;
        }

        // 2
        QStringList nameWords = appInfo.getName().split(" ", QString::SkipEmptyParts);
        int wordStartingCount = std::count_if(nameWords.constBegin(), nameWords.constEnd(), [=](QString word) {
            return word.startsWith(request);
        });
        relevance += wordStartingCount * 2;

        // 3
        if (appInfo.getGenericName().contains(request, Qt::CaseInsensitive)) {
            relevance += 2;
        }

        // 4
        QStringList keywords = appInfo.getKeywords();
        int occurrenceCount = std::count_if(keywords.constBegin(), keywords.constEnd(), [=](QString keyword) {
            return keyword.contains(request);
        });
        if (occurrenceCount > 0) {
            relevance += 2;
        }

        result.append(qMakePair(appInfo, relevance));
    }

    return result;
}

QList<AppInfo> ApplicationActionsProvider::getAppsSortedByRelevance(const QList<QPair<AppInfo, int>> &appRelevanceList) const
{
    QList<QPair<AppInfo, int>> sortedPairs = appRelevanceList;
    qSort(sortedPairs.begin(), sortedPairs.end(), [](auto left, auto right) {
        // Sort in descending order by the relevance
        return right.second < left.second;
    });

    QList<AppInfo> sortedApps;
    for (const auto pair : sortedPairs) {
        sortedApps.append(pair.first);
    }

    return sortedApps;
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
