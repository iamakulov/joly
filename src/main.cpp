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

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QFontDatabase>
#include <QSettings>

#include "globals.h"
#include "board.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    app.setOrganizationName("Ivan Akulov");
    app.setApplicationName("Joly");

    Board* board = new Board(&app);
    board->start();

    return app.exec();
}
