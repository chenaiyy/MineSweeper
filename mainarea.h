#ifndef MAINAREA_H
#define MAINAREA_H
#include "blockarea.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QGroupBox;
class QLabel;
class QLineEdit;
class QTimer;
QT_END_NAMESPACE


class MainArea : public QWidget
{
    Q_OBJECT
public:
    explicit MainArea(int r = 9, int c = 9, int minnum = 10, QWidget *parent = 0);

signals:

public slots:
    void setTime();
    void setRemainMineNum();
    void startClock();
    void timeStop();

private:
    void createGroup();

private:
    BlockArea *myMine;  //雷区

    QVBoxLayout *mainLayout;
    QGroupBox *groupBox;
    QLabel *timeLabel;
    QLabel *mineNumLabel;
    QLineEdit *timeEdit;
    QLineEdit *mintEdit;

    //计时器
    QTimer *timer;
    int time;
};

#endif // MAINAREA_H
