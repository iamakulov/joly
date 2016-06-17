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

#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QObject>
#include <QStringList>
#include <QHash>
#include <QTimer>
#include <QDateTime>
#include <QSet>
#include <QFileInfo>

/**
 * @brief The FileSystemWatcher class provides file system watcher imlementation which is more suitable for Joly.
 *
 * The QFileSystemWatcher class doesn't meet project requirements because is doesn't emit precise signals
 * (e.g. separated file change, file adding and file removing).
 *
 * At the moment, watching file system for changes is made by using timer.
 * This realisation is much easier, and it seems to be less resource-intensive,
 * because watching every file in a directory for a change could be quite consuming.
 */
class FileSystemWatcher : public QObject
{
    Q_OBJECT

    enum class EntryType { File, Dir };
public:
    explicit FileSystemWatcher(QObject *parent = 0);

    bool addDirectory(const QString &path);
    QStringList addDirectories(const QStringList &paths);
    bool removeDirectory(const QString &path);
    QStringList removeDirectories(const QStringList &paths);

    QStringList directories() const;

signals:
    void fileAdded(const QString &fileName);
    void fileChanged(const QString &fileName);
    void fileRemoved(const QString &fileName);

    void directoryAdded(const QString &fileName);
    void directoryRemoved(const QString &fileName);

public slots:

private slots:
    void updateTree();
    void updateDir(const QString &dir);

private /*methods*/:
    void saveDirectoryContent(const QString &path);
    void addEntry(const QFileInfo &entry);

    void getRealLists(const QString &dir, QSet<QString> *paths, QSet<QString> *pathsWithDates);
    void getCachedLists(const QString &dir, QSet<QString> *paths, QSet<QString> *pathsWithDates);

    void emitAdded(const QString &path);
    void emitChanged(const QString &path);
    void emitRemoved(const QString &path);

private /*variables*/:
    QHash<QString, QHash<QString, QDateTime>> m_directories; // { DirectoryPath: { EntryInDirectoryPath: Modified } }
    QHash<QString, EntryType> m_types;  // { EntryPath: EntryType }
    // m_types is necessary when emitting fileRemoved() or directoryRemoved() event, because when the entry is deleted, we can't get its type.
    QTimer m_timer;
};

#endif // FILESYSTEMWATCHER_H
