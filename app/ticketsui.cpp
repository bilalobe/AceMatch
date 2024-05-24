#include "ticketsui.h"
#include "ui_ticketsui.h"

TicketUI::TicketUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TicketUI)
{
    ui->setupUi(this);
}

TicketUI::~TicketUI()
{
    delete ui;
}
