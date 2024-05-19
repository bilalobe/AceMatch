#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playerbox.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Declare playerBox as a member variable
    playerBox = new PlayerBox(this);

    // Set PlayerBox as the central widget
    setCentralWidget(playerBox);

    // Connect signals from PlayerBox
    connect(playerBox, &PlayerBox::playerAdded, this, &MainWindow::handlePlayerAdded);
    connect(playerBox, &PlayerBox::playerRemoved, this, &MainWindow::handlePlayerRemoved);
    connect(playerBox, &PlayerBox::playerUpdated, this, &MainWindow::handlePlayerUpdated);
    connect(playerBox, &PlayerBox::playerSearched, this, &MainWindow::handlePlayerSearched);

    // ... (rest of your MainWindow code) ...
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlePlayerAdded(const QString& name, int ranking) {
    // Handle the addition of a new player in your main application logic
    qDebug() << "Player Added:" << name << "with ranking" << ranking;
}

void MainWindow::handlePlayerRemoved(const QString& name) {
    // Handle the removal of a player in your main application logic
    qDebug() << "Player Removed:" << name;
}

void MainWindow::handlePlayerUpdated(const QString& name, int newRanking) {
    // Handle the update of a player in your main application logic
    qDebug() << "Player Updated:" << name << "with new ranking" << newRanking;
}

void MainWindow::handlePlayerSearched(const QString& searchTerm) {
    // Handle the search query in your main application logic
    qDebug() << "Search Term:" << searchTerm;
}
