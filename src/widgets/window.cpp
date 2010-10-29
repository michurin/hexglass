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

#include "window.h"
#include "hexglass.h"

#include <QKeyEvent>
#include <QFocusEvent>
#include <QLayout>
//#include <QDebug>

Window::Window(QWidget * parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr(STR(HG_NAME)));
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void
Window::keyPressEvent(QKeyEvent * event) {
    switch(event->key()) {

#ifdef EXTRA_CONTROL
        case Qt::Key_Home:
            emit shift(FIGURE_MOVER_UP);
            break;
#endif

        case Qt::Key_Enter:
        case Qt::Key_Return:
            emit shift(FIGURE_MOVER_DOWN);
            break;
        case Qt::Key_Right:
            emit shift(FIGURE_MOVER_RIGHT);
            break;
        case Qt::Key_Left:
            emit shift(FIGURE_MOVER_LEFT);
            break;
        case Qt::Key_Up:
            emit shift(FIGURE_ROTATE_LEFT);
            break;
        case Qt::Key_Down:
            emit shift(FIGURE_ROTATE_RIGHT);
            break;
        case Qt::Key_Space:
            if (! event->isAutoRepeat()) {
                emit drop_down();
            }
            break;
        case Qt::Key_P:
            emit toggle_freeze();
            break;
    }
}

void
Window::keyReleaseEvent(QKeyEvent * event) {
    if (event->key() == Qt::Key_Space && ! event->isAutoRepeat()) {
        emit stop_dropping();
    }
}

void
Window::focusOutEvent(QFocusEvent * /* event */) {
    emit force_freeze();
}
