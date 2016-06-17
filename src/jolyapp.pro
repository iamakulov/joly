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

QT       += core gui widgets qml quick quickwidgets

TEMPLATE = app

#windows {
#    CODECFORTR = UTF-8
#    QMAKE_CXXFLAGS += -U__STRICT_ANSI__
#}

#QMAKE_CXXFLAGS += -std=c++11

CONFIG += c++11


#RESOURCES += \
#    joly.qrc

#OTHER_FILES += \
#    images/window.png \
#    images/watch.png \
#    images/up_arrow.png \
#    images/twitter.png \
#    images/star.png \
#    images/search.png \
#    images/restore_item_transparent.svg \
#    images/restore_item_transparent.png \
#    images/remove_item_transparent.svg \
#    images/remove_item_transparent.png \
#    images/remove_item.png \
#    images/question.svg \
#    images/question.png \
#    images/outline_star.png \
#    images/logo_small.png \
#    images/logo_middle.png \
#    images/logo_light.png \
#    images/logo_dark.png \
#    images/globe.png \
#    images/folder.png \
#    images/file.png \
#    images/equal.png \
#    images/email.png \
#    images/down_arrow.png \
#    images/command.png

HEADERS += \
    action.h \
    actionsmodel.h \
    actionsprovider.h \
    actionsprovider_application.h \
    appinfo.h \
    appscontainer.h \
    board.h \
    fileinfo.h \
    filesystemwatcher.h \
    globals.h \
    qmlactioniconprovider.h \
    qmlbackgroundprovider.h \
    userinterface.h \
    appsinterface.h

SOURCES += \
    action.cpp \
    actionsmodel.cpp \
    actionsprovider.cpp \
    actionsprovider_application.cpp \
    appinfo.cpp \
    appscontainer.cpp \
    board.cpp \
    filesystemwatcher.cpp \
    main.cpp \
    qmlactioniconprovider.cpp \
    qmlbackgroundprovider.cpp \
    userinterface.cpp \
    appsinterface.cpp \
    action_application.cpp

DISTFILES += \
    ui/Completer.qml \
    ui/SearchField.qml \
    ui/Window.qml
