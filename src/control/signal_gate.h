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

#ifndef SRC_CONTROL_SIGNAL_GATE_H
#define SRC_CONTROL_SIGNAL_GATE_H

#include <QObject>

class SignalGate : public QObject {

    Q_OBJECT

private:
    bool is_open;

public:
    SignalGate(QObject * p = 0);

public slots:
    void open(bool);
    void in();

signals:
    void out();
};

#endif // SRC_CONTROL_SIGNAL_GATE_H
