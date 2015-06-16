#include <QtWidgets>
#include <algorithm>
#include "baldaboard.h"


BaldaBoard::BaldaBoard(QWidget *parent)
    :QFrame(parent),cur_pos(0),row_size(5),col_size(5)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    setEnabled(false);
    QGridLayout *l_board = new QGridLayout(this);
    board = new QButtonGroup;
    letter = "A";
    isStarted = false;
    isPaused = false;
    addLetter = false;
    isPlayer = true;
    LoadDictionary();
    //Style for button text
    QString style = "QPushButton {font-size: 18pt;font-weight: bold;} ";

    //Create board and adding to layout
    for(int i=0;i<row_size;++i)
        for(int j=0;j<col_size;++j)
        {
            QPushButton * but = new QPushButton("");
            but->setCheckable(true);
            but->setStyleSheet(style);
            but->setMinimumSize(50,50);
            but->setMaximumSize(150,150);
            but->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
            board->addButton(but,XYtoID(i,j));
            l_board->addWidget(but,i,j);
        }
    //randomizer for generating different words
    qsrand (QDateTime::currentMSecsSinceEpoch());
    connect(board,SIGNAL(buttonClicked(int)),SLOT(onboard(int)));
    connect(&timer,SIGNAL(timeout()),this,SLOT(timeOutSlot()));
}

bool BaldaBoard::IsFree(int id)
{
    if(id>=0 && id<row_size*col_size-1 &&  board->button(id)->text()=="")
        return true;
    return false;
}

bool BaldaBoard::MakeStep(int id, QString ch)
{
    static QString word="";
    if(IsFree(id))
    {
        if( cur_pos+1 == id || cur_pos-1 == id || cur_pos+col_size == id ||cur_pos-col_size == id)
        {
            word += ch;
            cur_pos = id;
            return true;
        }

    }
    return false;
}

int BaldaBoard::XYtoID(int x, int y)
{
    return x*row_size+y;
}

void BaldaBoard::LoadDictionary()
{
    QFile file(":/dict/word_rus.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
           dict << line.toUpper();
           line = in.readLine();
    }
}

void BaldaBoard::SetPlayWord()
{
    int size = dict.size();
    for (int i = 0; i < size; ++i)
        qSwap(dict[i], dict[qrand() % dict.size()]);

    foreach(QString str ,dict)
    {
        if(str.size() == col_size && !play_word.contains(str))
        {
            play_word << str;
            break;
        }
    }

    for(int i=0;i<col_size;++i)
        board->button(XYtoID(row_size/2,i))->setText(QString(play_word[play_word.size()-1][i]));
}

void BaldaBoard::ClearBoard()
{

}


void BaldaBoard::timeOutSlot()
{
    time.setHMS(0,time.addSecs(-1).minute(),time.addSecs(-1).second()); // decrement counter
    emit timeChanged(time.toString());
    if (time.second() ==0 &&time.minute() == 0 ) // countdown has finished
    {
       timer.stop();
    }

}
void BaldaBoard::onboard(int id)
{
    if(board->exclusive())
        return;

    if(isPlayer)
    {
        if(!addLetter)
        {
            if(!cur_pos)
            {
                board->button(id)->setText(letter);
                cur_pos = id;
                addLetter = true;
            }

        }
        else
        {

        }


    }
    else
    {
        //Computer turn create word
    }
//    int cur_row = id/row_size;
//    int cur_col = id%col_size;
//    if(!isChosed){
//        board->button(id)->setText(letter);
//        isChosed = true;
//        prev_pos = QPoint(cur_row,cur_col);
//    }
//    else{
//        cur_pos = QPoint(cur_row,cur_col);
//        if(MakeStep(cur_pos.x(),cur_pos.y(),letter)){
//             board->button(id)->setChecked(true);
//             prev_pos = cur_pos;
//        }
//        else
//        {
//             board->button(id)->setChecked(false);
//        }
//    }

}

void BaldaBoard::curletter(QString l)
{
    letter = l;
}


void BaldaBoard::start()
{
    if (isPaused)
        return;
    setEnabled(true);
    isStarted = true;
    board->setExclusive(false);
    time = QTime(0,2,0);
    emit timeChanged(time.toString());
    pl_score = 0;
    comp_score = 0;
    timer.start(1000);
    ClearBoard();
    SetPlayWord();
}

void BaldaBoard::pause()
{
    if (!isStarted)
        return;

    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    isPaused = !isPaused;
    if (isPaused) {
        this->setEnabled(false);
        board->setExclusive(true);
        button->setText("&Continue");
        timer.stop();
    } else {
        this->setEnabled(true);
        board->setExclusive(false);
        button->setText("&Pause");
        timer.start(1000);
    }

}


