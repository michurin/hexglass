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

#include "scorewidget.h"

#include <QTimer>

ScoreWidget::ScoreWidget(QWidget * p) :
    QLabel(p),
    color_timer(new QTimer(this)),
    color_val(0)
{
    setAutoFillBackground(true);
    QPalette pp(palette());
    pp.setColor(QPalette::Background, QColor(0, 0, 0));
    pp.setColor(QPalette::Foreground, QColor(255, 255, 0));
    setPalette(pp);

    setAlignment(Qt::AlignCenter);
    QFont f;
    f.setStyle(QFont::StyleNormal);
    f.setStyleHint(QFont::SansSerif);
    f.setBold(true);
    f.setPixelSize(12);
    setFont(f);

    color_timer->setSingleShot(true);
    color_timer->setInterval(20);
    connect(color_timer, SIGNAL(timeout()), this, SLOT(update_color()));

    set_val(0);
}

void
ScoreWidget::update_color() {
    QPalette pp(palette());
    pp.setColor(QPalette::Foreground, QColor(255, 255, color_val * 5));
    pp.setColor(QPalette::Background, QColor(color_val, color_val, color_val));
    setPalette(pp);
    --color_val;
    if (color_val >= 0) {
        color_timer->start();
    }
}

void
ScoreWidget::set_val(int score) {
    setText(QString().setNum(score));
    color_val = 51;
    update_color();
}
