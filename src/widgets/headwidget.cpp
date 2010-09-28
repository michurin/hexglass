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

#include "headwidget.h"

HeadWidget::HeadWidget(QWidget * p) :
    QLabel(p)
{
    setAutoFillBackground(true);
    QPalette pp(palette());
    pp.setColor(QPalette::Background, QColor(20, 20, 20));
    pp.setColor(QPalette::Foreground, QColor(255, 255, 255));
    setPalette(pp);

    setAlignment(Qt::AlignCenter);
    QFont f;
    f.setStyle(QFont::StyleNormal);
    f.setStyleHint(QFont::SansSerif);
    f.setPixelSize(10);
    setFont(f);
}
