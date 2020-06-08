#include "messagedialog.h"
#include "ui_messagedialog.h"

MessageDialog::MessageDialog(QWidget *parent,QString message) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
    ui->messageTextBrowser->setText(message);
    QPixmap pixmap1(":/image/button_icon/chooselevel_ui/return.png");
    ui->returnPushButton->resize(pixmap1.size());
    ui->returnPushButton->setIcon(pixmap1);
    ui->returnPushButton->setIconSize(pixmap1.size());
    ui->returnPushButton->setMask(pixmap1.mask());
    ui->returnPushButton->setStyleSheet("QToolButton{border:0px;}");
}

MessageDialog::~MessageDialog()
{
    delete ui;
}

void MessageDialog::on_returnPushButton_clicked()
{
    close();
}
