#ifndef LINKGAME_H
#define LINKGAME_H

#include <QMainWindow>
#include <QSqlDatabase>
#include"messagedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LinkGame; }
QT_END_NAMESPACE

class LinkGame : public QMainWindow
{
    Q_OBJECT

public:
    LinkGame(QWidget *parent = nullptr);
    ~LinkGame();

private slots:
    void on_onePersonButton_clicked();
    void on_twoPersonButton_clicked();
    void on_setButton_clicked();

    void on_exitButton_clicked();

    void on_aboutButton_clicked();

private:
    Ui::LinkGame *ui;
};
#endif // LINKGAME_H
