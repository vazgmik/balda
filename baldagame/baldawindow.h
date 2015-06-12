#ifndef BALDAWINDOW_H
#define BALDAWINDOW_H

#include <QWidget>

class BaldaWindow : public QWidget
{
    Q_OBJECT

public:
    BaldaWindow(QWidget *parent = 0);
    ~BaldaWindow();
};

#endif // BALDAWINDOW_H
