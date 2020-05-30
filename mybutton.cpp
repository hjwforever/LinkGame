#include "mybutton.h"
#include<iostream>
using namespace std;

MyButton::MyButton()
{
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    setDown(false);
    update();
    emit clicked(row,column);//当按钮点击后释放时发送信号
}

void MyButton::setCoordinate(int row, int column){
    this->row=row;
    this->column=column;
}

int MyButton::getColumn(){
    return column;
}

int MyButton::getRow(){
    return row;
}
