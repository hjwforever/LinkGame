#ifndef SET_UI_H
#define SET_UI_H

#include <QMainWindow>
#include<iostream>
using namespace std;

namespace Ui {
class Set_UI;
}

class Set_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit Set_UI(QWidget *parent = nullptr);
    ~Set_UI();

    void setParentName(string parentName);
    string getParentName();

private slots:
    void on_returnButton_clicked();

private:
    Ui::Set_UI *ui;
    string parentName="";
};

#endif // SET_UI_H
