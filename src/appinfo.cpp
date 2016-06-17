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

#include "appinfo.h"
#include <QBuffer>
#include <QJsonArray>

QString convertKindToString(AppInfo::AppKind kind) {
    switch (kind) {
    case AppInfo::AppKind::NoKind:
        return "nokind";
    case AppInfo::AppKind::Installed:
        return "installed";
    case AppInfo::AppKind::WebApp:
        return "webapp";
    default:
        Q_UNREACHABLE();
        return "";
    }
}

AppInfo::AppKind convertKindFromString(QString kind) {
    if (kind == "installed") {
        return AppInfo::AppKind::Installed;
    } else if (kind == "webapp") {
        return AppInfo::AppKind::WebApp;
    } else {
        Q_UNREACHABLE();
        return AppInfo::AppKind::NoKind;
    }
}

/*QJsonObject AppInfo::toJsonObject() const
{
    QString kindString = convertKindToString( getKind() );

    // Creating JSON object
    QJsonObject json;
    json.insert("name", getName());
    json.insert("icon", getIconName());
    json.insert("exec", getExec());
    json.insert("kind", kindString);

    json.insert("runFolder", getRunFolder());
    json.insert("genericName", getGenericName());
    json.insert("keywords", QJsonArray::fromStringList( getKeywords() ));

    return json;
}

AppInfo AppInfo::fromJsonObject(const QJsonObject &object) const
{
    setName( object.value("name").toString() );
    setIconName( object.value("iconName") );
    setExec( object.value("exec") );
    setKind( convertKindFromString(object.value("kind")) );

    setRunFolder( subObject.value("runFolder").toString() );
    setGenericName( subObject.value("genericName").toString() );
    setKeywords( subObject.value("keywords").toVariant().toStringList() );
}
*/
