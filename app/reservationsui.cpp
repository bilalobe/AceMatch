#include "reservationsui.h"
#include "ui_reservationsui.h"

ReservationsUI::ReservationsUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReservationsUI)
{
    ui->setupUi(this);
}

ReservationsUI::~ReservationsUI()
{
    delete ui;
}
