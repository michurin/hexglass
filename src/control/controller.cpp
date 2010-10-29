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

#include "controller.h"
#include "configuration.h"

#include <QTimer>
//#include <QDebug>

#include <stdlib.h>

Controller::Controller(QObject * o):
    QObject(o),
    hex_width(0),
    hex_height(0),
    hex_data(0),
    timer(new QTimer(this)),
    state(WF_NEW_GAME),
    paused_state(WF_NEW_GAME),
    drop_mode(false),
    cleanup_line(0),
    figure(),
    figures_bank(),
    score_count(0),
    lines_count(0),
    level(1)
{
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(tik()));
}

Controller::~Controller() {
    delete[] hex_data;
}

// PRIVATE

void
Controller::re_schedule() {
    timer->stop();
    switch (state) {
        case WF_NEW_GAME:
        case WF_UNPAUSE:
            return;
        case WF_FALL_STEP:
            if (drop_mode) {
                timer->setInterval(30);
            } else {
                timer->setInterval(2400/(level+2));
            }
            break;
        case WF_VANISH_LINE:
            timer->setInterval(100);
            break;
        case WF_SHIFT:
            timer->setInterval(200);
            break;
    }
    timer->start();
}

void
Controller::unpause() {
    if (state == WF_UNPAUSE) {
        toggle_freeze();
    }
}

void
Controller::start_figure_or_game_over() {
    unpause();
    drop_mode = false;
    ++figures_bank;
    emit next_figure(+figures_bank);
    figure = *figures_bank;
    figure.shift(LPlace(hex_width/2, 0));
    draw_figure();
    if (figure_is_placeable(figure)) {
        state = WF_FALL_STEP;
    } else {
        // stop
        state = WF_NEW_GAME;
        emit hide_next();
    }
}

void
Controller::undraw_figure(int color) {
    for(Figure_iter fi(figure); fi(); ++fi) {
        LPlace q(*fi);
        emit hex_update(q.y, q.x, color);
    }
}

void
Controller::draw_figure() {
    undraw_figure(figure.color());
}

bool
Controller::figure_is_placeable(Figure const & f) const {
    for(Figure_iter fi(f); fi(); ++fi) {
        LPlace q(*fi);
        if (q.x < 0 || q.x >= hex_width || q.y < 0 || q.y >= hex_height) {
            return false;
        }
        if (hex_data[q.y * hex_width + q.x] != 0) {
            return false;
        }
    }
    return true;
}

bool
Controller::check_cleanup() {
    int last(hex_height - 1);
    int s(hex_width * last);
    for (cleanup_line = last; cleanup_line >= 0; --cleanup_line, s -= hex_width) {
        bool f(true);
        for (int r(0); r<hex_width; ++r) {
            if (hex_data[s + r] == 0) {
                f = false;
                break;
            }
        }
        if (f) {
            return true;
        }
    }
    return false;
}

// SLOTS

void
Controller::setup_game(int w, int h) {
//    qDebug() << "Controller::setup_game(int w=" << w << ", int h=" << h << ")";
    delete[] hex_data;
    hex_width = w;
    hex_height = h;
    hex_data = new int[hex_width * hex_height];
    emit hex_size(hex_width, hex_height);
}

void
Controller::start_game() {
    // cleanup field
    timer->stop();
    int *i(hex_data);
    for (int l(0); l<hex_height; ++l) {
        for (int r(0); r<hex_width; ++r) {
            emit hex_update(l, r, *i = 0);
            ++i;
        }
    }
    //
    emit show_next();
    emit set_score(score_count = 0);
    emit set_lines(lines_count = 0);
    emit set_level(level = 1);
    start_figure_or_game_over();
    re_schedule();
}

void
Controller::shift(Figure_trans_mode mode) {
    unpause();
    if (state == WF_FALL_STEP) {
        for(Figure_trans ft(figure, mode); ft(); ++ft) {
            if (figure_is_placeable(*ft)) {
                undraw_figure();
                figure = *ft;
                draw_figure();
                break;
            }
        }
    }
}

void
Controller::force_drop() { // drop or new or unpause
    if (state == WF_UNPAUSE) {
        toggle_freeze();
    } else if (state == WF_FALL_STEP && ! drop_mode) {
        drop_mode = true;
        re_schedule();
    } else if (state == WF_NEW_GAME) {
        start_game();
    }
}

void
Controller::force_undrop() {
    if (state == WF_FALL_STEP && drop_mode) {
        drop_mode = false;
        re_schedule();
    }
}

void
Controller::toggle_freeze() {
    if (state == WF_UNPAUSE) {
        state = paused_state;
    } else if (state != WF_NEW_GAME) {
        paused_state = state;
        state = WF_UNPAUSE;
    }
    emit set_paused_mode(state == WF_UNPAUSE);
    re_schedule();
}

void
Controller::force_freeze() {
    if (state != WF_UNPAUSE && state != WF_NEW_GAME) {
        paused_state = state;
        state = WF_UNPAUSE;
    }
    emit set_paused_mode(state == WF_UNPAUSE);
    re_schedule();
}

void
Controller::tik() {
    if (state == WF_FALL_STEP) {
        Figure n(figure);
        n.shift(LPlace(0, 1));
        if (figure_is_placeable(n)) {
            undraw_figure();
            figure = n;
            draw_figure();
            if (drop_mode) {
                emit set_score(++score_count);
            }
        } else {
            int color = figure.color();
            for(Figure_iter fi(figure); fi(); ++fi) {
                LPlace q(*fi);
                hex_data[q.y * hex_width + q.x] = color;
            }
            if (check_cleanup()) {
                state = WF_VANISH_LINE; // continue in VANISH case
            } else {
                start_figure_or_game_over();
            }
        }
    }
    if (state == WF_VANISH_LINE) {
        // vanish
        int * d(hex_data + cleanup_line * hex_width);
        for (int r(0); r<hex_width; ++r) {
            emit hex_update(cleanup_line, r, *d = 0);
        }
        // plan shift
        state = WF_SHIFT;
    } else if (state == WF_SHIFT) {
        // shift
        emit set_lines(++lines_count);
        emit set_score(score_count += 10 * level);
        if (lines_count % 10 == 0) {
            emit set_level(level = 1 + lines_count/10);
            emit set_score(score_count += 100);
        }

        int * s(hex_data + hex_width * cleanup_line);
        int * t(s + hex_width);

        for (int l(cleanup_line); l > 0; --l) {
            for (int r(hex_width-1); r >= 0; --r) {
                --s;
                --t;
                emit hex_update(l, r, *t = *s);
            }
        }
        for (int r(0); r<hex_width; ++r) {
            emit hex_update(0, r, *t = 0);
            --t;
        }
        // plan next action
        if (check_cleanup()) {
            state = WF_VANISH_LINE;
        } else {
            start_figure_or_game_over();
        }
    }
    re_schedule();
}
