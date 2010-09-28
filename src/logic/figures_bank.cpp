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

#include "figures_bank.h"

#include <stdlib.h>
#include <time.h>

Figures_bank::Figures_bank() {
    //sranddev(); // mingw do not support it
    srand(time(0));
    randomize();
}

void
Figures_bank::randomize() {
    now = bank + rand() % bank_len;
    next = bank + rand() % bank_len;
}

Figure const &
Figures_bank::operator*() const {
    return *now;
}

Figure const &
Figures_bank::operator+() const {
    return *next;
}

Figures_bank &
Figures_bank::operator++() {
    now = next;
    next = bank + rand() % bank_len;
    return *this;
}

const int Figures_bank::bank_len = 10;

const Figure
Figures_bank::bank[] = {
    Figure(0,0,  0,1,  0,2,  0,3,     0,2,   1), // ----
    Figure(0,0,  0,1,  0,2,  1,2,     0,2,   2), // ___/
    Figure(0,0,  0,1,  0,2, -1,3,     0,2,   3), // ~~~.
    Figure(0,0,  0,1,  0,2,  1,1,     0,1,   4), // __/.
    Figure(0,0,  0,1,  0,2, -1,2,     0,1,   5), // ~~`/
    Figure(0,0,  0,1,  1,0,  1,1,     0,1,   6), // /_/
    Figure(0,0,  1,0,  1,1, -1,1,     0,1,   7), // C
    Figure(0,0,  0,1,  1,1,  1,2,     0,1,   8), // _/~
    Figure(0,0,  0,1, -1,2, -1,3,     0,1,   9), // ~`_
    Figure(0,0,  0,1,  1,1, -1,2,     0,1,  10), // T
};
