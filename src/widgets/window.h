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

#ifndef SRC_WIDGETS_WINDOW_H
#define SRC_WIDGETS_WINDOW_H

#include "figure_trans.h"

#include <QMainWindow>

class QKeyEvent;
class QFocusEvent;

class Window : public QMainWindow {

    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void focusOutEvent(QFocusEvent * event);

public:
    Window(QWidget * parent = 0);

signals:
    void shift(Figure_trans_mode);
    void drop_down();
    void stop_dropping();
    void toggle_freeze();
    void force_freeze();
};

#endif // SRC_WIDGETS_WINDOW_H
