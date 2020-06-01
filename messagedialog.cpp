#include "messagedialog.h"
#include "ui_messagedialog.h"

MessageDialog::MessageDialog(QWidget *parent,QString message) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
    ui->messageTextBrowser->setText(message);
}

MessageDialog::~MessageDialog()
{
    delete ui;
}

void MessageDialog::on_returnPushButton_clicked()
{
    close();
}
