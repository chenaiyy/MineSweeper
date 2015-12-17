#ifndef BLOCKAREA_H
#define BLOCKAREA_H

#include <QWidget>
#include <QGridLayout>


class BlockArea : public QWidget
{
    Q_OBJECT
public:
    explicit BlockArea(int r = 9, int c = 9, int minnum = 10,QWidget *parent = 0);

signals:
    void mineChanged();
    void firstClick();
    void stopTime();

public slots:

private slots:
    void slotSafe();
    void slotExplode();
    void spread();
//    void overSpread();
    void markPlus();
    void markSub();

private:
    int calculateMines(int x, int y) const;

private:
    QGridLayout *mainLayout;
    int row;
    int col;
    int totalBlockNum;
    int totalMineNum;
    int okBlockNum;
    int markNum;

    bool startClick;

public:
    int getRemainMines();
};

#endif // BLOCKAREA_H
