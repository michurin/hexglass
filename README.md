# HexGlass

The HexGlass is a Tetris-like puzzle game where
10 different types of blocks continuously fall
from above and you must arrange them to make
horizontal rows of hexagonal bricks.
Completing any row causes those hexagonal blocks
to disappear and the rest above move downwards.
The blocks above gradually fall faster and the
game is over when the screen fills up and blocks
can no longer fall from the top.


## Licensing

HexGlass is a Tetris-like puzzle game.

Project homepage: https://github.com/michurin/hexglass

Copyright (C) 2010-2020 Alexey Michurin <a.michurin@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.


## Build

Before building, you will need to have the Qt4 library and developers
tools installed on your system (http://www.trolltech.com/).

Build:

```sh
mkdir -p build
cd build
qmake .. # or qmake-qt4
make     # or gmake or mingw32-make or nmake or other
```

Test it:

```sh
./hexglass # or hexglass.exe ,-)
```

Install:

```sh
sudo make install
```

Uninstall:

```sh
sudo make uninstall
```

You can specify some options in build time.
Setup default size and skin:

```sh
qmake 'DEFINES += DEFAULT_SIZE=0 DEFAULT_SKIN=0'
```

Enjoy!

--
Alexey Michurin
