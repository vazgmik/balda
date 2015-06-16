#include <QtWidgets>
#include <algorithm>
#include "baldaboard.h"


BaldaBoard::BaldaBoard(QWidget *parent)
    :QFrame(parent),cur_pos(-1),prev_pos(-1),row_size(5),col_size(5)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    setEnabled(false);
    QGridLayout *l_board = new QGridLayout(this);
    board = new QButtonGroup;
    letter = "A";
    player_word ="";
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

bool BaldaBoard::MakeStep(int id)
{
    if(player.contains(board->button(id)))
    {
        foreach (QAbstractButton *but, player) {
            but->setChecked(true);
        }
        int size = player.size();
        if(board->button(id) == player[size-1])
        {
            if(size==1)
            {
                board->button(id)->setText("");
                NormalMode();
                addLetter = false;
                isPlayer = false;
            }
            player_word.remove(player_word.size()-1,1);
            board->button(id)->setStyleSheet("QPushButton {font-size: 18pt;font-weight: bold;}");
            player.pop_back();

            cur_pos = prev_pos;
//            QMessageBox msgBox;
//            msgBox.setText(player_word);
//            msgBox.exec();
        }

    }
    else if(cur_pos+1 == id || cur_pos-1 == id || cur_pos+col_size == id ||cur_pos-col_size == id || cur_pos == -1)
    {
        player.push_back(board->button(id));
        prev_pos = cur_pos;
        player_word  += board->button(id)->text();

//        QMessageBox msgBox;
//        msgBox.setText(player_word);
//        msgBox.exec();

        cur_pos = id;
        return true;
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
        if(str.size() == col_size && !play_words.contains(str))
        {
            play_words << str;
            break;
        }
    }

    for(int i=0;i<col_size;++i)
        board->button(XYtoID(row_size/2,i))->setText(QString(play_words[play_words.size()-1][i]));
}

void BaldaBoard::ClearBoard()
{

}

void BaldaBoard::SelectCell(int id)
{
    if(IsFree(id))
    {
        board->button(id)->setText(letter);
        board->button(id)->setChecked(false);
        addLetter = true;
    }
}

void BaldaBoard::EditMode()
{
    foreach(QAbstractButton *but,board->buttons())
    {
        if(but->text()=="")
            but->setEnabled(false);
    }
}

void BaldaBoard::NormalMode()
{
    foreach(QAbstractButton *but,board->buttons())
    {
        but->setEnabled(true);
        but->setChecked(false);
        QString style = "QPushButton {font-size: 18pt;font-weight: bold;} ";
        but->setStyleSheet(style);
    }
}


void BaldaBoard::timeOutSlot()
{
    time.setHMS(0,time.addSecs(-1).minute(),time.addSecs(-1).second()); // decrement counter
    emit timeChanged(time.toString());
    if (time.second() ==0 && time.minute() == 0 ) // countdown has finished
    {
        //gameover
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
            SelectCell(id);
            EditMode();
        }
        else
        {
            //edit mode
            if(MakeStep(id))
            {
                 QString style = "QPushButton {font-size: 18pt;font-weight: bold;color: #ff0000;} ";
                 board->button(id)->setStyleSheet(style);
            }
            else
            {
                board->button(id)->setChecked(false);
            }
        }



    }
    else
    {
        //Computer turn create word
    }

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

void BaldaBoard::apply()
{
    if(dict.contains(player_word))
    {
        NormalMode();
        addLetter = false;
        isPlayer = false;
        emit pl_addWord(player_word);
        emit pl_scoreChanged(player_word.size());
    }
}


