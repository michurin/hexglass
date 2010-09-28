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

#ifndef SRC_CONTROL_SKIN_H
#define SRC_CONTROL_SKIN_H

#include "lplace.h"

#include <QPixmap>
#include <QSize>

class Skin {
private:
    int swidth; // mod+app
    int swidth_mod;
    int swidth_app;
    int sheight;
    int sheight2;
    int swidth2;
    QPixmap pixmaps[11];

public:
    Skin(); // XXX we need it?
    Skin(QString const & path, int w, int wm, int h);

    int width2() const;
    int height2() const;
    int width() const;
    int height() const;
    int width_app() const;
    int width_mod() const;

    QSize glass_size(int w, int h) const;
    QRect hexogon_rect(int l, int r) const;
    QRect hexogon_rect(LPlace const & p) const;
    QPixmap const & pixmap(int i) const;
};

#endif // SRC_CONTROL_SKIN_H
