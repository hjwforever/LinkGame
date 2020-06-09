#ifndef SET_UI_H

#include "voiceplayer.h"
#include<QMainWindow>
#include <QPixmap>
#include <QBitmap>
#include<QTcpSocket>
#include<iostream>

#include"messagedialog.h"

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

    void connectToServer();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void signal_signInSuccessfully();
    void signal_loginSuccessfully();
    void signal_startPK(int** gameMap);
    void signal_ChangeHasPrepared(bool win);

private slots:
    void on_returnButton_clicked();
    void on_BGM_pushButton_clicked();
    void on_image_style_comboBox_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(int index);
    void on_method_and_rule_pushButton_clicked();

    void on_save_set_pushButton_clicked();

    void slotconnectedsuccess();//用来处理连接成功的信号
    void slotreceive();//接收服务器传过来的信息
    void slotdisconnected();//用来处理离开聊天室的信号

private:
    Ui::Set_UI *ui;
    string parentName="";
    bool isopen=false;

public:
    int currentModelNum = 0;
    bool hasLogin=false;
    bool ispking=false;
    bool isTwoPeople=true;
    QString name="";
    QString mail="";

    int port=8888;
    QString serverIP="47.110.14.59";
    QTcpSocket *tcpsocket;
};

#endif // SET_UI_H
