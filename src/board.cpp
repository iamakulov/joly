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

#include <iostream>
#include <string>
#include <QEventLoop>
#include <QtCore>
#include <QQuickView>
#include <QWidget>
#include <QLineEdit>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QApplication>
#include "action.h"
#include "board.h"
#include "globals.h"
#include "actionsprovider.h"
#include "filesystemwatcher.h"
#include "qmlactioniconprovider.h"

using namespace std;

Board::Board(QApplication *a)
{
    m_app = a;
    m_userInterface.addImageProvider("ActionIcons", new QmlActionIconProvider);
    m_userInterface.setActionsProvider(&m_actionsProvider);
}

void Board::start()
{
    m_userInterface.show();
}
