#ifndef CHOOSELEVEL_UI_H
#define CHOOSELEVEL_UI_H

#include <QMainWindow>
#include <QPixmap>
#include <QBitmap>
#include "mymainwindow.h"

namespace Ui {
class ChooseLevel_UI;
}

class ChooseLevel_UI : public MyMainWindow
{
    Q_OBJECT

public:
    explicit ChooseLevel_UI(QWidget *parent = nullptr);
    ~ChooseLevel_UI();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_easyButton_clicked();
    void on_normalButton_clicked();
    void on_hardButton_clicked();
    void on_returnButton_clicked();

signals:
    void createMap();

private:
    Ui::ChooseLevel_UI *ui;
};

#endif // CHOOSELEVEL_UI_H
