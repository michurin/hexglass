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

#include "freeze_proxy.h"

FreezeProxy::FreezeProxy(QObject * p) :
    QObject(p),
    is_open(false)
{
}

void
FreezeProxy::open(bool o) {
    is_open = o;
}

void
FreezeProxy::freeze() {
    if (is_open) {
        emit force_freeze();
    }
}
