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
    void setLevel(int level);
    int getLevel();

private slots:
    void on_returnButton_clicked();

private:
    Ui::Game_UI *ui;
    int level=1;
};

#endif // GAME_UI_H
