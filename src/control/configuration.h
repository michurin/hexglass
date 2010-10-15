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

#ifndef SRC_CONTROL_CONFIGURATION_H
#define SRC_CONTROL_CONFIGURATION_H

#include "skin.h"

#include <QObject>
#include <QSettings>

class QAction;

class Configuration : public QObject {

    Q_OBJECT

private:
    QSettings settings;
    Skin skin_bank[6];
    int skin_index;
    int geometry_index;
    bool autopause_mode;

public:
    Configuration(QObject * p = 0);

    int get_height() const;
    int get_width() const;
    Skin const & get_skin() const;
    bool get_autopause_mode() const;

    int get_geometry_as_int() const;
    int get_skin_as_int() const;

public slots:
    void set_geometry(QAction *);
    void set_skin(QAction *);
    void set_autopause_mode(bool);

    void save_configuration();

signals:
    void update_geometry(int, int);
    void update_skin(const Skin &);
};

#endif // SRC_CONTROL_CONFIGURATION_H
