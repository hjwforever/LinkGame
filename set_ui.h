#ifndef SET_UI_H

#include "voiceplayer.h"
#include<QMainWindow>
#include <QPixmap>
#include <QBitmap>
#include<QTcpSocket>
#include<iostream>

#include"messagedialog.h"
#include "mymainwindow.h"

using namespace std;

namespace Ui {
class Set_UI;
}

class Set_UI : public MyMainWindow
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
    void signal_RankMsg(QString rankMsg);

private slots:
    void on_returnButton_clicked();
    void on_BGM_pushButton_clicked();
    void on_image_style_comboBox_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(int index);
    void on_method_and_rule_pushButton_clicked();

    void on_save_set_pushButton_clicked();

    void slotconnectedsuccess();//�����������ӳɹ����ź�
    void slotreceive();//���շ���������������Ϣ
    void slotdisconnected();//���������뿪�����ҵ��ź�

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
    QString serverIP="47.110.14.59";//"127.0.0.1";//
    QTcpSocket *tcpsocket=new QTcpSocket(this);
};

#endif // SET_UI_H
