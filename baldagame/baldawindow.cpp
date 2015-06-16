#include <QtWidgets>

#include "baldaboard.h"
#include "baldawindow.h"


BaldaWindow::BaldaWindow()
{
    alphabet = "А Б В Г Д Е Ё Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я";

    board = new BaldaBoard;


    //Players score
    pl_scoreLcd = new QLCDNumber(5);
    pl_scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    pl_scoreLcd->setMinimumHeight(50);

    //Computer score
    comp_scoreLcd = new QLCDNumber(5);
    comp_scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    comp_scoreLcd->setMinimumHeight(50);

    //Players Words
    pl_words = new QPlainTextEdit;
    pl_words->setReadOnly(true);
    pl_words->setMinimumWidth(150);
    pl_words->setMaximumWidth(150);

    //Computers Words
    comp_words = new QPlainTextEdit;
    comp_words->setReadOnly(true);
    comp_words->setMinimumWidth(150);
    comp_words->setMaximumWidth(150);

    //Timer
    timeLcd = new QLCDNumber(5);

    //Create buttons
    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    applyButton = new QPushButton(tr("&Apply"));
    applyButton->setFocusPolicy(Qt::NoFocus);


    //Add letters
    letters = new QComboBox;
    letters->setStyleSheet("combobox-popup: 0;");
    letters->addItems(alphabet.split(" "));

    connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
    connect(letters,SIGNAL(currentTextChanged(QString)),board,SLOT(curletter(QString)));
    connect(board, SIGNAL(timeChanged(QString)), timeLcd, SLOT(display(QString)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("Player's score")),0,0);
    layout->addWidget(pl_scoreLcd,1,0);

    layout->addWidget(createLabel(tr("Player's words")),2,0);
    layout->addWidget(pl_words,3,0,1,1);

    layout->addWidget(board,0,1,4,5);

    layout->addWidget(createLabel(tr("Computer's score")),0,6);
    layout->addWidget(comp_scoreLcd,1,6);

    layout->addWidget(createLabel(tr("Computer's words")),2,6);
    layout->addWidget(comp_words,3,6);

    layout->addWidget(createLabel(tr("Time")),5,1);
    layout->addWidget(timeLcd,5,2);

    layout->addWidget(createLabel(tr("Letters")),5,3);
    layout->addWidget(letters,5,4);

    layout->addWidget(applyButton,5,5);

    layout->addWidget(startButton,6,0);
    layout->addWidget(pauseButton,6,3);
    layout->addWidget(quitButton, 6,6);
    setLayout(layout);

    setWindowTitle(tr("Balda"));
    resize(800, 600);
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


