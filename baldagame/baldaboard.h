#ifndef BALDABOARD_H
#define BALDABOARD_H

#include <QBasicTimer>
#include <QFrame>

class BaldaBoard: public QFrame
{
public:
    BaldaBoard(QWidget *parent = 0);
    ~BaldaBoard();

public slots:
    void start();
    void pause();

signals:
    void pl_scoreChanged(int score);
    void comp_scoreChanged(int score);

private:
    QBasicTimer timer;
    int pl_score;
    int comp_score;
    int N;
    int M;
};

#endif // BALDABOARD_H
