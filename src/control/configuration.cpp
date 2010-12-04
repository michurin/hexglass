/****
    * HexGlass is a Tetris-like puzzle game.
    *
    * Project homepage: http://hexglass.googlecode.com/
    *
    * Copyright (C) 2010 Alexey Michurin <a.michurin@gmail.com>
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

char
Configuration::high_scores_label[] = STR(HG_SIGNAME) "/high_score_label_XX";

Configuration::Configuration(QObject * p) :
    QObject(p),
    settings(),
    skin_index(settings.value(
        STR(HG_SIGNAME) "/skin",
        QVariant(int(DEFAULT_SKIN))).toInt()),
    geometry_index(settings.value(
        STR(HG_SIGNAME) "/size",
        QVariant(int(DEFAULT_SIZE))).toInt()),
    autopause_mode(settings.value(
        STR(HG_SIGNAME) "/autopause",
        QVariant(false)).toBool()),
    careful_dropping_mode(settings.value(
        STR(HG_SIGNAME) "/careful_dropping",
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
    char * e(high_scores_label);
    for (; *e; ++e);
    --e;
    char * ee(e - 1);
    for (int g(0); g<5; ++g) {
        *ee = 'a' + g;
        for (int p(0); p<3; ++p) {
            *e = '1' + p;
            high_scores[g][p] = settings.value(
                high_scores_label,
                QVariant(int(0))).toInt();
        }
    }
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

bool
Configuration::get_careful_dropping_mode() const {
    return careful_dropping_mode;
}

int const *
Configuration::get_high_score() const {
    return &high_scores[geometry_index][0];
}

void
Configuration::set_geometry(QAction * a) {
    geometry_index = a->actionGroup()->actions().indexOf(a);
    // order is significant, cose update_geometry restarted game
    emit update_high_scores(get_high_score());
    emit update_geometry(get_width(), get_height());
}

void
Configuration::set_skin(QAction * a) {
    skin_index = a->actionGroup()->actions().indexOf(a);
    emit update_skin(get_skin());
}

void
Configuration::set_autopause_mode(bool m) {
    autopause_mode = m;
}

void
Configuration::set_careful_dropping_mode(bool m) {
    careful_dropping_mode = m;
}

void
Configuration::set_high_scores(const int * a) {
    for (int i(0); i<3; ++i) {
        high_scores[geometry_index][i] = a[i];
    }
}

void
Configuration::save_configuration() {
    settings.setValue(STR(HG_SIGNAME) "/skin", skin_index);
    settings.setValue(STR(HG_SIGNAME) "/size", geometry_index);
    settings.setValue(STR(HG_SIGNAME) "/autopause", autopause_mode);
    settings.setValue(STR(HG_SIGNAME) "/careful_dropping", careful_dropping_mode);
    char * e(high_scores_label);
    for (; *e; ++e);
    --e;
    char * ee(e - 1);
    for (int g(0); g<5; ++g) {
        *ee = 'a' + g;
        for (int p(0); p<3; ++p) {
            *e = '1' + p;
            settings.setValue(high_scores_label, high_scores[g][p]);
        }
    }
}
