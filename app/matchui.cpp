#include "matchui.h"
#include "ui_matchui.h"

MatchUI::MatchUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatchUI)
{
    ui->setupUi(this);
}

MatchUI::~MatchUI()
{
    delete ui;
}
