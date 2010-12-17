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

#include "sdl_joystick.h"

#include <QTimer>
//#include <QDebug>

#define POLL_INTERVAL 20

Joystick::Joystick(QObject * p, int js) :
    QObject(p),
    timer(new QTimer(this)),
    joy1pushed(FALSE),
    joy2pushed(FALSE),
    joy3pushed(FALSE),
    joystick(0)
{
    // Sure, we're only using the Joystick, but
    // SDL doesn't work if video isn't initialised
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

    Q_ASSERT(js < attachedJoysticks());
    Q_ASSERT(js >= 0);

    joystick = SDL_JoystickOpen(js);

    timer->setSingleShot(true);
    timer->setInterval(POLL_INTERVAL);
    connect(timer, SIGNAL(timeout()), this, SLOT(poll_joystick()));
    timer->start();

    connect(
        this, SIGNAL(shift(Figure_trans_mode)),
        parent(), SIGNAL(shift(Figure_trans_mode))
    );
    connect(this, SIGNAL(drop_down()), parent(), SIGNAL(drop_down()));
    connect(this, SIGNAL(stop_dropping()), parent(), SIGNAL(stop_dropping()));
    connect(this, SIGNAL(toggle_freeze()), parent(), SIGNAL(toggle_freeze()));
    connect(this, SIGNAL(force_freeze()), parent(), SIGNAL(force_freeze()));
}

Joystick::~Joystick() {
    SDL_JoystickClose(joystick);
    SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
}

void Joystick::poll_joystick() {
    SDL_Event event;
//    qDebug() << "poll";
    while (SDL_PollEvent(&event)) {
//        qDebug() << "poll enter loop";
        switch(event.type) {
            case SDL_JOYAXISMOTION:
                if (event.jaxis.axis == 0) {
                    if (event.jaxis.value < -5200) { // THIS IS FALLING DOWN
                        if(!joy1pushed) {
                            joy1pushed = TRUE;
                            emit drop_down();
                        }
                    }
                    if (event.jaxis.value > -3200) {
                        if(joy1pushed) {
                            joy1pushed = FALSE;
                            emit stop_dropping();
                        }
                    }
                }
                if (event.jaxis.axis == 1) {
                    if(event.jaxis.value<1) {
                        if (event.jaxis.value < -5200) { // THIS IS MOVE LEFT
                            if(!joy2pushed) {
                                joy2pushed = TRUE;
                                emit shift(FIGURE_MOVER_LEFT);
                            }
                        }
                        if (event.jaxis.value > -3200 ) {
                            if(joy2pushed) {
                                joy2pushed = FALSE;
                            }
                        }
                    }
                    if (event.jaxis.value > -1) {
                        if (event.jaxis.value > 5200) { // THIS IS MOVE RIGHT
                            if(!joy3pushed) {
                                joy3pushed = TRUE;
                                emit shift(FIGURE_MOVER_RIGHT);
                            }
                        }
                        if (event.jaxis.value < 3200) {
                            if(joy3pushed) {
                                joy3pushed = FALSE;
                            }
                        }
                    }
                }
                break;
            case SDL_JOYBUTTONDOWN:
                if(event.jbutton.button==8) {
                    emit shift(FIGURE_ROTATE_LEFT);
                }
                if(event.jbutton.button==9) {
                    emit shift(FIGURE_ROTATE_RIGHT);
                }
                break;
            case SDL_JOYBUTTONUP:
                break;
        }
    }
    timer->start();
}
