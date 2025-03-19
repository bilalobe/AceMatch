#include "../../mainwindow.h"
#include "ui/ui_matchui.h"
#include "../Matchui.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "../Match.h"
#include "data/

MatchUI::MatchUI(QWidget *parent, const QSqlDatabase& database)
    : QWidget(parent), ui(new Ui::MatchUI), db(database)
{
    ui->setupUi(this);

    // Get access to your PlayerManager instance
    playerManager = dynamic_cast<MainWindow*>(parent)->getGestionJoueurs();
    if (!playerManager) {
        qDebug() << "Error: Could not access PlayerManager.";
        return;
    }

    // Initialize the matchModel
    matchModel = new QStandardItemModel(0, 4, this);
    matchModel->setHeaderData(0, Qt::Horizontal, tr("Player 1"));
    matchModel->setHeaderData(1, Qt::Horizontal, tr("Player 2"));
    matchModel->setHeaderData(2, Qt::Horizontal, tr("Score 1"));
    matchModel->setHeaderData(3, Qt::Horizontal, tr("Score 2"));
    ui->matchTableView->setModel(matchModel);

    // Populate combo boxes and match list
    updatePlayerComboBoxes();
    updateMatchList();

    // Connect signals and slots:
    connect(ui->createMatchButton, &QPushButton::clicked, this, &MatchUI::createMatch);
    connect(ui->matchTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MatchUI::updateMatchDetails);
    connect(ui->deleteMatchButton, &QPushButton::clicked, this, &MatchUI::deleteMatch);
    connect(ui->updateMatchButton, &QPushButton::clicked, this, &MatchUI::updateMatch);
}

MatchUI::~MatchUI()
{
    delete ui;
    delete matchModel;
}

void MatchUI::createMatch()
{
    QString player1Name = ui->player1ComboBox->currentText();
    QString player2Name = ui->player2ComboBox->currentText();

    if (player1Name == player2Name) {
        QMessageBox::warning(this, "Error", "Please select different players.");
        return;
    }

    int score1 = ui->score1SpinBox->value();
    int score2 = ui->score2SpinBox->value();

    // Emit the matchCreated signal (use correct variable names)
    emit matchCreated(player1Name, player2Name, score1, score2);

    // Clear input fields
    ui->score1SpinBox->setValue(0);
    ui->score2SpinBox->setValue(0);

    // Update the match list
    updateMatchList();
}

void MatchUI::updateMatchList()
{
    matchModel->clear();
    matchModel->setHorizontalHeaderLabels({"Player 1", "Player 2", "Score 1", "Score 2"});

    // Get matches from PlayerManager
    QList<Match> matches = playerManager->getMatches(db);

    for (const Match& match : matches) {
        int row = matchModel->rowCount();
        matchModel->insertRow(row);

        // Use the correct variable names and getter methods from your Match class
        matchModel->setData(matchModel->index(row, 0), match.getPlayer1().getName());
        matchModel->setData(matchModel->index(row, 1), match.getPlayer2().getName());
        matchModel->setData(matchModel->index(row, 2), match.getScore1());
        matchModel->setData(matchModel->index(row, 3), match.getScore2());
    }
}

void MatchUI::updateMatchDetails(const QModelIndex& index)
{
    if (!index.isValid()) {
        clearMatchDetails();
        return;
    }

    int row = index.row();
    Match selectedMatch = playerManager->getMatches(db)[row];

    // Use the correct getter methods from your Match and Player classes
    ui->player1NameLabel->setText(selectedMatch.getPlayer1().getName());
    ui->player2NameLabel->setText(selectedMatch.getPlayer2().getName());
    ui->player1ScoreLabel->setText(QString::number(selectedMatch.getScore1()));
    ui->player2ScoreLabel->setText(QString::number(selectedMatch.getScore2()));
}

void MatchUI::clearMatchDetails()
{
    ui->player1NameLabel->clear();
    ui->player2NameLabel->clear();
    ui->player1ScoreLabel->clear();
    ui->player2ScoreLabel->clear();
}

void MatchUI::deleteMatch()
{
    QModelIndexList selectedIndexes = ui->matchTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No match selected.");
        return;
    }

    // Assuming you have a Match ID or a way to uniquely identify matches:
    int matchId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get match ID from UserRole

    // Emit the matchDeleted signal
    emit matchDeleted(matchId);

    // Update the match list
    updateMatchList();
    clearMatchDetails();
}

void MatchUI::updateMatch() {
    QModelIndexList selectedIndexes = ui->matchTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No match selected.");
        return;
    }

    // Assuming you have a Match ID or a way to uniquely identify matches:
    int matchId = selectedIndexes.at(0).data(Qt::UserRole).toInt(); // Get match ID from UserRole

    int newScore1 = ui->score1SpinBox->value();
    int newScore2 = ui->score2SpinBox->value();

    // Emit the matchUpdated signal
    emit matchUpdated(matchId, newScore1, newScore2);

    // Clear input fields
    ui->score1SpinBox->setValue(0);
    ui->score2SpinBox->setValue(0);

    // Update the match list
    updateMatchList();
}

void MatchUI::updatePlayerComboBoxes() {
    ui->player1ComboBox->clear();
    ui->player2ComboBox->clear();

    QList<Player> players = playerManager->getPlayers(db);

    for (const Player& player : players) {
        ui->player1ComboBox->addItem(player.getName());
        ui->player2ComboBox->addItem(player.getName());
    }
}

void MatchUI::searchMatch(const QString& searchTerm) {
    matchModel->clear();
    matchModel->setHorizontalHeaderLabels({"Player 1", "Player 2", "Score 1", "Score 2"});

    QList<Match> matches = playerManager->getMatches(db);

    for (const Match& match : matches) {
        if (match.getPlayer1().getName().contains(searchTerm, Qt::CaseInsensitive) ||
            match.getPlayer2().getName().contains(searchTerm, Qt::CaseInsensitive)) {

            int row = matchModel->rowCount();
            matchModel->insertRow(row);

            matchModel->setData(matchModel->index(row, 0), match.getPlayer1().getName());
            matchModel->setData(matchModel->index(row, 1), match.getPlayer2().getName());
            matchModel->setData(matchModel->index(row, 2), match.getScore1());
            matchModel->setData(matchModel->index(row, 3), match.getScore2());
        }
    }
}

void MatchUI::clearSearch() {
    ui->searchLineEdit->clear();
    updateMatchList();
}

