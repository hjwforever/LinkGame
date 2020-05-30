#ifndef MYBUTTON_H
#define MYBUTTON_H

#include<QPushButton>

class MyButton : public QPushButton
{

    Q_OBJECT

public:
    MyButton();
    void mouseReleaseEvent(QMouseEvent *ev);

signals:
    void clicked(int row,int column);

public:
    void setCoordinate(int row,int column);  //设置button在数组中的下标
    int getRow();
    int getColumn();
private:
    int row=0;
    int column=0;
};

#endif // MYBUTTON_H
