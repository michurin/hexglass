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

#ifndef SRC_CONTROL_CONTROLLER_H
#define SRC_CONTROL_CONTROLLER_H

#include "figures_bank.h"
#include "figure_iter.h"
#include "figure_trans.h"

#include <QObject>

class QTimer;
class Configuration;

class Controller : public QObject {

    Q_OBJECT

private:
    typedef enum { // FW -- waiting for
        WF_NEW_GAME,
        WF_FALL_STEP,
        WF_VANISH_LINE,
        WF_SHIFT,
        WF_UNPAUSE
    } state_t;
    int hex_width;
    int hex_height;
    int * hex_data;
    QTimer * timer;

    state_t state;
    state_t paused_state;
    bool drop_mode;

    int cleanup_line;
    Figure figure;
    Figures_bank figures_bank;

    int score_count;
    int lines_count;
    int level;

private:
    void re_schedule();
    void unpause();
    void start_figure_or_game_over();
    void undraw_figure(int color = 0);
    void draw_figure();
    bool figure_is_placeable(Figure const & f) const;
    bool check_cleanup();

public:
    Controller(QObject * o = 0);
    ~Controller();

public slots:
    void setup_game(int, int);
    void start_game();

    void shift(Figure_trans_mode);
    void force_drop();
    void force_undrop();
    void toggle_freeze();
    void force_freeze();

    void tik();

signals:
    void hex_size(int, int);
    void hex_update(int, int, int);
    void next_figure(const Figure &);
    void hide_next();
    void show_next();
    void set_lines(int);
    void set_score(int);
    void set_level(int);
    void set_paused_mode(bool); // XXX two signals?
};

#endif // SRC_CONTROL_CONTROLLER_H
