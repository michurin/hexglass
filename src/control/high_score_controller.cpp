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
#include "signal_emiter.h"

//#include <QDebug>

HighScoreController::HighScoreController(QObject * p) :
    QObject(p),
    upper(2)
{
    for(int i(0); i<3; ++i) {
        emiters[i] = new SignalEmiter(this);
    }
}

// PUBLIC

SignalEmiter *
HighScoreController::operator[](int i) {
    return emiters[i];
}

// SLOTS

void
HighScoreController::setup_scores(int const * a) {
    for (int i(0); i<3; ++i) {
        sc[i] = a[i];
        (*emiters[i])(sc[i]);
    }
}

void
HighScoreController::set_val(int v) {
    if (v == 0) { // new game
        upper = 2;
    }
    while (upper > -1) {
        if (sc[upper] > v) {
            break;
        }
        if (upper < 2) {
            int p(upper + 1);
            sc[p] = sc[upper];
            (*emiters[p])(sc[upper]);
        }
        --upper;
    }
    if (upper < 2) {
        sc[upper + 1] = v;
        (*emiters[upper + 1])(v);
        emit updated(sc);
    }
}
