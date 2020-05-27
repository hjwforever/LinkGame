#ifndef CHOOSELEVEL_UI_H
#define CHOOSELEVEL_UI_H

#include <QMainWindow>

namespace Ui {
class ChooseLevel_UI;
}

class ChooseLevel_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseLevel_UI(QWidget *parent = nullptr);
    ~ChooseLevel_UI();

private:
    Ui::ChooseLevel_UI *ui;
};

#endif // CHOOSELEVEL_UI_H
