#include "rankinglist.h"
#include "ui_rankinglist.h"
#include"set_ui.h"

extern Set_UI *set_ui;

RankingList::RankingList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RankingList)
{
    ui->setupUi(this);

    connect(set_ui,SIGNAL(signal_RankMsg(QString)),this,SLOT(slot_GetRankMsg(QString)));
}

RankingList::~RankingList()
{
    delete ui;
}

void RankingList::closeEvent(QCloseEvent *event){
    delete this;
}

void RankingList::slot_GetRankMsg(QString rankMsg){
    ui->rankingListLabel->setText(rankMsg);
}

