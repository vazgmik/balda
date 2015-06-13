#ifndef BALDAWINDOW_H
#define BALDAWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class BaldaBoard;

class BaldaWindow : public QWidget
{
    Q_OBJECT

public:
    BaldaWindow();
    ~BaldaWindow();
    QLabel *createLabel(const QString &text);

private:
    BaldaBoard *board;
    QLCDNumber *pl_scoreLcd;
    QLCDNumber *comp_scoreLcd;
    QLCDNumber *timeLcd;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
};

#endif // BALDAWINDOW_H
