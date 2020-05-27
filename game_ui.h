#ifndef GAME_UI_H
#define GAME_UI_H

#include <QMainWindow>

namespace Ui {
class Game_UI;
}

class Game_UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game_UI(QWidget *parent = nullptr);
    ~Game_UI();

private:
    Ui::Game_UI *ui;
};

#endif // GAME_UI_H
