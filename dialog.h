#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainarea.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMenuBar;
class QVBoxLayout;
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

signals:

private slots:

    //关于对话框提示
    void aboutAuthor_s();
    void aboutQt_s();

    //新建游戏
    void newGame_s();
    //重置雷区个数
    void num10Mines();
    void num40Mines();
    void num99Mines();

private:
    void createMenu();  //创建菜单

private:

    QVBoxLayout *myLayout;
    MainArea *mainMine;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *aboutMenu;

    QAction *newGame;
    QAction *statInfo;
    QAction *option1;
    QAction *option2;
    QAction *option3;
    QAction *exit;

    QAction *aboutAuthor;
    QAction *aboutQt;

};

#endif // DIALOG_H
