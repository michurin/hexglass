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

#include "glasswidget.h"

#include <QPainter>
#include <QTimerEvent>
#include <QPaintEvent>
//#include <QDebug>

GlassWidget::GlassWidget(QWidget * parent) :
    QWidget(parent),
    glass_width(0),
    glass_height(0),
    glass_body(0),
    cursor_hide_timer(0),
    show_paused_label(false)
{
    setCursor(QCursor(Qt::BlankCursor));
    setMouseTracking(true);
}

GlassWidget::~GlassWidget() {
    delete[] glass_body;
}

void
GlassWidget::paintEvent(QPaintEvent * event) {
//    qDebug() << "paint rect:" << event->rect();
    QPainter painter(this);
//    painter.fillRect(rect(), QBrush(QColor(100, 100, 100)));
    for(int l(0); l<glass_height; ++l) {
        for(int r(0); r<glass_width; ++r) {
            QRect h(skin.hexogon_rect(l, r));
            if (h.intersects(event->rect())) {
                painter.drawPixmap(
                    skin.hexogon_rect(l, r),
                    skin.pixmap(glass_body[l * glass_width + r])
                );
            }
        }
    }
    if (show_paused_label) {
        int w(width());
        int h(height());
        QFont f;
        f.setStyle(QFont::StyleNormal);
        f.setStyleHint(QFont::SansSerif);
        f.setBold(true);
        f.setPixelSize(w/6);
        painter.setFont(f);
        QFontMetrics metrics = painter.fontMetrics();
        QString text(tr("pause"));
        int tw(metrics.width(text));
        int th(metrics.lineSpacing());
        int md(metrics.descent());
        QBrush b(QColor(0, 0, 0, 192));
        painter.setPen(QColor(255, 255, 0));

        painter.fillRect((w - tw) / 2 - 8, (h - md) / 4 + md - th - 2, tw + 16, th + 4, b);
        painter.drawText((w - tw) / 2, (h - md) / 4, text);
    }
}

void
GlassWidget::touch_mouse() {
    setCursor(QCursor(Qt::ArrowCursor));
    if (cursor_hide_timer != 0) {
        killTimer(cursor_hide_timer);
    }
    cursor_hide_timer = startTimer(2000);
}

void
GlassWidget::mouseDoubleClickEvent(QMouseEvent *) {
    touch_mouse();
}

void
GlassWidget::mouseMoveEvent(QMouseEvent *) {
    touch_mouse();
}

void
GlassWidget::mousePressEvent(QMouseEvent *) {
    touch_mouse();
}

void
GlassWidget::mouseReleaseEvent(QMouseEvent *) {
    touch_mouse();
}

void
GlassWidget::timerEvent(QTimerEvent * e) {
    if (e->timerId() == cursor_hide_timer) {
        cursor_hide_timer = 0;
        setCursor(QCursor(Qt::BlankCursor));
    }
}

void
GlassWidget::set_skin(const Skin & s) {
    skin = s;
    regeometry();
}

void
GlassWidget::set_paused_mode(bool m) {
    show_paused_label = m;
    update();
}

void
GlassWidget::regeometry() {
    setFixedSize(skin.glass_size(glass_width, glass_height));
    update();
}

void
GlassWidget::hex_size(int w, int h) {
    delete[] glass_body;
    glass_width = w;
    glass_height = h;
    regeometry();
    glass_body = new int[w * h];
    emit start_game();
}

void
GlassWidget::hex_update(int l, int r, int id) {
    glass_body[l * glass_width + r] = id;
    update(skin.hexogon_rect(l, r));
}
