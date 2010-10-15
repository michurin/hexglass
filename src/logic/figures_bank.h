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

#ifndef SRC_LOGIC_FIGURES_BANK_H
#define SRC_LOGIC_FIGURES_BANK_H

#include "figure.h"

class Figures_bank {
private:
    Figure const * now;
    Figure const * next;
    static const Figure bank[];
    static const int bank_len;
public:
    Figures_bank();
    void randomize();
    Figure const & operator*() const;
    Figure const & operator+() const;
    Figures_bank & operator++();
};

#endif // SRC_LOGIC_FIGURES_BANK_H
