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

#ifndef SRC_WIDGETS_PREVIEWWIDGET_H
#define SRC_WIDGETS_PREVIEWWIDGET_H

#include "skin.h"
#include "figure.h"

#include <QWidget>
#include <QPixmap>

class QPaintEvent;
class QTimerEvent;
class Configuration;

class PreviewWidget : public QWidget {

Q_OBJECT

private:
    bool show;
    Skin skin;
    Figure figure;
    float phase;
    QPixmap pixmap;

protected:
    void paintEvent(QPaintEvent * event);
    void timerEvent(QTimerEvent * event);

public:
    PreviewWidget(QWidget * parent = 0);

public slots:
    void next(const Figure &);
    void show_next();
    void hide_next();
    void set_skin(const Skin &);
};

#endif // SRC_WIDGETS_PREVIEWWIDGET_H
