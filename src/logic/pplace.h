/****
    * HexGlass is a Tetris-like puzzle game.
    *
    * Copyright (C) 2010 Alexey Michurin
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    * GNU General Public License for more details.
    *
    * You should have received a copy of the GNU General Public License
    * along with this program. If not, see <http://www.gnu.org/licenses/>.
*****/

#ifndef SRC_LOGIC_PPLACE_H
#define SRC_LOGIC_PPLACE_H

#include "abstract_place.h"
#include "lplace.h"

class LPlace;

class PPlace : public AbstractPlace {
public:
    PPlace();
    PPlace(int xx, int yy);
    PPlace(LPlace const & logical_place);
    PPlace(PPlace const & logical_place);
    PPlace const operator+(PPlace const & s) const;
    PPlace const operator+=(PPlace const & s);
    PPlace const operator-(PPlace const & s) const;
    PPlace const operator*(int f) const;
};

#endif // SRC_LOGIC_PPLACE_H
