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

#ifndef GLOBALS_H
#define GLOBALS_H

namespace Global
{

}

#ifdef WIN_OLD_COMPILER
#define forc11(x,y) foreach (x, y)
#define enumc11 enum
#else
#define forc11(x,y) for (x : y)
#define enumc11 enum class
#endif

#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

#endif // GLOBALS_H
