/****
    * HexGlass is a Tetris-like puzzle game.
    *
    * Project homepage: http://hexglass.googlecode.com/
    *
    * Copyright (C) 2010 Alexey Michurin <a.michurin@gmail.com>
    * Copyright (C) 2010 Ramainen Ainu <ainu.sky@gmail.com>
    * Based on code of SDL-joystick-qt by Fred Emmott <mail@fredemmott.co.uk>
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

#ifndef SRC_ADMIXTURE_SDL_JOYSTICK_H
#define SRC_ADMIXTURE_SDL_JOYSTICK_H

#include "figure_trans.h"

#include <QObject>

#include <SDL.h>

class QTimer;
class QTimerEvent;

class Joystick : public QObject
{

    Q_OBJECT;

private:
    QTimer * timer;
    bool joy1pushed;
    bool joy2pushed;
    bool joy3pushed;
    SDL_Joystick * joystick;

public:
    Joystick(QObject * p = 0, int jsNumber = 0);
    ~Joystick();

public slots:
    void poll_joystick();

signals:
    void shift(Figure_trans_mode);
    void drop_down();
    void stop_dropping();
    void toggle_freeze();
    void force_freeze();
};

#endif // SRC_ADMIXTURE_SDL_JOYSTICK_H
