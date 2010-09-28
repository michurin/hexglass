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

#include "dialogs.h"
#include "hexglass.h"

#include <QMessageBox>
#include <QIcon>

Dialogs::Dialogs(QWidget * p) :
    QWidget(p)
{
    setWindowIcon(QIcon(QPixmap(":/about_icon.xpm")));
}

void
Dialogs::about() {
    QMessageBox::about(
    this,
    tr("About"),
        "<h3>" STR(HG_NAME) " " STR(HG_VERSION) "</h3>" +

    tr( "<p>Copyright (c) 2010 Alexey Michurin</p>"

        "<p>Released under the terms of the"
        " <a href=\"http://www.gnu.org/licenses/\">GNU GPL v3</a></p>"

        "<p>The ") + STR(HG_NAME) +
    tr( " is a Tetris-like puzzle game."
        " 10 different types of blocks continuously fall"
        " from above and you must arrange them to make"
        " horizontal rows of hexagonal bricks."
        " Completing any row causes those hexagonal blocks"
        " to disappear and the rest above move downwards."
        " The blocks above gradually fall faster and the"
        " game is over when the screen fills up and blocks"
        " can no longer fall from the top.</p>"

        "<p>Project home page: "
        "<a href=\"http://hexglass.googlecode.com/\">"
        "http://hexglass.googlecode.com/</a></p>")
    );
}

void
Dialogs::help() {
    QMessageBox::about(
    this,
    tr("Help"),
    tr( "<h3>Hot keys</h3>"
        "<dl>"
        "<dt>Left/Right (arrows)</td>"
        "<dd>Shift block</dd>"
        "</dl>"
        "<dl>"
        "<dt>Up/Down (arrows)</td>"
        "<dd>Rotate block</dd>"
        "</dl>"
        "<dl>"
        "<dt>Space</td>"
        "<dd>Drop block down or start new game</dd>"
        "</dl>"
        "<dl>"
        "<dt>Enter</td>"
        "<dd>Force one step to down</dd>"
        "</dl>"
        "<dl>"
        "<dt>P</td>"
        "<dd>Pause/unpause</dd>"
        "</dl>"
        "<dl>"
        "<dt>N</td>"
        "<dd>New game</dd>"
        "</dl>"
        "<dl>"
        "<dt>1 ... 5</td>"
        "<dd>Change size (and restart game)</dd>"
        "</dl>"
        "<dl>"
        "<dt>A, S, D, F, G, H</td>"
        "<dd>Change skin</dd>"
        "</dl>"
        "<dl>"
        "<dt>Q</td>"
        "<dd>Qute</dd>"
        "</dl>"
        )
    );
}
