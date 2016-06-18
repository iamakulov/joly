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

#ifndef APPSINTERFACE_H
#define APPSINTERFACE_H

#include <QObject>
#include <QHash>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>
#include "appinfo.h"
#include "globals.h"
#include "appscontainer.h"
#include "filesystemwatcher.h"
class QJsonObject;
class QFileInfo;

/**
 * @brief The AppsInterface class provides the interface for all user's apps such as installed apps, Chrome Web Store apps etc.
 *
 * The class implements the 'Meyers singleton' pattern.
 * Thus, the new object of the class should be created like this:
 *   AppsInterface *appsInterface = AppsInterface::instance();
 *
 * Currently supported kinds of apps:
 *   - Installed apps
 */
class AppsInterface : public QObject
{
    Q_OBJECT

#ifdef Q_OS_LINUX
    struct LocaleInfo {
        inline bool localeInfoExists() const { return (!lang.isEmpty()); }
        QString lang;
        QString encoding;
        bool containsCountryCode;
    };
#endif

    enum class AppFileKind { InstalledApp, ChromeWebApp };

private:
    explicit AppsInterface(QObject *parent = 0);

public:
    static AppsInterface *instance();

    /**
     * @return true, if user has an app called #appName, otherwise false.
     */
    inline bool exists(const QString &appName) const {
        return m_appsContainer.containsName(appName);
    }

    /**
     * @brief Launches app #appInfo.
     * @return true, if app was launched correctly, otherwise false.
     */
    inline bool open(const AppInfo &appInfo) const {
        return QDesktopServices::openUrl(QUrl::fromLocalFile(appInfo.getAppFile()));
    }

    /**
     * @return All available apps.
     */
    inline QList<AppInfo> getApps() const {
        return m_appsContainer.apps();
    }

signals:

private slots:
    void indexApps();

    void addFile(const QString &filePath);
    void changeFile(const QString &filePath);
    void removeFile(const QString &filePath);

    void addDirectory(const QString &dirPath);
    void removeDirectory(const QString &dirPath);

private /*methods*/:
    void indexLocalApps();

    void indexAppsInDirectory(const QString &dirPath, AppFileKind filesKind);

    QStringList collectAppFilesInDirectory(const QString &dir, AppFileKind filesKind) const;
    bool isAppFile(const QString &filePath, AppFileKind fileKind) const;

    AppInfo extractAppInfoFromFile(const QString &filePath, AppFileKind fileKind) const;
    AppInfo parseLocalAppFile(const QString &filePath) const;

#ifdef Q_OS_LINUX
    LocaleInfo getLocaleInfo(QString varName) const;
    void changeAccordingToLanguage(QString *var, const QString &varName, const QString &varValue) const;
#endif

private /*variables*/:
    AppsContainer m_appsContainer;
    FileSystemWatcher m_watcher;
};

#endif // APPSINTERFACE_H
