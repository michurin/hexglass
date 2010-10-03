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

#include "configuration.h"
#include "hexglass.h"

#include <QAction>
//#include <QDebug>

Configuration::Configuration(QObject * p) :
    QObject(p),
    settings(),
    skin_index(settings.value(
        STR(HG_SIGNAME) "/skin",
        QVariant(int(4))).toInt()),
    geometry_index(settings.value(
        STR(HG_SIGNAME) "/size",
        QVariant(int(2))).toInt()),
    autopause_mode(settings.value(
        STR(HG_SIGNAME) "/autopause",
        QVariant(false)).toBool())
{
    if (skin_index < 0 || skin_index > 6) {
        skin_index = 0;
    }
    if (geometry_index < 0 || geometry_index > 5) {
        geometry_index = 0;
    }
    skin_bank[0] = Skin(":/tiny.xpm", 8, 6, 8);
    skin_bank[1] = Skin(":/mosaic_small.xpm", 13, 10, 12);
    skin_bank[2] = Skin(":/mosaic_big.xpm", 18, 14, 16);
    skin_bank[3] = Skin(":/drop_small.xpm", 13, 10, 12);
    skin_bank[4] = Skin(":/drop_big.xpm", 18, 14, 16);
    skin_bank[5] = Skin(":/huge.xpm", 26, 20, 24);
}

int
Configuration::get_height() const {
    return geometry_index * 4 + 20;
}

int
Configuration::get_width() const {
    return geometry_index * 2 + 9;
}

Skin const &
Configuration::get_skin() const {
    return skin_bank[skin_index];
}

int
Configuration::get_geometry_as_int() const {
    return geometry_index;
}

int
Configuration::get_skin_as_int() const {
    return skin_index;
}

bool
Configuration::get_autopause_mode() const {
    return autopause_mode;
}

void
Configuration::set_geometry(QAction * a) {
    geometry_index = a->actionGroup()->actions().indexOf(a);
//    qDebug() << "geometry_index =" << geometry_index;
    emit update_geometry(get_width(), get_height());
}

void
Configuration::set_skin(QAction * a) {
    skin_index = a->actionGroup()->actions().indexOf(a);
//    qDebug() << "skin_index =" << skin_index;
    emit update_skin(get_skin());
}

void
Configuration::set_autopause_mode(bool m) {
    autopause_mode = m;
}

void
Configuration::save_configuration() {
    settings.setValue(STR(HG_SIGNAME) "/skin", skin_index);
    settings.setValue(STR(HG_SIGNAME) "/size", geometry_index);
    settings.setValue(STR(HG_SIGNAME) "/autopause", autopause_mode);
}
