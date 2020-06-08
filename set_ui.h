#ifndef SET_UI_H

#include "voiceplayer.h"
#include<QMainWindow>
#include <QPixmap>
#include <QBitmap>
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

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_returnButton_clicked();
    void on_BGM_pushButton_clicked();
    void on_image_style_comboBox_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(int index);
    void on_method_and_rule_pushButton_clicked();

private:
    Ui::Set_UI *ui;
    string parentName="";
    bool isopen=false;

public:
    int currentModelNum = 0;
};

#endif // SET_UI_H
