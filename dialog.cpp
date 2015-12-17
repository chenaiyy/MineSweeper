#include "dialog.h"
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QAction>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    createMenu();
    mainMine = new MainArea;

    myLayout = new QVBoxLayout;

    myLayout->setMenuBar(menuBar);
    myLayout->addWidget(mainMine);

    setLayout(myLayout);
}

Dialog::~Dialog()
{

}

void Dialog::createMenu()
{
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&Game"),this);
    QMenu *optionMenu = new QMenu(tr("&Option"),this);
    aboutMenu = new QMenu(tr("&About"),this);


    newGame = fileMenu->addAction(tr("&New &Game"));
    fileMenu->addSeparator();
    statInfo = fileMenu->addAction(tr("&Info"));
    fileMenu->addMenu(optionMenu);
    option1 = optionMenu->addAction(tr("10 &Mines"));
    option2 = optionMenu->addAction(tr("40 &Mines"));
    option3 = optionMenu->addAction(tr("99 &Mines"));
    fileMenu->addSeparator();
    exit = fileMenu->addAction(tr("&Exit"));
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    aboutAuthor = aboutMenu->addAction(tr("&Author"));
    aboutQt = aboutMenu->addAction(tr("&About &Qt"));

    connect(aboutAuthor,SIGNAL(triggered()),this,SLOT(aboutAuthor_s()));
    connect(aboutQt,SIGNAL(triggered()),this,SLOT(aboutQt_s()));
    connect(newGame,SIGNAL(triggered()),this,SLOT(newGame_s()));

    connect(option1,SIGNAL(triggered()),this,SLOT(num10Mines()));
    connect(option2,SIGNAL(triggered()),this,SLOT(num40Mines()));
    connect(option3,SIGNAL(triggered()),this,SLOT(num99Mines()));

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(aboutMenu);
}



void Dialog::aboutAuthor_s()
{
    QMessageBox::about(this,tr("关于作者"),tr("chenaiyy，Email：chenaiyy@aliyun.com"));
}

void Dialog::aboutQt_s()
{
    QMessageBox::aboutQt(this);
}

void Dialog::newGame_s()
{
    myLayout->removeWidget(mainMine);
    if(mainMine)
        delete mainMine;
    mainMine = new MainArea;

    myLayout->addWidget(mainMine);
    setLayout(myLayout);

}

void Dialog::num10Mines()
{
    myLayout->removeWidget(mainMine);
    if(mainMine)
        delete mainMine;
    mainMine = new MainArea(9,9,10);

    myLayout->addWidget(mainMine);
    setLayout(myLayout);
}

void Dialog::num40Mines()
{
    myLayout->removeWidget(mainMine);
    if(mainMine)
        delete mainMine;
    mainMine = new MainArea(16,16,40);

    myLayout->addWidget(mainMine);
    setLayout(myLayout);
}

void Dialog::num99Mines()
{
    myLayout->removeWidget(mainMine);
    if(mainMine)
        delete mainMine;
    mainMine = new MainArea(16,30,99);

    myLayout->addWidget(mainMine);
    setLayout(myLayout);
}
