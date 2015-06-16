#ifndef BALDABOARD_H
#define BALDABOARD_H

#include <QTimer>
#include <QTime>
#include <QFrame>
#include "baldaword.h"

QT_BEGIN_NAMESPACE
class QGridLayout;
class QButtonGroup;
class QAbstractButton;
QT_END_NAMESPACE


class BaldaBoard: public QFrame
{
    Q_OBJECT

public:
    BaldaBoard(QWidget *parent = 0);
    bool IsFree(int);
    bool MakeStep(int);
    int XYtoID(int,int);
    void LoadDictionary();
    void SetPlayWord();
    void ClearBoard();
    void SelectCell(int);
    void EditMode();
    void NormalMode();
public slots:
    void onboard(int);
    void curletter(QString);
    void start();
    void pause();
    void apply();
    void timeOutSlot();

signals:
    void pl_scoreChanged(int score);
    void comp_scoreChanged(int score);
    void timeChanged(QString);
    void pl_addWord(QString);

private:
    QVector<QString> play_words;
    QString player_word;
    QVector<QString> dict;
    QString letter;
    QTimer timer;
    QTime time;
    QButtonGroup * board;
    bool isStarted;
    bool isPaused;
    bool isPlayer;
    bool addLetter;
    int pl_score;
    int comp_score;
    int cur_pos;
    int prev_pos;
    int row_size;
    int col_size;

    QVector <QAbstractButton*> player;

};
#endif // BALDABOARD_H
