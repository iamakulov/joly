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

#include "filesystemwatcher.h"
#include <QFileInfo>
#include <QDirIterator>
#include <QStringList>
#include <QSet>
#include <QDebug>
#include "globals.h"

/**
 * @brief Returns list of QFileInfo objects for each entry inside the directory #dir.
 */
inline QList<QFileInfo> getInfosList(const QString &dir) {
    return QDir(dir).entryInfoList(QDir::Dirs | QDir::Files | QDir::System | QDir::NoDotAndDotDot);
}

/**
 * @brief Converts #originalPath to canonical form.
 */
inline QString toCanonicalPath(const QString &originalPath) {
    return QFileInfo(originalPath).canonicalFilePath();
}

/**
 * @brief Returns #name + "///" + <string representation of #date>.
 */
inline QString joinStringAndDate(const QString &name, const QDateTime &date) {
    const QString separator = "///";
    return name + separator + date.toString();
}

/**
 * @brief Extracts and returns name part from #string.
 *
 * String must be in format: name + "///" + <string representation of date>.
 */
inline QString getPathFromJoined(const QString &string) {
    const QString separator = "///";
    return string.split(separator).at(0);
}

/********************************************************/

FileSystemWatcher::FileSystemWatcher(QObject *parent) :
    QObject(parent)
{
    connect(&m_timer, SIGNAL(timeout()), SLOT(updateTree()));
    m_timer.start(1000);
}

/**
 * @brief Starts watching directory for changes.
 * @param path Directory to add.
 * @return True, if directory was added successfully, otherwise false.
 *
 * Watching directory for changes means watching all files and directories inside it
 * adding, changing or removing.
 */
bool FileSystemWatcher::addDirectory(const QString &path)
{
    QFileInfo dirInfo(path);
    QString canonicalPath = toCanonicalPath(path);

    // Checking necessary conditions
    if (!dirInfo.exists())
        return false;
    if (!dirInfo.isDir())
        return false;
    if (m_directories.contains(canonicalPath))
        return false;

    // Saving all file entries
    saveDirectoryContent(canonicalPath);

    return true;
}

/**
 * @brief Starts watching all listed directories for changes.
 * @param paths Directories to watch.
 * @return True, if ALL directories were added successfully, otherwise false.
 */
QStringList FileSystemWatcher::addDirectories(const QStringList &paths)
{
    QStringList result;

    for (QString path : paths) {
        if (!addDirectory(path))
            result += path;
    }

    return result;
}

/**
 * @brief Removes directory and all its subfiles and subdirectories from watching for changes.
 * @param path Directory to unwatch.
 * @return True, if watching stopped successfully, otherwise false.
 */
bool FileSystemWatcher::removeDirectory(const QString &path)
{
    QString canonicalPath = toCanonicalPath(path);

    if (!m_directories.contains(canonicalPath))
        return false;

    m_directories.remove(canonicalPath);

    return true;
}

/**
 * @brief Removes all listed directories from watching for changes.
 * @param paths Directories to remove.
 * @return True, if ALL directories were removed successfully, otherwise false.
 */
QStringList FileSystemWatcher::removeDirectories(const QStringList &paths)
{
    QStringList result;

    for (QString path : paths) {
        if (!removeDirectory(path))
            result += path;
    }

    return result;
}

/**
 * @brief Returns all directories being monitored for changes.
 */
QStringList FileSystemWatcher::directories() const
{
    return m_directories.keys();
}

/**
 * @brief Updates content of all directories being watched and emits according signals.
 */
void FileSystemWatcher::updateTree()
{
    QList<QString> directories = m_directories.keys();
    for (auto dir : directories)
        updateDir(dir);
}

/**
 * @brief Updates content of given directory and emits according signals.
 * @param dir Directory to update.
 */
void FileSystemWatcher::updateDir(const QString &dir)
{
    QSet<QString> realPaths, realPathsWithDates, cachedPaths, cachedPathsWithDates;
    getRealLists(dir, &realPaths, &realPathsWithDates);
    getCachedLists(dir, &cachedPaths, &cachedPathsWithDates);

    saveDirectoryContent(dir);

    // Getting and emitting removed entries. Must be before "added" part.
    QSet<QString> removed = cachedPaths - realPaths;
    for (auto path : removed)
        emitRemoved(path);

    // Getting and emitting added entries. Must be before "removed" part.
    QSet<QString> added = realPaths - cachedPaths;
    for (auto path : added)
        emitAdded(path);

    // Getting and emitting changed entries.
    QSet<QString> changedWithDates = realPathsWithDates - cachedPathsWithDates;
    QSet<QString> changed;
    for (auto path : changedWithDates)
        changed.insert(getPathFromJoined(path));

    // We do this to prevent appearing added files in changed list.
    changed -= added;

    for (auto path : changed)
        emitChanged(path);

    // TOFIX: if between two timer ticks, a file was deleted and a directory was created with the same name as file had,
    // changed() signal is emitted (instead of removed() and added()).
}

/**
 * @brief Replaces all cached content of given directory #path with real one.
 */
void FileSystemWatcher::saveDirectoryContent(const QString &path)
{
    m_directories.remove( toCanonicalPath(path) );
    QList<QFileInfo> infosList = getInfosList(path);
    for (const QFileInfo &fileInfo : infosList)
        addEntry(fileInfo);
}

/**
 * @brief Adds information about given entry to cache in appropriate format.
 * @param entry Given entry information.
 */
void FileSystemWatcher::addEntry(const QFileInfo &entry)
{
    m_directories[ entry.canonicalPath() ].insert(entry.canonicalFilePath(), entry.lastModified());

    EntryType entryType = (entry.isFile())? EntryType::File : EntryType::Dir;
    m_types[ entry.canonicalFilePath() ] = entryType;
}

/**
 * @brief Saves information about real (not cached) content of given directory to two lists in appropriate format.
 * @param dir Directory to save information about.
 * @param paths Output parameter; set of full file paths of each file.
 * @param pathsWithDates Output parameter; set of full file paths of each file joined with its last modification date and time.
 */
void FileSystemWatcher::getRealLists(const QString &dir, QSet<QString> *paths, QSet<QString> *pathsWithDates)
{
    Q_ASSERT(paths != NULL);
    Q_ASSERT(pathsWithDates != NULL);

    QList<QFileInfo> realInfos = getInfosList(dir);
    for (const QFileInfo &info : realInfos) {
        paths->insert(info.canonicalFilePath());
        pathsWithDates->insert(joinStringAndDate( info.canonicalFilePath(), info.lastModified() ));
    }
}

/**
 * @brief Saves information about cached content of given directory to two lists in appropriate format.
 * @param dir Directory to save information about.
 * @param paths Output parameter; set of full file paths of each file.
 * @param pathsWithDates Output parameter; set of full file paths of each file joined with its last modification date and time.
 */
void FileSystemWatcher::getCachedLists(const QString &dir, QSet<QString> *paths, QSet<QString> *pathsWithDates)
{
    Q_ASSERT(paths != NULL);
    Q_ASSERT(pathsWithDates != NULL);

    const QHash<QString, QDateTime> &cachedHash = m_directories[dir];
    QList<QString> cachedKeys = cachedHash.keys();
    for (const QString &key : cachedKeys) {
        paths->insert(key);
        pathsWithDates->insert(joinStringAndDate( key, cachedHash.value(key) ));
    }
}

/**
 * @brief Emits fileAdded() or directoryAdded() signal according to #path entry type.
 */
void FileSystemWatcher::emitAdded(const QString &path)
{
    if (m_types[path] == EntryType::File)
        emit fileAdded(path);
    else
        emit directoryAdded(path);
}

/**
 * @brief Emits fileChanged() signal with given #path as a parameter. Provided for convenience.
 */
void FileSystemWatcher::emitChanged(const QString &path)
{
    if (m_types[path] == EntryType::File)
        emit fileChanged(path);
    else
        Q_UNREACHABLE();
}

/**
 * @brief Emits fileRemoved() or directoryRemoved() signal according to #path entry type.
 */
void FileSystemWatcher::emitRemoved(const QString &path)
{
    if (m_types[path] == EntryType::File)
        emit fileRemoved(path);
    else
        emit directoryRemoved(path);
}
