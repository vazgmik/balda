#include <QtWidgets>

#include "baldaboard.h"
#include "baldawindow.h"


BaldaWindow::BaldaWindow()
{

    board = new BaldaBoard;
    //Players score
    pl_scoreLcd = new QLCDNumber(5);
    pl_scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    //Computer score
    comp_scoreLcd = new QLCDNumber(5);
    comp_scoreLcd->setSegmentStyle(QLCDNumber::Filled);


    //Create buttons
    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    //connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
    //connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("Player's Score")), 0, 0);
    layout->addWidget(pl_scoreLcd, 1, 0);
    layout->addWidget(board, 0, 1, 4, 5);
    layout->addWidget(createLabel(tr("Comput's Score")), 0, 6);
    layout->addWidget(comp_scoreLcd,1,6);
    layout->addWidget(startButton, 5, 0);
    layout->addWidget(pauseButton, 5,3);
    layout->addWidget(quitButton, 5, 6);
    setLayout(layout);

    setWindowTitle(tr("Balda"));
    resize(550, 370);
}

BaldaWindow::~BaldaWindow()
{

}

QLabel *BaldaWindow::createLabel(const QString &text)
{
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return lbl;
}
