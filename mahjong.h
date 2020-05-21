#ifndef MAHJONG_H
#define MAHJONG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Mahjong; }
QT_END_NAMESPACE

class Mahjong : public QMainWindow
{
    Q_OBJECT

public:
    Mahjong(QWidget *parent = nullptr);
    ~Mahjong();

private:
    Ui::Mahjong *ui;
};
#endif // MAHJONG_H
