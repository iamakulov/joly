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

#ifndef APPINFO_H
#define APPINFO_H

#include <QJsonObject>
#include <QIcon>
#include "globals.h"

class AppInfo {
public:
    enumc11 AppKind { NoKind, Installed, WebApp };

    // Getters & setters
    inline QString getName() const
    {
        return m_name;
    }

    inline void setName(QString newName)
    {
        m_name = newName;
    }

    inline QIcon getIcon() const
    {
        return m_icon;
    }

    inline void setIcon(QIcon newIcon)
    {
        m_icon = newIcon;
    }

    inline QString getExec() const
    {
        return m_exec;
    }

    inline void setExec(const QString &newExec)
    {
        m_exec = newExec;
    }

    inline QString getAppFile() const
    {
        return m_appFile;
    }

    inline void setAppFile(const QString &newAppFile)
    {
        m_appFile = newAppFile;
    }

    inline AppKind getKind() const
    {
        return m_kind;
    }

    inline void setKind(const AppKind &newKind)
    {
        m_kind = newKind;
    }

    inline QString getRunDirectory() const
    {
        return m_runDirectory;
    }

    inline void setRunFolder(const QString &newRunDirectory)
    {
        m_runDirectory = newRunDirectory;
    }

    inline QString getGenericName() const
    {
        return m_genericName;
    }

    inline void setGenericName(const QString &newGenericName)
    {
        m_genericName = newGenericName;
    }

    inline QStringList getKeywords() const
    {
        return m_keywords;
    }

    inline void setKeywords(const QStringList &newKeywords)
    {
        m_keywords = newKeywords;
    }

    inline bool operator<(const AppInfo &other) const {
        return m_name < other.m_name;
    }
    AppInfo &operator =(const AppInfo &) = default;

    inline bool isNull() const {
        return m_kind == AppKind::NoKind;
    }

    /*QJsonObject toJsonObject() const;
    static AppInfo fromJsonObject(const QJsonObject &object) const;*/

private /*methods*/:

private /*variables*/:
    QString m_name;
    QIcon m_icon;
    QString m_exec;
    QString m_appFile;
    AppKind m_kind = AppKind::NoKind;

    QString m_runDirectory;
    QString m_genericName;
    QStringList m_keywords;
};

#endif // APPINFO_H
