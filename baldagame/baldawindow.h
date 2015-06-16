#ifndef BALDAWINDOW_H
#define BALDAWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
class QComboBox;
class QPlainTextEdit;
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
    QString alphabet;
    BaldaBoard *board;
    QLCDNumber *pl_scoreLcd;
    QLCDNumber *comp_scoreLcd;
    QLCDNumber *timeLcd;
    QPushButton *startButton;
    QPushButton *applyButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
    QComboBox * letters;
    QPlainTextEdit * pl_words;
    QPlainTextEdit * comp_words;
};

#endif // BALDAWINDOW_H
