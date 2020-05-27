#ifndef SET_UI_H
#define SET_UI_H

#include <QMainWindow>

namespace Ui {
class Set_UI;
}

class Set_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit Set_UI(QWidget *parent = nullptr);
    ~Set_UI();

private:
    Ui::Set_UI *ui;
};

#endif // SET_UI_H
