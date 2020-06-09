#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include<QMainWindow>
#include<QMouseEvent>
class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyMainWindow(QWidget *parent = 0);
    ~MyMainWindow();
signals:
public:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *);
public:
    QPoint mousePoint;
    bool flag;
};

#endif // MYMAINWINDOW_H
