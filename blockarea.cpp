#include "blockarea.h"
#include "block.h"
//#include <QPushButton>
#include <QMessageBox>
#include <QList>
//#include <windows.h>

//随机函数
#include <stdlib.h>
#include <time.h>
//产生num个随机数，这些随机数范围为：min~max-1
void myrand(int *arr, int num, int min, int max)
{
    int r;
    int cnt = 0;
    int i;

    srand((unsigned)time(NULL));
    r = rand()%(max-min);
    while(cnt < num)
    {
        for(i = 0; i < cnt; ++i)
        {
            if(r == arr[i])
                break;
        }
        if(i == cnt)
        {
            arr[i] = r;
            ++cnt;
        }
        r = rand()%(max-min);
    }

}

BlockArea::BlockArea(int r, int c, int minnum, QWidget *parent) : QWidget(parent)
{
//基本参数设置，需要修改构造函数参数来设定扫雷区域的大小和雷数目
    row = r;
    col = c;
    totalBlockNum = row * col;
    totalMineNum = minnum;
    okBlockNum = 0;
    markNum = 0;
    startClick = false;

//设置雷，并随机雷的分布！   此随机函数为伪随机
    bool mine_flag[totalBlockNum];
//    for(int i = 0; i < totalMineNum; ++i)
//        mine_flag[i]=true;
//    for(int i = totalMineNum; i < totalBlockNum; ++i)
//        mine_flag[i]=false;
//    std::random_shuffle(mine_flag,mine_flag+totalBlockNum);
    int minetmp[totalMineNum] = {0};
    myrand(minetmp,totalMineNum,0,totalBlockNum);
    for(int i = 0; i < totalBlockNum; ++i)
        mine_flag[i] = false;
    for(int i = 0; i < totalMineNum; ++i)
        mine_flag[minetmp[i]] = true;


//界面布局
    mainLayout = new QGridLayout(this);
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            mainLayout->addWidget(new Block(mine_flag[i*col+j]),i,j);
        }
    }
    setLayout(mainLayout);

    //每个方块周围雷数目确定
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            Block *block_tmp = static_cast<Block *>(mainLayout->itemAtPosition(i,j)->widget());
            if(!block_tmp->isMine())
                block_tmp->setNumber(calculateMines(i,j));

            //事件处理
            connect(block_tmp,SIGNAL(safe()),this,SLOT(slotSafe()));
            connect(block_tmp,SIGNAL(explode()),this,SLOT(slotExplode()));
            connect(block_tmp,SIGNAL(zero()),this,SLOT(spread()));
            connect(block_tmp,SIGNAL(mineMark()),this,SLOT(markPlus()));
            connect(block_tmp,SIGNAL(mineUnMark()),this,SLOT(markSub()));
        }
    }

    //设置窗体大小
    setFixedSize(sizeHint());
}

int BlockArea::calculateMines(int x, int y) const
{
    int num = 0;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            //判断是否越界
            if( (x-1+i >= 0) && (x-1+i < row) && (y-1+j >= 0) && (y-1+j < col) )
            {
                if(static_cast<Block *>(mainLayout->itemAtPosition(x-1+i,y-1+j)->widget())->isMine())
                    ++num;
            }
        }
    }

    return num;
}

void BlockArea::slotSafe()
{
    ++okBlockNum;
    if(!startClick)
    {
        startClick = true;
        emit firstClick();
    }

    if(okBlockNum == totalBlockNum - totalMineNum)
    {
        emit stopTime();
        QMessageBox::information(this,tr("result"),tr("You win"));
    }
}

void BlockArea::slotExplode()
{
    int i,j,r,c;
    QList<int> list_x;
    QList<int> list_y;

    bool isErgodic[totalBlockNum];
    for(i = 0; i < totalBlockNum; ++i)
        isErgodic[i] = false;


    for(i = 0; i < row; ++i)
    {
        for(j = 0; j < col; ++j)
        {
            Block *tmp_block = static_cast<Block *>(mainLayout->itemAtPosition(i,j)->widget());
            if(tmp_block->markOver)
                break;
        }
        if(j != col)
            break;
    }

    list_x.push_back(i);
    list_y.push_back(j);
    isErgodic[i*col+j] = true;

    while(!list_x.isEmpty())
    {
        r = list_x.first();
        c = list_y.first();
        list_x.pop_front();
        list_y.pop_front();

        for(i = 0; i < 3; ++i)
        {
            for(j = 0; j < 3; ++j)
            {
                //判断是否越界
                int m = r-1+i;
                int n = c-1+j;
                if( (m >= 0) && (m < row) && (n >= 0) && (n < col) )
                {
                    if(!isErgodic[m*col+n])
                    {
                        //访问标记
                        isErgodic[m*col+n] = true;
                        list_x.push_back(m);
                        list_y.push_back(n);

                        Block *tmp_block1 = static_cast<Block *>(mainLayout->itemAtPosition(m,n)->widget());
                        int num = tmp_block1->getNumber();
                        if(!tmp_block1->isOk())
                        {
//                            Sleep(1000);
                            if(!tmp_block1->isMine())
                                tmp_block1->setPixmap(QPixmap(":/imgFile/img/"+QString("%1").arg(num)+".jpg"));
                            else
                                tmp_block1->setPixmap(QPixmap(":/imgFile/img/mine.jpg"));
                        }
                        tmp_block1->update();
                    }
                }
            }
        }

    }
    emit stopTime();
    QMessageBox::information(this,tr("result"),tr("You lose"));

}

void BlockArea::spread()
{
    int i,j;
    int num;
    int r;
    int c;
    QList<int> list_x;
    QList<int> list_y;

    bool isErgodic[totalBlockNum];
    for(i = 0; i < totalBlockNum; ++i)
        isErgodic[i] = false;

    for(i = 0; i < row; ++i)
    {
        for(j = 0; j < col; ++j)
        {
            Block *tmp_block = static_cast<Block *>(mainLayout->itemAtPosition(i,j)->widget());
            if(tmp_block->click_zero)
            {
                tmp_block->click_zero = false;
                break;
            }
        }
        if(j != col)
            break;
    }
    list_x.push_back(i);
    list_y.push_back(j);

    isErgodic[i*col+j] = true;

    while(!list_x.isEmpty())
    {
        r = list_x.first();
        c = list_y.first();
        list_x.pop_front();
        list_y.pop_front();

   //     int aaa = list_x.length();

        for(i = 0; i < 3; ++i)
        {
            for(j = 0; j < 3; ++j)
            {
                //判断是否越界
                int m = r-1+i;
                int n = c-1+j;
                if( (m >= 0) && (m < row) && (n >= 0) && (n < col) )
                {
                    if(!isErgodic[m*col+n])
                    {
                        //访问标记
                        isErgodic[m*col+n] = true;

                        Block *tmp_block1 = static_cast<Block *>(mainLayout->itemAtPosition(m,n)->widget());
                        num = tmp_block1->getNumber();
                        if(!tmp_block1->isOk())
                        {
                            tmp_block1->setPixmap(QPixmap(":/imgFile/img/"+QString("%1").arg(num)+".jpg"));
                            tmp_block1->update();
                            ++okBlockNum;
                        }
                        if(num == 0)
                        {
                            list_x.push_back(m);
                            list_y.push_back(n);
                        }
                    }
                }
            }
        }
    }

    if(okBlockNum == totalBlockNum - totalMineNum)
    {
        emit stopTime();
        QMessageBox::information(this,tr("result"),tr("You win"));
    }
}

void BlockArea::markPlus()
{
    ++markNum;
    emit mineChanged();
}

void BlockArea::markSub()
{
    --markNum;
    emit mineChanged();
}

int BlockArea::getRemainMines()
{
    return totalMineNum-markNum;
}
