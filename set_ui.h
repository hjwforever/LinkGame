#ifndef SET_UI_H
#define SET_UI_H

#include <QMainWindow>
#include<iostream>
#include "voiceplayer.h"
#include"musicthread.h"

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
    VoicePlayer *voiceplayer;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_returnButton_clicked();

    void on_BGM_pushButton_clicked();

private:
    Ui::Set_UI *ui;
    string parentName="";

public:
    MusicThread musicThread;
};

#endif // SET_UI_H
