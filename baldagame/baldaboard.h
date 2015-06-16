#ifndef BALDABOARD_H
#define BALDABOARD_H

#include <QTimer>
#include <QTime>
#include <QFrame>
#include "baldaword.h"

QT_BEGIN_NAMESPACE
class QGridLayout;
class QButtonGroup;
QT_END_NAMESPACE


class BaldaBoard: public QFrame
{
    Q_OBJECT
public:
    BaldaBoard(QWidget *parent = 0);
    bool IsFree(int);
    bool MakeStep(int, QString);
    int XYtoID(int , int  );
    void LoadDictionary();
    void SetPlayWord();
    void ClearBoard();
public slots:
    void onboard(int);
    void curletter(QString);
    void start();
    void pause();
    void timeOutSlot();
signals:
    void pl_scoreChanged(int score);
    void comp_scoreChanged(int score);
    void timeChanged(QString);
private:
    QVector<QString> play_word;
    QVector<QString> dict;
    int cur_pos;
    QString letter;
    QTimer timer;
    QButtonGroup * board;
    bool isStarted;
    bool isPaused;
    bool isPlayer;
    bool addLetter;
    QTime time;
    int pl_score;
    int comp_score;
    int row_size;
    int col_size;
    bool isChosed;
};
#endif // BALDABOARD_H
