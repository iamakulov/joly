##################################################
# Joly. Connect your web and your computer in the one place.
# Copyright (C) 2012-2013 Ivan Akulov <gxoptg@gmail.com>
#
# This file is the part of Joly.
# 
# Joly is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Joly is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Joly. If not, see <http://www.gnu.org/licenses/>.
##################################################

QT       += core gui qml quick quickwidgets script network

TEMPLATE = app

CONFIG += c++14

HEADERS += \
    actions/action.h \
    actionsmodel.h \
    actionsproviders/actionsprovider.h \
    appinfo.h \
    appscontainer.h \
    board.h \
    filesystemwatcher.h \
    globals.h \
    qmlactioniconprovider.h \
    userinterface.h \
    appsinterface.h \
    actions/applicationaction.h \
    actionsproviders/applicationactionsprovider.h \
    actions/calculationaction.h \
    actionsproviders/calculationactionsprovider.h \
    calculator.h \
    actions/websiteaction.h \
    actionsproviders/websiteactionsprovider.h \
    tldretriever.h

SOURCES += \
    actions/action.cpp \
    actionsmodel.cpp \
    actionsproviders/actionsprovider.cpp \
    appinfo.cpp \
    appscontainer.cpp \
    board.cpp \
    filesystemwatcher.cpp \
    main.cpp \
    qmlactioniconprovider.cpp \
    userinterface.cpp \
    appsinterface.cpp \
    actions/applicationaction.cpp \
    actionsproviders/applicationactionsprovider.cpp \
    actions/calculationaction.cpp \
    actionsproviders/calculationactionsprovider.cpp \
    calculator.cpp \
    actions/websiteaction.cpp \
    actionsproviders/websiteactionsprovider.cpp \
    tldretriever.cpp

DISTFILES += \
    ui/Completer.qml \
    ui/SearchField.qml \
    ui/Root.qml \
    ui/ShadowContainer.qml

RESOURCES += \
    resources.qrc
