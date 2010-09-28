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

#ifndef SRC_WIDGETS_SCOREWIDGET_H
#define SRC_WIDGETS_SCOREWIDGET_H

#include <QLabel>

class QTimer;

class ScoreWidget : public QLabel {

    Q_OBJECT

private:
    QTimer * color_timer;
    int color_val;

public:
    ScoreWidget(QWidget * p = 0);

public slots:
    void update_color();
    void set_val(int);
};

#endif // SRC_WIDGETS_SCOREWIDGET_H
