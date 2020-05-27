#include "set_ui.h"
#include "ui_set_ui.h"

Set_UI::Set_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Set_UI)
{
    ui->setupUi(this);
}

Set_UI::~Set_UI()
{
    delete ui;
}
