#include "placesui.h"
#include "ui_placesui.h"

PlacesUI::PlacesUI(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::PlacesUI)
{
    ui->setupUi(this);
}

PlacesUI::~PlacesUI()
{
    delete ui;
}
