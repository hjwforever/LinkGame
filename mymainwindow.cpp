#include "mymainwindow.h"

MyMainWindow::MyMainWindow(QWidget *parent) : QMainWindow(parent)
{
}
MyMainWindow::~MyMainWindow()
{
}
void MyMainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        flag = true;
        mousePoint = event->globalPos() - this->pos();
        event->accept();
    }
}
void MyMainWindow::mouseMoveEvent(QMouseEvent *event)
{
if (flag && (event->buttons() && Qt::LeftButton) )//&& event->pos().y() < 100 && event->pos().y() > 0)
    {
        move(event->globalPos() - mousePoint);
        event->accept();
    }
}
void MyMainWindow::mouseReleaseEvent(QMouseEvent *)
{
    flag = false;
}
