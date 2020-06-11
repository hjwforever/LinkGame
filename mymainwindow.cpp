#include "mymainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>


MyMainWindow::MyMainWindow(QWidget *parent) : QMainWindow(parent)
{

      this->setWindowFlags( Qt::WindowStaysOnTopHint); //|Qt::FramelessWindowHint
      resize(400, 300);
      setWindowTitle("LinkGame");
      setWindowIcon(QIcon(":/image/button_icon/fruit/8.png"));

}
MyMainWindow::~MyMainWindow()
{
}
void MyMainWindow::mousePressEvent(QMouseEvent *event)
{
//    if (event->buttons() == Qt::LeftButton)
//    {
//        flag = true;
//        mousePoint = event->globalPos() - this->pos();
//        event->accept();
//    }
}
void MyMainWindow::mouseMoveEvent(QMouseEvent *event)
{
//if (flag && (event->buttons() && Qt::LeftButton) )//&& event->pos().y() < 100 && event->pos().y() > 0)
//    {
//        move(event->globalPos() - mousePoint);
//        event->accept();
//    }
}
void MyMainWindow::mouseReleaseEvent(QMouseEvent *)
{
//    flag = false;
}
