#ifndef LOGIN_UI_H
#define LOGIN_UI_H

#include <QMainWindow>
#include "mymainwindow.h"

namespace Ui {
class Login_UI;
}

class Login_UI : public MyMainWindow
{
    Q_OBJECT

public:
    explicit Login_UI(QWidget *parent = nullptr);
    ~Login_UI();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void signal_createEmptyMap();

private slots:
    void slot_loginSuccessfully();

    void on_registerToolButton_clicked();

    void on_loginToolButton_clicked();

private:
    Ui::Login_UI *ui;
};

#endif // LOGIN_UI_H
