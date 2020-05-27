#include "linkgame.h"
#include "ui_linkgame.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSysInfo>

LinkGame::LinkGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LinkGame)
{
    ui->setupUi(this);
}

LinkGame::~LinkGame()
{
    delete ui;
}

