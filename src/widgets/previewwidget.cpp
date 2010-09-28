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

#include "previewwidget.h"
#include "figure_iter.h"

#include <QPainter>
#include <QRect>
//#include <QDebug>

#include <math.h>

PreviewWidget::PreviewWidget(QWidget * p) :
    QWidget(p),
    show(false),
    phase(0),
    pixmap()
{
    startTimer(40);
}

void
PreviewWidget::paintEvent(QPaintEvent * /* event */) {
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(QColor(0, 0, 0)));
    if (show) {
        // calc delta
        QRect u(0, 0, 0, 0);
        for(Figure_iter fi(figure); fi(); ++fi) {
            u = u.united(skin.hexogon_rect(*fi));
        }
        QPoint d(rect().center() - u.center());
        // show figure
        for(Figure_iter fi(figure); fi(); ++fi) {
            painter.drawPixmap(
                skin.hexogon_rect(*fi).translated(
                    d + QPoint(
                        skin.width2()*sin(phase*5),
                        skin.height2()*cos(phase*7))),
                pixmap
            );
        }
    }
}

void
PreviewWidget::timerEvent(QTimerEvent * /* event */) {
    phase += .02;
    update();
}

void
PreviewWidget::set_skin(const Skin & s) {
    skin = s;
    setMinimumSize(QSize(
        3 * skin.width_mod() + skin.width_app() + skin.width(),
        5 * skin.height()
    ));
    pixmap = skin.pixmap(figure.color());
    update();
}

void
PreviewWidget::next(const Figure & f) {
    figure = f;
    pixmap = skin.pixmap(figure.color());
    update();
}

void
PreviewWidget::show_next() {
    show = true;
    update();
}

void
PreviewWidget::hide_next() {
    show = false;
    update();
}
