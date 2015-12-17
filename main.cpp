#include "dialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
//    BlockArea *test = new BlockArea;
//    test->show();
//    MainArea *test = new MainArea;
//    test->show();

    return a.exec();
}
