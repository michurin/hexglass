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

#include "skin.h"

Skin::Skin() :
    swidth(0),
    swidth_mod(0),
    swidth_app(0),
    sheight(0),
    sheight2(0),
    swidth2(0)
{
}

Skin::Skin(QString const & path, int w, int wm, int h) :
    swidth(w),
    swidth_mod(wm),
    swidth_app(w - wm),
    sheight(h),
    sheight2(h/2),
    swidth2(w/2)
{
    QPixmap hexagons(path);
    for (int i(0); i<11; ++i) {
        pixmaps[i] = hexagons.copy(0, sheight * i, swidth, sheight);
    }
}

int
Skin::width2() const {
    return swidth2;
}

int
Skin::height2() const {
    return sheight2;
}

int
Skin::width() const {
    return swidth;
}

int
Skin::height() const {
    return sheight;
}

int
Skin::width_app() const {
    return swidth_app;
}

int
Skin::width_mod() const {
    return swidth_mod;
}

QSize
Skin::glass_size(int w, int h) const {
    return QSize(
        w * swidth_mod + swidth_app,
        h * sheight + sheight2);
}

QRect
Skin::hexogon_rect(int l, int r) const {
    return QRect(
        r * swidth_mod,
        l * sheight + ((r+1000)%2)*sheight2,
        swidth,
        sheight);
}

QRect
Skin::hexogon_rect(LPlace const & p) const {
    return hexogon_rect(p.y, p.x);
}

QPixmap const &
Skin::pixmap(int i) const {
    return pixmaps[i];
}
