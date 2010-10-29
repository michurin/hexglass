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

#include "high_score_controller.h"
#include "scorewidget.h"

#include <QDebug>

HighScoreController::HighScoreController(QObject * p) :
    QObject(p),
    upper(2),
    last_v(-1)
{
    // we believe that all objects in heap found thouse parents,
    // and parents take care about distruction
    for(int i(0); i<3; ++i) {
        sc_widgets[i] = new ScoreWidget;
    }
}

// PUBLIC

ScoreWidget *
HighScoreController::operator[](int i) {
    return sc_widgets[i];
}

// SLOTS

void
HighScoreController::setup_scores(int const * a) {
    for (int i(0); i<3; ++i) {
        sc[i] = a[i];
        sc_widgets[i]->set_val(sc[i]); // direct emit DANGEROUS now!!
    }
    last_v = -1;
}

void
HighScoreController::set_val(int v) {
    if (last_v < 0 || v < last_v) { // new game
        upper = 2;
    }
    last_v = v;
    while (upper > -1) {
        if (sc[upper] > v) {
            break;
        }
        if (upper < 2) {
            int p(upper + 1);
            sc[p] = sc[upper];
            sc_widgets[p]->set_val(sc[upper]);
        }
        --upper;
    }
    if (upper < 2) {
        sc[upper+1] = v;
        sc_widgets[upper+1]->set_val(v);
        emit updated(sc);
    }
}
