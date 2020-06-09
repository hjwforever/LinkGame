#ifndef REGISTER_UI_H
#define REGISTER_UI_H

#include <QMainWindow>
#include "mymainwindow.h"

namespace Ui {
class Register_UI;
}

class Register_UI : public MyMainWindow
{
    Q_OBJECT

public:
    explicit Register_UI(QWidget *parent = nullptr);
    ~Register_UI();

private slots:
    void slot_SignInSuccessfully();
    void on_sureToolButton_clicked();

private:
    Ui::Register_UI *ui;
};

#endif // REGISTER_UI_H
