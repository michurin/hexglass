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

#ifndef SRC_LOGIC_FIGURE_TRANS_H
#define SRC_LOGIC_FIGURE_TRANS_H

#include "figure.h"

typedef enum {
#ifdef EXTRA_CONTROL
    FIGURE_MOVER_UP,
#endif
    FIGURE_MOVER_DOWN,
    FIGURE_MOVER_RIGHT,
    FIGURE_MOVER_LEFT,
    FIGURE_ROTATE_RIGHT,
    FIGURE_ROTATE_LEFT
} Figure_trans_mode;

class Figure_trans {
private:
    Figure src;
    Figure tgt;
    PPlace shifts[3];
    PPlace *shift;
    PPlace *end;

    void prepare_trans();
    void rotate(int, int, int, int);

public:
    Figure_trans(Figure const & f, Figure_trans_mode);
    const Figure & operator*() const;
    Figure_trans & operator++();
    bool operator()() const;
};

#endif // SRC_LOGIC_FIGURE_TRANS_H
