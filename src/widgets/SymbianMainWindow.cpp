#include "SymbianMainWindow.h"

#include "hexglass.h"
#include "displaywidget.h"
#include "glasswidget.h"
#include "headwidget.h"
#include "previewwidget.h"
#include "scorewidget.h"
#include "window.h"
#include "controller.h"
#include "freeze_proxy.h"

#include <QPalette>

#include <QHBoxLayout>
#include <QGridLayout>

#include <QAction>

#include <QPushButton>
#include <QFrame>

#include <QApplication>

#include <QDebug>

SymbianMainWindow::SymbianMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    gameIsOver = false ;

    glass = new GlassWidget();

    preview = new PreviewWidget();
    score = new ScoreWidget();
    lines = new ScoreWidget();
    level = new ScoreWidget();

    preview_head = new HeadWidget();
    score_head = new HeadWidget();
    lines_head = new HeadWidget();
    level_head = new HeadWidget();

    preview_box = new DisplayWidget();
    score_box = new DisplayWidget();
    lines_box = new DisplayWidget();
    level_box = new DisplayWidget();

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

    controller = new Controller(glass);
    connect(controller, SIGNAL(hide_next()), this, SLOT(processGameOver())) ;
    connect(controller, SIGNAL(set_paused_mode(bool)), this, SLOT(processPauseToggled(bool)));

    QFrame * central_widget = new QFrame();

    central_widget->setAutoFillBackground(true);
    QPalette pp(central_widget->palette());
    pp.setColor(QPalette::Background, QColor(50, 50, 50));
    central_widget->setPalette(pp);

    QHBoxLayout* bottomLayout = new QHBoxLayout ;
    const QSize buttonSize(80,80) ;
    const QString buttonStyleSheet = "QPushButton "
                                     "{  "
                                     "   border-image: url(%1) ; "
                                     "   background-color: rgba(0, 0, 0, 0%); "
                                     "}";

    QPushButton* lb = new QPushButton ;
    lb->setFixedSize(buttonSize) ;
    lb->setStyleSheet( buttonStyleSheet.arg(":symbian/touch_icons/left.png"));
    bottomLayout->addWidget(lb);
    bottomLayout->addStretch();
    QObject::connect(lb, SIGNAL(clicked()), this, SLOT(processShiftLeftRequest()));

    QPushButton* rotateb = new QPushButton ;
    rotateb->setStyleSheet( buttonStyleSheet.arg(":symbian/touch_icons/rotate.png"));
    rotateb->setFixedSize(buttonSize) ;
    bottomLayout->addWidget(rotateb);
    bottomLayout->addStretch();
    QObject::connect(rotateb, SIGNAL(clicked()), this, SLOT(processRotateRequest()));

    QPushButton* rb = new QPushButton ;
    rb->setStyleSheet( buttonStyleSheet.arg(":symbian/touch_icons/right.png"));
    rb->setFixedSize(buttonSize) ;
    QObject::connect(rb, SIGNAL(clicked()), this, SLOT(processShiftRightRequest()));
    bottomLayout->addWidget(rb);

    QPushButton* closeb = new QPushButton ;
    closeb->setStyleSheet( buttonStyleSheet.arg(":symbian/touch_icons/close.png"));
    connect(closeb, SIGNAL(clicked()), this, SLOT(processCloseRequest()));
    closeb->setFixedSize(buttonSize) ;

    pauseButton = new QPushButton ;
    pauseButton->setStyleSheet( buttonStyleSheet.arg(":symbian/touch_icons/pause.png"));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(processPauseRequest()));
    pauseButton->setFixedSize(buttonSize) ;

    QPushButton* dropb = new QPushButton ;
    dropb->setStyleSheet( buttonStyleSheet.arg(":symbian/touch_icons/drop.png"));
    QObject::connect(dropb, SIGNAL(clicked()), controller, SLOT(force_drop()));
    dropb->setFixedSize(buttonSize) ;

    QGridLayout * layout = new QGridLayout();
//    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setContentsMargins(5, 5, 5, 1);
    layout->setSpacing(4);
    layout->addWidget(glass,       0, 0, 9, 1, Qt::AlignTop);
    layout->addWidget(closeb, 0, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(preview_box, 1, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(score_box,   2, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(lines_box,   3, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(level_box,   4, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(pauseButton,   5, 1, 1, 1, Qt::AlignTop);
    layout->addWidget(dropb,   7, 1, 1, 1, Qt::AlignTop);
    layout->setRowStretch(6, 1);

    layout->addLayout(bottomLayout,9,0,1,2);

    central_widget->setLayout(layout);

    // SETUP

    setCentralWidget(central_widget);

    // MENU

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

//    freeze_a->setChecked(false);//conf.get_autopause_mode());

    glass->set_skin(Skin(":/huge.xpm", 26, 20, 24));//conf.get_skin());
    preview->set_skin(Skin(":/drop_big.xpm", 18, 14, 16));//conf.get_skin());
    controller->setup_game(13, 23);//conf.get_width(), conf.get_height());
//    freeze_proxy->open(false);//conf.get_autopause_mode());



}

SymbianMainWindow::~SymbianMainWindow()
{

    delete controller ;

}

void
SymbianMainWindow::processRotateRequest()
{
    controller->shift(FIGURE_ROTATE_LEFT);
}

void
SymbianMainWindow::processShiftLeftRequest()
{
    controller->shift(FIGURE_MOVER_LEFT);
}

void
SymbianMainWindow::processShiftRightRequest()
{
    controller->shift(FIGURE_MOVER_RIGHT);
}

void
SymbianMainWindow::processDropRequest()
{
    controller->shift(FIGURE_MOVER_DOWN);
}

void
SymbianMainWindow::processCloseRequest()
{
    QApplication::closeAllWindows() ;
}

void
SymbianMainWindow::processPauseRequest()
{
    if (gameIsOver)
    {
        controller->start_game();
        gameIsOver = false ;
    }
    else
    {
        controller->toggle_freeze();
    }
}

void
SymbianMainWindow::processGameOver()
{
    const QString buttonStyleSheet = "QPushButton "
                                     "{  "
                                     "   border-image: url(%1) ; "
                                     "   background-color: rgba(0, 0, 0, 0%); "
                                     "}";

    pauseButton->setStyleSheet( buttonStyleSheet.arg(":touch_icons/play.png"));
    gameIsOver = true ;
}

void
SymbianMainWindow::processPauseToggled( bool on)
{
    qDebug() << "SymbianMainWindow::processPauseToggled() | here" << on ;

    const QString buttonStyleSheet = "QPushButton "
                                     "{  "
                                     "   border-image: url(%1) ; "
                                     "   background-color: rgba(0, 0, 0, 0%); "
                                     "}";

    if(on)
    {
        pauseButton->setStyleSheet( buttonStyleSheet.arg(":touch_icons/play.png"));
    }
    else
    {
        pauseButton->setStyleSheet( buttonStyleSheet.arg(":touch_icons/pause.png"));
    }
}




