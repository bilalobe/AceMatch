#include "playerprofileui.h"
#include "ui_playerprofileui.h"

PlayerProfileUI::PlayerProfileUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerProfileUI)
{
    ui->setupUi(this);
}

PlayerProfileUI::~PlayerProfileUI()
{
    delete ui;
}
