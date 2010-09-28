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

#include "figure_trans.h"

Figure_trans::Figure_trans(Figure const & f, Figure_trans_mode mode) :
    src(f),
    tgt(),
    shift(shifts),
    end(shift+2)
{
    tgt.figure_color = src.figure_color;
    switch (mode) {

#ifdef EXTRA_CONTROL
        case FIGURE_MOVER_UP:
            shifts[0].x =  0;
            shifts[0].y = -1;
            prepare_trans();
            --end;
            break;
#endif

        case FIGURE_MOVER_DOWN:
            shifts[0].x =  0;
            shifts[0].y =  1;
            prepare_trans();
            --end;
            break;
        case FIGURE_MOVER_RIGHT:
            if (src.figure[4].x & 1) {
                shifts[0].x =  1;
                shifts[0].y = -1;
                shifts[1].x =  1;
                shifts[1].y =  0;
            } else {
                shifts[0].x =  1;
                shifts[0].y =  0;
                shifts[1].x =  1;
                shifts[1].y = -1;
            }
            prepare_trans();
            break;
        case FIGURE_MOVER_LEFT:
            if (src.figure[4].x & 1) {
                shifts[0].x = -1;
                shifts[0].y =  0;
                shifts[1].x = -1;
                shifts[1].y =  1;
            } else {
                shifts[0].x = -1;
                shifts[0].y =  1;
                shifts[1].x = -1;
                shifts[1].y =  0;
            }
            prepare_trans();
            break;
        case FIGURE_ROTATE_RIGHT:
            rotate(0, -1, 1, 1);
            tgt = src;
            shifts[0].x =  1;
            shifts[0].y =  0;
            shifts[1].x = -1;
            shifts[1].y =  1;
            --shift;
            break;
        case FIGURE_ROTATE_LEFT:
            rotate(1, 1, -1, 0);
            tgt = src;
            shifts[0].x = -1;
            shifts[0].y =  1;
            shifts[1].x =  1;
            shifts[1].y =  0;
            --shift;
            break;
    }
}

void
Figure_trans::rotate(int a, int b, int c, int d) {
    PPlace cc(src.figure[4]);
    for(int i(0); i<4; ++i) {
        PPlace r(src.figure[i] - cc);
        src.figure[i] = cc + PPlace(a * r.x + b * r.y, c * r.x + d * r.y);
    }
}

void
Figure_trans::prepare_trans() {
    for (int i(0); i<5; ++i) {
        tgt.figure[i] = src.figure[i] + *shift;
    }
}

const Figure &
Figure_trans::operator*() const {
    return tgt;
}

Figure_trans &
Figure_trans::operator++() {
    ++shift;
    if ((*this)()) {
        prepare_trans();
    }
    return *this;
}

bool
Figure_trans::operator()() const {
    return shift < end;
}
