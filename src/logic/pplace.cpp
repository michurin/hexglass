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

#include "pplace.h"

PPlace::PPlace():
    AbstractPlace()
{
}

PPlace::PPlace(int xx, int yy):
    AbstractPlace(xx, yy)
{
}

PPlace::PPlace(LPlace const & logical_place):
    AbstractPlace(logical_place.x, logical_place.y - (logical_place.x + 1000)/2 + 500)
{
}

PPlace::PPlace(PPlace const & phys_place):
    AbstractPlace(phys_place.x, phys_place.y)
{
}

PPlace const
PPlace::operator+(PPlace const & s) const {
    return PPlace(x + s.x, y + s.y);
}

PPlace const
PPlace::operator+=(PPlace const & s) {
    x += s.x;
    y += s.y;
    return *this;
}

PPlace const
PPlace::operator-(PPlace const & s) const {
    return PPlace(x - s.x, y - s.y);
}

PPlace const
PPlace::operator*(int f) const {
    return PPlace(x * f, y * f);
}
