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

#include "displaywidget.h"

#include <QGridLayout>
#include <QLabel>

DisplayWidget::DisplayWidget(QWidget * parent) :
    QWidget(parent)
{
    QPalette pp;

    setAutoFillBackground(true);
    pp = palette();
    pp.setColor(QPalette::Background, QColor(80, 80, 80));
    setPalette(pp);

    QGridLayout * layout = new QGridLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setContentsMargins(1, 1, 1, 1);
    layout->setSpacing(1);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);
}
