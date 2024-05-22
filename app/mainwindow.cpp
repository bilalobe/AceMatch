#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scoreboard(new Scoreboard(this)) {
    ui->setupUi(this);

    playerBox = new PlayerBox(this);
    ui->centralWidget->layout()->addWidget(playerBox);

    connect(scoreboard, &Scoreboard::resultsChanged, this, &MainWindow::updateResultsView);

    // Initialize other UI components, menus, etc.
}

MainWindow::~MainWindow() {
    delete ui;
}

connect(scoreboard, &Scoreboard::resultsChanged, this, &MainWindow::updateResultsView);

void MainWindow::updateResultsView() {
    QList<MatchResult*> results = scoreboard->getAllResults();
    QStringList resultList;
    for (const auto &result : results) {
        resultList << QString("%1 vs %2: %3")
                          .arg(result->getPlayer1()->getName())
                          .arg(result->getPlayer2()->getName())
                          .arg(result->getScore());
    }
    ui->resultsListView->clear();
    ui->resultsListView->addItems(resultList);
}

