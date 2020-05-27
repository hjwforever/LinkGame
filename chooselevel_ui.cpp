#include "chooselevel_ui.h"
#include "ui_chooselevel_ui.h"

ChooseLevel_UI::ChooseLevel_UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseLevel_UI)
{
    ui->setupUi(this);
}

ChooseLevel_UI::~ChooseLevel_UI()
{
    delete ui;
}
