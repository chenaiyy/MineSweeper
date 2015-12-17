#include "mainarea.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>

MainArea::MainArea(int r, int c, int minnum,QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    myMine = new BlockArea(r,c,minnum);

    mainLayout->addWidget(myMine);
    createGroup();
    mainLayout->addWidget(groupBox);

    timer = new QTimer(this);
    time = 1;

    setLayout(mainLayout);

    connect(timer,SIGNAL(timeout()),this,SLOT(setTime()));
    connect(myMine,SIGNAL(mineChanged()),this,SLOT(setRemainMineNum()));
    connect(myMine,SIGNAL(firstClick()),this,SLOT(startClock()));
    connect(myMine,SIGNAL(stopTime()),this,SLOT(timeStop()));

}

void MainArea::createGroup()
{
    groupBox = new QGroupBox;
    QHBoxLayout *layout = new QHBoxLayout;

    timeLabel = new QLabel;
    mineNumLabel = new QLabel;
    mintEdit = new QLineEdit;
    //    mintEdit->resize(48,48);
    mintEdit->setFixedWidth(48);
    mintEdit->setFixedHeight(42);
    mintEdit->setReadOnly(true);
    mintEdit->setText(QString::number(myMine->getRemainMines()));
    timeEdit = new QLineEdit;
    //    timeEdit->resize(48,48);
    timeEdit->setFixedWidth(48);
    timeEdit->setFixedHeight(42);
    timeEdit->setReadOnly(true);
    timeEdit->setText(QString::number(0));

    timeLabel->setPixmap(QPixmap(":/imgFile/img/clock.jpg"));
    mineNumLabel->setPixmap(QPixmap(":/imgFile/img/mine2.jpg"));

    layout->addWidget(timeLabel);
    layout->addWidget(timeEdit);
    layout->addWidget(mintEdit);
    layout->addWidget(mineNumLabel);

    groupBox->setLayout(layout);
    groupBox->setFixedSize(200,50);
}

void MainArea::setTime()
{
    timeEdit->setText(QString::number(time++));
}

void MainArea::setRemainMineNum()
{
    mintEdit->setText(QString::number(myMine->getRemainMines()));
}

void MainArea::startClock()
{
    timer->start(1000);
}

void MainArea::timeStop()
{
    timer->stop();
}
