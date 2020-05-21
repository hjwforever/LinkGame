#include "mahjong.h"
#include "ui_mahjong.h"

Mahjong::Mahjong(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Mahjong)
{
    ui->setupUi(this);
}

Mahjong::~Mahjong()
{
    delete ui;
}

