#include <block.h>

Block::Block(bool isMine, QWidget *parent) : QLabel(parent)
{
    resize(8,8);
    mine_flag = isMine;
    ok_flag = false;
    mark_flag = false;
    click_zero = false;
    markOver = false;

    number = -1;
    setPixmap(QPixmap(":/imgFile/img/blue.jpg"));
}

void Block::setNumber(int num)
{
    number = num;
}

int Block::getNumber()
{
    return number;
}

bool Block::isMine() const
{
    return mine_flag;
}

bool Block::isOk() const
{
    return ok_flag;
}

void Block::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(!ok_flag && !mark_flag)
        {
            ok_flag = true;
            if(mine_flag)
            {
                setPixmap(QPixmap(":/imgFile/img/mine.jpg"));
                markOver = true;
                update();
                emit explode();
            }
            else
            {
                setPixmap(QPixmap(":/imgFile/img/"+QString("%1").arg(number)+".jpg"));
                update();
                emit safe();

                if(number == 0)
                {
                    click_zero = true;
                    emit zero();
                }
            }
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        if(!ok_flag)
        {
            if(!mark_flag)
            {
                mark_flag = true;
                setPixmap(QPixmap(":/imgFile/img/flag.jpg"));
                emit mineMark();
            }
            else
            {
                mark_flag = false;
                setPixmap(QPixmap(":/imgFile/img/blue.jpg"));
                emit mineUnMark();
            }
            update();
        }
    }
}

/*
void Block::safe()
{

}

void Block::explode()
{

}
*/


