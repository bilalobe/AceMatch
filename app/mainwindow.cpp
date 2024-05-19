
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the Add Player button to the addPlayerSlot
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addPlayerSlot);
}

void MainWindow::addPlayerSlot() {
    // Get the player's name and ranking from the text boxes
    QString name = ui->nameInput->text();
    int ranking = ui->rankingInput->text().toInt();

    // Call the addPlayer method on your TennisChampionship object
    tennisChampionship.addPlayer(name.toStdString(), ranking);

    // Update the UI (e.g., display the new player in a list widget)
    // ...
}

// ... (Other methods to handle other UI actions) ...
