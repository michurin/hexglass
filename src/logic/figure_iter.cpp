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

#include "figure_iter.h"

Figure_iter::Figure_iter(Figure const & figure) :
    ptr(logical_figure),
    end(ptr + 4)
{
    PPlace const * s(figure.figure);
    for(LPlace * t(ptr); t < end; ++t, ++s) {
        *t = *s;
#ifdef SELF_TEST
        std::cout << "copy: " << (*t).x << " " << (*t).y << " (logical)" << std::endl;
#endif
    }
}

const LPlace &
Figure_iter::operator*() const {
    return *ptr;
}

Figure_iter &
Figure_iter::operator++() {
    ++ptr;
    return *this;
}

bool
Figure_iter::operator()() const {
    return (ptr < end);
}
