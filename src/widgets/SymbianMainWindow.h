#ifndef SYMBIANMAINWINDOW_H
#define SYMBIANMAINWINDOW_H

#include <QMainWindow>

class GlassWidget;
class PreviewWidget ;
class ScoreWidget ;
class HeadWidget ;
class DisplayWidget ;
class Controller ;
class FreezeProxy ;

class QPushButton ;
class QFrame ;
class QLabel ;
class QStackedLayout ;

class SymbianMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SymbianMainWindow(QWidget *parent = 0);
    ~SymbianMainWindow() ;

signals:

public slots:
    void processRotateRequest() ;
    void processShiftLeftRequest() ;
    void processShiftRightRequest() ;
    void processDropRequest() ;
    void processPauseRequest() ;
    void processCloseRequest() ;
    void processShowHelp() ;
    void processCloseHelp() ;

    void processGameOver() ;
    void processPauseToggled( bool) ;

protected:
//    void resizeEvent ( QResizeEvent * event ) ;

    GlassWidget * glass;

    PreviewWidget * preview;
    ScoreWidget * score;
    ScoreWidget * lines;
    ScoreWidget * level;

    HeadWidget * preview_head;
    HeadWidget * score_head;
    HeadWidget * lines_head;
    HeadWidget * level_head;

    DisplayWidget * preview_box;
    DisplayWidget * score_box;
    DisplayWidget * lines_box;
    DisplayWidget * level_box;

    Controller* controller ;
    FreezeProxy * freeze_proxy ;

    QPushButton* pauseButton;
    QPushButton* helpButton ;

    bool gameIsOver ;

    QFrame* makeCentralWidget() ;
    QFrame* makeHelpWidget() ;
    QStackedLayout* widgetsStack ;

    QSize buttonSize ;
    QString buttonStyleSheet ;


};

#endif // SYMBIANMAINWINDOW_H
