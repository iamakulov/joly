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

#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPointer>
#include <QCoreApplication>
#include <QQmlApplicationEngine>

#include "action.h"
#include "actionsprovider.h"
#include "userinterface.h"

class QApplication;

class Board : public QObject
{
    Q_OBJECT

public:
    Board(QApplication *a);

public slots:
    void start();

private /*variables*/:
    QApplication *m_app = nullptr;
    ActionsProvider m_actionsProvider;
    UserInterface m_userInterface;
};

#endif // BOARD_H
