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

#include "hexglass.h"
#include "configuration.h"
#include "displaywidget.h"
#include "glasswidget.h"
#include "headwidget.h"
#include "previewwidget.h"
#include "scorewidget.h"
#include "window.h"
#include "controller.h"
#include "dialogs.h"

#include <QApplication>
#include <QGridLayout>
#include <QFrame>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QList>
#include <QLocale>
#include <QTranslator>
//#include <QDebug>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QTranslator translator;
    //qDebug() << QLocale::system().name();
    if (translator.load(":/" STR(HG_SIGNAME) "_" + QLocale::system().name())) {
        app.installTranslator(&translator);
    }

    app.setApplicationVersion(QObject::tr(STR(HG_VERSION)));
    app.setOrganizationName("michurin");
    app.setOrganizationDomain("michurin.com.ru");
    app.setApplicationName(STR(HG_SIGNAME));
    app.setWindowIcon(QIcon(":/icon.xmp"));

    Configuration conf;

    // CREATE

    Window main_window;
    Dialogs * dialogs(new Dialogs(&main_window));
    GlassWidget * glass(new GlassWidget());

    PreviewWidget * preview(new PreviewWidget());
    ScoreWidget * score(new ScoreWidget());
    ScoreWidget * lines(new ScoreWidget());
    ScoreWidget * level(new ScoreWidget());

    HeadWidget * preview_head(new HeadWidget());
    HeadWidget * score_head(new HeadWidget());
    HeadWidget * lines_head(new HeadWidget());
    HeadWidget * level_head(new HeadWidget());

    DisplayWidget * preview_box(new DisplayWidget());
    DisplayWidget * score_box(new DisplayWidget());
    DisplayWidget * lines_box(new DisplayWidget());
    DisplayWidget * level_box(new DisplayWidget());

    preview_head->setText(QObject::tr("Next"));
    preview_box->layout()->addWidget(preview_head);
    preview_box->layout()->addWidget(preview);

    score_head->setText(QObject::tr("Score"));
    score_box->layout()->addWidget(score_head);
    score_box->layout()->addWidget(score);

    lines_head->setText(QObject::tr("Lines"));
    lines_box->layout()->addWidget(lines_head);
    lines_box->layout()->addWidget(lines);

    level_head->setText(QObject::tr("Level"));
    level_box->layout()->addWidget(level_head);
    level_box->layout()->addWidget(level);

    Controller * controller = new Controller(glass);

    QFrame * central_widget = new QFrame();

    central_widget->setAutoFillBackground(true);
    QPalette pp(central_widget->palette());
    pp.setColor(QPalette::Background, QColor(50, 50, 50));
    central_widget->setPalette(pp);

    QGridLayout * layout = new QGridLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(4);
    layout->addWidget(glass,       0, 0, 4, 1, Qt::AlignTop);
    layout->addWidget(preview_box, 0, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(score_box,   1, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(lines_box,   2, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(level_box,   3, 1, 1, 1, Qt::AlignTop);
    layout->setRowStretch(3, 1);
    central_widget->setLayout(layout);

    // SETUP

    main_window.setCentralWidget(central_widget);

    // MENU

    QAction *a;
    QMenu *m;
    QMenuBar *mbar(main_window.menuBar());
    QActionGroup *ag;

    m = mbar->addMenu(QObject::tr("Game"));

    m->addAction(QObject::tr("New game"),
        controller, SLOT(start_game()), Qt::Key_N);

    m->addSeparator();

    ag = new QActionGroup(&main_window);
    QObject::connect(
        ag, SIGNAL(triggered(QAction *)),
        &conf, SLOT(set_geometry(QAction *))
    );
    QObject::connect(
        &conf, SIGNAL(update_geometry(int, int)),
        controller, SLOT(setup_game(int, int))
    );

    a = m->addAction(QObject::tr("Tiny"));
    a->setShortcut(Qt::Key_1);
    a->setCheckable(true);
    ag->addAction(a);

    a = m->addAction(QObject::tr("Small"));
    a->setShortcut(Qt::Key_2);
    a->setCheckable(true);
    ag->addAction(a);

    a = m->addAction(QObject::tr("Normal"));
    a->setShortcut(Qt::Key_3);
    a->setCheckable(true);
    ag->addAction(a);

    a = m->addAction(QObject::tr("Big"));
    a->setShortcut(Qt::Key_4);
    a->setCheckable(true);
    ag->addAction(a);

    a = m->addAction(QObject::tr("Huge"));
    a->setShortcut(Qt::Key_5);
    a->setCheckable(true);
    ag->addAction(a);

    m->addSeparator();

    ag = new QActionGroup(&main_window);
    QObject::connect(
        ag, SIGNAL(triggered(QAction *)),
        &conf, SLOT(set_skin(QAction *))
    );
    QObject::connect(
        &conf, SIGNAL(update_skin(const Skin &)),
        glass, SLOT(set_skin(const Skin &))
    );
    QObject::connect(
        &conf, SIGNAL(update_skin(const Skin &)),
        preview, SLOT(set_skin(const Skin &))
    );

    a = m->addAction(QObject::tr("Small"));
    a->setShortcut(Qt::Key_A);
    a->setCheckable(true);
    ag->addAction(a);

    a = m->addAction(QObject::tr("Mosaic normal"));
    a->setShortcut(Qt::Key_S);
    a->setCheckable(true);
    ag->addAction(a);

    a = m->addAction(QObject::tr("Mosaic big"));
    a->setShortcut(Qt::Key_D);
    a->setCheckable(true);
    ag->addAction(a);

    a = m->addAction(QObject::tr("Aqua normal"));
    a->setShortcut(Qt::Key_F);
    a->setCheckable(true);
    ag->addAction(a);

    a = m->addAction(QObject::tr("Aqua big"));
    a->setShortcut(Qt::Key_G);
    a->setCheckable(true);
    ag->addAction(a);

    a = m->addAction(QObject::tr("Huge"));
    a->setShortcut(Qt::Key_H);
    a->setCheckable(true);
    ag->addAction(a);

    m->addSeparator();

    m->addAction(QObject::tr("Help"), dialogs, SLOT(help()), Qt::Key_F1);

    m->addSeparator();

    m->addAction(QObject::tr("About"), dialogs, SLOT(about()));
    m->addAction(QObject::tr("About Qt"), &app, SLOT(aboutQt()));

    m->addSeparator();

    m->addAction(QObject::tr("Quit"), &app, SLOT(quit()), Qt::Key_Q);

    // BIND

    QObject::connect(
        &main_window, SIGNAL(shift(Figure_trans_mode)),
        controller, SLOT(shift(Figure_trans_mode))
    );
    QObject::connect(
        &main_window, SIGNAL(drop_down()),
        controller, SLOT(force_drop())
    );
    QObject::connect(
        &main_window, SIGNAL(toggle_freeze()),
        controller, SLOT(toggle_freeze())
    );

    QObject::connect(
        controller, SIGNAL(hex_size(int, int)),
        glass, SLOT(hex_size(int, int))
    );
    QObject::connect(
        glass, SIGNAL(start_game()),
        controller, SLOT(start_game())
    );
    QObject::connect(
        controller, SIGNAL(hex_update(int, int, int)),
        glass, SLOT(hex_update(int, int, int))
    );
    QObject::connect(
        controller, SIGNAL(set_paused_mode(bool)),
        glass, SLOT(set_paused_mode(bool))
    );

    QObject::connect(
        controller, SIGNAL(next_figure(const Figure &)),
        preview, SLOT(next(const Figure &))
    );
    QObject::connect(
        controller, SIGNAL(show_next()),
        preview, SLOT(show_next())
    );
    QObject::connect(
        controller, SIGNAL(hide_next()),
        preview, SLOT(hide_next())
    );

    QObject::connect(
        controller, SIGNAL(set_lines(int)),
        lines, SLOT(set_val(int))
    );
    QObject::connect(
        controller, SIGNAL(set_level(int)),
        level, SLOT(set_val(int))
    );
    QObject::connect(
        controller, SIGNAL(set_score(int)),
        score, SLOT(set_val(int))
    );

    QObject::connect(
        &app, SIGNAL(aboutToQuit()),
        &conf, SLOT(save_configuration())
    );

    // INIT

    mbar->findChildren<QMenu *>()[0]->actions()[2 + conf.get_geometry_as_int()]->setChecked(true);
    mbar->findChildren<QMenu *>()[0]->actions()[8 + conf.get_skin_as_int()]->setChecked(true);

    glass->set_skin(conf.get_skin());
    preview->set_skin(conf.get_skin());
    controller->setup_game(conf.get_width(), conf.get_height());

    // SHOW

    main_window.show();

    // EXEC

    return app.exec();
}
