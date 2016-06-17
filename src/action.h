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

#ifndef ACTION_H
#define ACTION_H

#include "globals.h"
#include <QString>
#include <QIcon>
#include <QUrl>
#include "appinfo.h"

class Action;
class FileInfo { }; // This class is placed here temporary, until it is written and moved to "fileinfo.h".

typedef Action* ActionPointer;

/**
 * @brief The Action class simulates an action that can be launched (e.g., opening application, file or URL).
 * It is the abstract superclass for actions of different kinds (InternetSearchAction, etc).
 * Currently supported kinds of actions:
 *  - launch an application
 *  - open a file\directory
 *  - open a link (to a website or an email address)
 *  - search something in the Internet
 *  - calculate or define something
 *
 * Normally, actions are provided by ActionsProvider class (see actionsprovider.h). You should not create them by yourself.
 *
 * For public access, an action provides all information necessary for the UI (text, icon and kind), and launch() method.
 * Everything else is done is private area.
 * Note: subclasses have other opened methods, but they are used only to fill actions by ActionsProvider.
 * Normally, you should not "reinterpret_cast" an Action object to subclass object.
 *
 * For simpler use, this header file contains declaration of all Actions subclasses (as well as the Action class),
 * while their definitions is contained in different source files (action_internetsearch.cpp and so on).
 */
class Action
{
public:
    enum Kind {
        Kind_Application,
        Kind_FileSystemEntry,
        Kind_Link,
        Kind_InternetSearch,
        Kind_Tool
    };

    Action();
    virtual ~Action();

    // Id
    int id();
    static ActionPointer byId(int id);

    // Launcher
    /**
     * @brief Launches the action.
     */
    virtual void launch() const = 0;

    // Getters and setters
    /**
     * @brief Returns an icon to display in GlobalLine completer.
     */
    virtual QIcon getIcon() const = 0;

    /**
     * @brief Returns a text to display in GlobalLine completer.
     */
    virtual QString getText() const = 0;

    /**
     * @brief Returns a text to display in GlobalLine completer formatted especially for it.
     */
    virtual QString getFormattedText() const = 0;

    /**
     * @brief Returns the action kind.
     */
    virtual Kind getKind() const = 0;

private:
    int m_id;
};

// Subclasses
/**
 * @brief The ApplicationAction class simulates the "launch application" action.
 * For detailed description for the class and uncommented methods, see the comment before Action class.
 */
class ApplicationAction : public Action
{
public:
    ApplicationAction();

    virtual void launch() const;
    virtual QIcon getIcon() const;
    virtual QString getText() const;
    virtual QString getFormattedText() const;
    virtual Kind getKind() const;

    inline void setInfo(const AppInfo &info)
    {
        m_info = info;
    }

private:
    AppInfo m_info;
};

/**
 * @brief The FileSystemEntryAction class simulates the "open file/directory" action.
 * For detailed description for the class and uncommented methods, see the comment before Action class.
 */
class FileSystemEntryAction : public Action
{
public:
    FileSystemEntryAction();

    virtual void launch() const;
    virtual QIcon getIcon() const;
    virtual QString getText() const;
    virtual QString getFormattedText() const;
    virtual Kind getKind() const;

    inline void setInfo(const FileInfo &info)
    {
        m_info = info;
    }

private:
    FileInfo m_info;
};

/**
 * @brief The LinkAction class simulates the "open a link (to a website or an email address)" action.
 * For detailed description for the class and uncommented methods, see the comment before Action class.
 */
class LinkAction : public Action
{
public:
    LinkAction();

    virtual void launch() const;
    virtual QIcon getIcon() const;
    virtual QString getText() const;
    virtual QString getFormattedText() const;
    virtual Kind getKind() const;

    void setUrl(const QUrl &url, bool removeScheme = true)
    {
        m_url = url;
        m_removeScheme = removeScheme;
    }

private:
    QUrl m_url;
    bool m_removeScheme;
};

/**
 * @brief The InternetSearchAction class simulates the "search something in the Internet" action.
 * For detailed description for the class and uncommented methods, see the comment before Action class.
 */
class InternetSearchAction : public Action
{
public:
    InternetSearchAction();

    virtual void launch() const;
    virtual QIcon getIcon() const;
    virtual QString getText() const;
    virtual QString getFormattedText() const;
    virtual Kind getKind() const;

    void setSearchRequest(const QString &request)
    {
        m_request = request;
    }

private:
    QString m_request;
};

/**
 * @brief The ToolAction class simulates some helpful actions like calculating something and definind something.
 * For detailed description for the class and uncommented methods, see the comment before Action class.
 */
class ToolAction : public Action
{
public:
    enum class ToolKind {
        Calculator,
        Dictionary
    };

    ToolAction();

    virtual void launch() const;
    virtual QIcon getIcon() const;
    virtual QString getText() const;
    virtual QString getFormattedText() const;
    virtual Kind getKind() const;

    void setRequest(const QString &request, const ToolKind &kind)
    {
        m_request = request;
        m_kind = kind;

        calculateAction();
    }

private /*methods*/:
    void calculateAction();

private /*variables*/:
    QString m_request;
    ToolKind m_kind;

    QIcon m_icon;
    QString m_text;
    QString m_formattedText;
};


#endif // ACTION_H
