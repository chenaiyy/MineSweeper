#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <QMouseEvent>

class Block : public QLabel
{
    Q_OBJECT

public:
    explicit Block(bool mine_flag, QWidget *parent = 0);
    void setNumber(int num);
    int getNumber();
    bool isOk() const;
    bool isMine() const;

signals:
    void explode();
    void safe();
    //扩散
    void zero();
    void mineMark();
    void mineUnMark();

protected:
    void mousePressEvent(QMouseEvent *e);
//    bool eventFilter(QObject *, QEvent *);

private:
    bool mine_flag;
    bool ok_flag;
    bool mark_flag;
    int number;

public:
    bool click_zero;
    bool markOver;
};

#endif // BLOCK

