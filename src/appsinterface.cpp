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

#include "appsinterface.h"
#include "globals.h"
#include <QtCore>
#include <QFileIconProvider>

AppsInterface::AppsInterface(QObject *parent) :
    QObject(parent)
{
    connect(&m_watcher, SIGNAL(fileAdded(QString)), SLOT(addFile(QString)));
    connect(&m_watcher, SIGNAL(fileChanged(QString)), SLOT(changeFile(QString)));
    connect(&m_watcher, SIGNAL(fileRemoved(QString)), SLOT(removeFile(QString)));
    connect(&m_watcher, SIGNAL(directoryAdded(QString)), SLOT(addDirectory(QString)));
    connect(&m_watcher, SIGNAL(directoryRemoved(QString)), SLOT(removeDirectory(QString)));

    indexApps();
}

/**
 * @brief Returns the only instance of the class, according to Singleton pattern.
 */
AppsInterface *AppsInterface::instance()
{
    /* This realisation is thread-safe only in C++11.
     * Joly is compiled with C++11 support according to qmake flags in jolyapp.pro file.
     */
    static AppsInterface inst;
    return &inst;
}

/**
 * @brief Indexes list of apps.
 */
void AppsInterface::indexApps()
{
    indexLocalApps();
    // Future: indexChromeApps();
}

/**
 * @brief Parses file #filePath, and, if it's an app file, adds it to apps list.
 * It is a slot for signals from FileSystemWatcher class.
 */
void AppsInterface::addFile(const QString &filePath)
{
    AppInfo app;
    if (isAppFile(filePath, AppFileKind::InstalledApp)) {
        app = extractAppInfoFromFile(filePath, AppFileKind::InstalledApp);
    }
    else if (isAppFile(filePath, AppFileKind::ChromeWebApp)) {
        app = extractAppInfoFromFile(filePath, AppFileKind::ChromeWebApp);
    }
    else {
        Q_UNREACHABLE();
    }

    if (!app.isNull())
        m_appsContainer.add(filePath, app);
}

/**
 * @brief Parses file #filePath, and, if it's an app file, updates app info of corresponding app.
 * It is a slot for signals from FileSystemWatcher class.
 */
void AppsInterface::changeFile(const QString &filePath)
{
    AppInfo app;
    if (isAppFile(filePath, AppFileKind::InstalledApp)) {
        app = extractAppInfoFromFile(filePath, AppFileKind::InstalledApp);
    }
    else if (isAppFile(filePath, AppFileKind::ChromeWebApp)) {
        app = extractAppInfoFromFile(filePath, AppFileKind::ChromeWebApp);
    }
    else {
        Q_UNREACHABLE();
    }

    if (!app.isNull())
        m_appsContainer.set(filePath, app);
}

/**
 * @brief Removes app that corresponds app file #filePath.
 * It is a slot for signals from FileSystemWatcher class.
 */
void AppsInterface::removeFile(const QString &filePath)
{
    m_appsContainer.remove(filePath);
}

/**
 * @brief Parses all app files in directory #dirPath and subdirectories and pushes them to apps container.
 * It is a slot for signals from FileSystemWatcher class.
 */
void AppsInterface::addDirectory(const QString &dirPath)
{
    QDirIterator it(dirPath, QDir::NoDotAndDotDot, QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
    while (it.hasNext()) {
        it.next();

        QFileInfo fileInfo = it.fileInfo();
        // Prevending infinite loop in case when symlink in current folder links to folder we're in.
        if (fileInfo.symLinkTarget() != it.path()) {
            if (fileInfo.isFile())
                addFile(fileInfo.filePath());
            else if (fileInfo.isBundle())
                addDirectory(fileInfo.filePath());
            else // It may be a bundle (QFileInfo::isBundle()), but this case is unimplemented.
                Q_ASSERT(false);
        }
    }

    m_watcher.addDirectory(dirPath);
}

/**
 * @brief Removes all apps that corresponds files that are located on directory #dirPath or its subdirectories.
 * It is a slot for signals from FileSystemWatcher class.
 */
void AppsInterface::removeDirectory(const QString &dirPath)
{
    m_appsContainer.removeByRegExp(QRegExp("^" + dirPath));
}

/**
 * @brief Indexes list of apps installed on the user's OS.
 */
void AppsInterface::indexLocalApps()
{
    QStringList appsDirs = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);

    // NOTE: temporary workaround for the bug https://bugreports.qt-project.org/browse/QTBUG-40565
#ifdef Q_OS_WIN
    // STOPPED HERE
//    QString globalStartMenu = "%ProgramData%/Microsoft/Windows/Start Menu/Programs";
//    QString programDataDir =
#endif

    for (QString dir : appsDirs) {
        indexAppsInDirectory(dir, AppFileKind::InstalledApp);
    }
}

/**
 * @brief Parses all app files that correspond #filesKind in directory #dirPath and subdirectries and pushes them to app container.
 */
void AppsInterface::indexAppsInDirectory(const QString &dirPath, AppsInterface::AppFileKind filesKind)
{
    QStringList appFiles = collectAppFilesInDirectory(dirPath, filesKind);

    // Process every file and push it to apps container
    for (QString filePath : appFiles) {
        AppInfo app = extractAppInfoFromFile(filePath, AppFileKind::InstalledApp);
        if (!app.isNull()) {
            m_appsContainer.add(filePath, app);
            m_watcher.addDirectory(filePath);
        }
    }
}

/**
 * @brief Goes through a directory #dir and its subdirectories and collects paths of all files that correspond #filesKind.
 * @param dir Dir to start from
 * @param filesKind File kind to filter all files by
 * @return List of collected file paths
 */
QStringList AppsInterface::collectAppFilesInDirectory(const QString &dir, AppFileKind filesKind) const
{
    QStringList result;

    // Does QDir::Files automatically mean QDir::NoDotAndDotDot?
    QDirIterator it(dir, QDir::NoDotAndDotDot | QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString file = it.next();
        QFileInfo fileInfo = it.fileInfo();

        if (!fileInfo.isHidden() && isAppFile(file, filesKind)) {
            result.append(file);
        }
    }

    return result;
}

/**
 * @brief Checks whether given #file is of kind #fileKind.
 * @return True, if #file corresponds #fileKind, otherwise false.
 */
bool AppsInterface::isAppFile(const QString &filePath, AppsInterface::AppFileKind fileKind) const
{
    QFileInfo file(filePath);
    if (fileKind == AppFileKind::InstalledApp) {
#ifdef Q_OS_WIN
        return file.isSymLink() && QFileInfo(file.symLinkTarget()).isExecutable();
#elif defined(Q_OS_LINUX)
        return file.suffix() == "desktop";
#else
#error OS is not supported
#endif
    }
    else if (fileKind == AppFileKind::ChromeWebApp){
        Q_UNREACHABLE();
        return false;
    } else {
        Q_UNREACHABLE();
        return false;
    }

}

/**
 * @brief Parses app file to AppInfo object.
 * @param filePath App file to parse.
 * @param fileKind Kind of file #filePath.
 * @param error Will be set to true, if error occured during parsing process.
 * @return Parsed AppInfo object.
 */
AppInfo AppsInterface::extractAppInfoFromFile(const QString &filePath, AppsInterface::AppFileKind fileKind) const
{
    switch (fileKind) {
    case AppFileKind::InstalledApp:
        return parseLocalAppFile(filePath);
        break;
    case AppFileKind::ChromeWebApp:
        Q_UNIMPLEMENTED();
        return AppInfo();
        break;
    default:
        Q_UNREACHABLE();
        return AppInfo();
    }
}

/**
 * @brief Parses installed app file to AppInfo object.
 * @param filePath App file to parse.
 * @return Parsed object.
 */
AppInfo AppsInterface::parseLocalAppFile(const QString &filePath) const
{
#ifdef Q_OS_LINUX

    // Opening file
    QFile file(filePath);
    if (Q_UNLIKELY(!file.open(QIODevice::ReadOnly))) {
        qWarning() << "File" << filePath << "can't be opened";
        return AppInfo();
    }

    QTextStream in(&file);

    // Preparing loop
    bool saveThisApp = true;
    bool passedDesktopEntryHeader = false;
    const QString currentDesktopEnvironment = QProcessEnvironment::systemEnvironment().value("XDG_CURRENT_DESKTOP");

    QString appName;
    QString appIconName;
    QString appExec;
    QString appRunFolder;
    QString appGenericName;
    QString appKeywords;

    // Processing file; see http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s02.html
    while (!in.atEnd() && saveThisApp) {
        QString line = in.readLine();

        // replacing possible escape sequences; see http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s03.html
        line.replace("\\s", " ");
        line.replace("\\n", "\n");
        line.replace("\\t", "\t");
        line.replace("\\r", "\r");
        line.replace("\\\\", "\\");

        line = line.trimmed();

        // if it's a comment or an empty line
        if (line.isEmpty() || line.startsWith('#'))
            continue;

        // if it's the title of the "Desktop Entry" group
        // it's the group that contains the needed variables
        if (line == "[Desktop Entry]") {
            passedDesktopEntryHeader = true;
            continue;
        }

        // if it's the title of the other group
        if (line.startsWith('[')) {
            // we are leaving the loop if desktopEntryGroup == true, i.e. if this group was already processed
            // there won't be continuations of it in this file
            if (passedDesktopEntryHeader)
                break;
            else
                continue;
        }

        // now it's (most likely) variable
        QStringList separatedLine = line.split('=');

        // prevending wrong format of file
        if (Q_UNLIKELY(separatedLine.length() != 2)) {
            qWarning() << qPrintable(trUtf8("Could not process file %1 in AppsInterface: wrong format of line %2").arg(filePath).arg(line));
            saveThisApp = false;
            break;
        }

        QString varName = separatedLine.first().trimmed();
        QString varValue = separatedLine.last().trimmed();

        // processing variable; see http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s05.html
        if (varName == "Type") {
            if (varValue != "Application") {
                // we must process only applications
                // nothing to do in this file
                saveThisApp = false;
                break;
            }
        }

        // We use "startsWith" instead of == because varName may look like "Name[en]"
        else if (varName.startsWith("Name")) {
            changeAccordingToLanguage(&appName, varName, varValue);
        }
        else if (varName.startsWith("GenericName")) {
            changeAccordingToLanguage(&appGenericName, varName, varValue);
        }
        else if (varName.startsWith("Icon")) {
            changeAccordingToLanguage(&appIconName, varName, varValue);
        }
        else if (varName == "Exec") {
            appExec = varValue;
        }
        else if (varName == "Path") {
            appRunFolder = varValue;
        }
        else if (varName == "Keywords") {
            appKeywords = varValue;
        }

        else if (varName == "NoDisplay" || varName == "Hidden") {
            // by specification, we shouldn't display entries that have parameter "NoDisplay" or "Hidden" equaling true
            if (varValue == "true") {
                saveThisApp = false;
                break;
            }
        }

        else if (varName == "OnlyShowIn") {
            QStringList onlyShowIn = varValue.split(';', QString::SkipEmptyParts);

            // if current environment isn't in list of enviroments where we should display this item
            if (!onlyShowIn.contains(currentDesktopEnvironment)) {
                saveThisApp = false;
                break;
            }
        }

        else if (varName == "NotShowIn") {
            QStringList notShowIn = varValue.split(';', QString::SkipEmptyParts);

            // if current environment isn't in list of enviroments where we should display this item
            if (notShowIn.contains(currentDesktopEnvironment)) {
                saveThisApp = false;
                break;
            }
        }

        else if (varName == "TryExec") {
            if (!QFileInfo(varValue).isExecutable()) {
                // we should ignore this item
                saveThisApp = false;
                break;
            }
        }

    }

    AppInfo app;

    if (saveThisApp) {

        /* There's some extra work:
         * We replace parameters like "%s"; see http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s06.html */

        // we're removing them because we don't open any files with this app
        appExec.remove("%f");
        appExec.remove("%F");
        appExec.remove("%u");
        appExec.remove("%U");

        // we're removing them because they're deprecated
        appExec.remove("%d");
        appExec.remove("%D");
        appExec.remove("%n");
        appExec.remove("%N");
        appExec.remove("%v");
        appExec.remove("%m");

        // replacing by specification
        appExec.replace("%i", QString("--icon %1").arg(appIconName));
        appExec.replace("%c", appName);
        appExec.replace("%k", filePath);

        app.setName(appName);
        app.setIcon( QIcon::fromTheme( iconName, QIcon(iconName) ) );
        app.setExec(appExec);
        app.setAppFile(filePath);
        app.setKind(AppInfo::AppKind::Installed);
        app.setRunFolder(appRunFolder);
        app.setGenericName(appGenericName);
        app.setKeywords( appKeywords.split(';') );

        return app;
    }

    return AppInfo();

#elif defined(Q_OS_WIN)

    QFileInfo file(filePath);

    AppInfo app;

    app.setName(file.completeBaseName());
    app.setExec(file.symLinkTarget());
    app.setAppFile(filePath);
    app.setKind(AppInfo::AppKind::Installed);
    app.setIcon( QFileIconProvider().icon(file.symLinkTarget()) );

    return app;

#else
#error OS is not supported
#endif

}

// Here goes the old, ugly code.
#ifdef Q_OS_LINUX
/**
 * @brief Extracts locale information from given #varName and parses it to LocaleInfo object.
 * @return Parsed LocaleInfo object.
 */
AppsInterface::LocaleInfo AppsInterface::getLocaleInfo(QString varName) const
{
    LocaleInfo localeInfo;

    if (varName.contains('[')) {
        // isolating locale
        QString locale = varName;
        locale.remove(QRegExp("*[", Qt::CaseInsensitive, QRegExp::Wildcard));
        locale.remove(']');

        // removing @MODIFIER
        locale.remove(QRegExp("@*", Qt::CaseInsensitive, QRegExp::Wildcard));

        // splitting locale to components
        if (locale.contains('.')) {
            QStringList localeComponents = locale.split('.');
            localeInfo.lang = localeComponents.first();
            localeInfo.encoding = localeComponents.last();
        } else {
            localeInfo.lang = locale;
        }

        localeInfo.containsCountryCode = localeInfo.lang.contains('_'); // '_' is separator between the language code and the country code
    }

    return localeInfo;
}

/**
 * @brief Sets variable value depending on system locale.
 */
void AppsInterface::changeAccordingToLanguage(QString *var, const QString &varName, const QString &varValue) const
{
    LocaleInfo locale = getLocaleInfo(varName);

    // if there is the locale info in this varName
    if (locale.localeInfoExists()) {

        // getting current language name
        // QLocale::name returns smth like "en_US"
        QString systemLang = QLocale().name();

        // if locale.lang == "en_US"
        if (locale.lang == systemLang || locale.lang == systemLang.split('_').first()) {
            *var = varValue;
        }
    } else {
        // if we still didn't set localized version of name
        if (var->isNull())
            *var = varValue;
    }
}
#endif
// End of the old, ugly code.

