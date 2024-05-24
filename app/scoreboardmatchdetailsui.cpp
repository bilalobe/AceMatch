#include "scoreboardmatchdetailsui.h"
#include "ui_scoreboardmatchdetailsui.h"

scoreboardmatchdetailsui::scoreboardmatchdetailsui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::scoreboardmatchdetailsui)
{
    ui->setupUi(this);
}

scoreboardmatchdetailsui::~scoreboardmatchdetailsui()
{
    delete ui;
}
