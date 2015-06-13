#include <QtWidgets>
#include "baldaboard.h"


BaldaBoard::BaldaBoard(QWidget *parent)
    : QFrame(parent),N(5),M(5)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    QGridLayout *layout = new QGridLayout(this);

    for(int i=0;i<N;++i)
        for(int j=0;j<M;++j)
        {
            QPushButton * but = new QPushButton;
            but->setMinimumSize(50,50);
            but->setMaximumSize(150,150);
            but->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
            layout->addWidget(but,i,j);
        }


}

BaldaBoard::~BaldaBoard()
{

}

