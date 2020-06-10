#ifndef RANKINGLIST_H
#define RANKINGLIST_H

#include <QMainWindow>

namespace Ui {
class RankingList;
}

class RankingList : public QMainWindow
{
    Q_OBJECT

public:
    explicit RankingList(QWidget *parent = nullptr);
    ~RankingList();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void slot_GetRankMsg(QString rankMsg);

private:
    Ui::RankingList *ui;
};

#endif // RANKINGLIST_H
