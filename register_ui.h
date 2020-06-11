#ifndef REGISTER_UI_H
#define REGISTER_UI_H

#include <QMainWindow>
#include <QPixmap>
#include <QBitmap>
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

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void slot_SignInSuccessfully();
    void on_sureToolButton_clicked();


    void on_captchaToolButton_clicked();

    void on_returnButton_clicked();

private:
    Ui::Register_UI *ui;
};

#endif // REGISTER_UI_H
