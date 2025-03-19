#include "playerui.h"
#include "ui_playerui.h"
#include <QMessageBox>

PlayerUI::PlayerUI(QWidget *parent, const QSqlDatabase& database)
    : QWidget(parent), ui(new Ui::PlayerUI), db(database)
{
    ui->setupUi(this);

    // Initialize the playersModel
    playersModel = new QStandardItemModel(0, 2, this);
    playersModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
    playersModel->setHeaderData(1, Qt::Horizontal, tr("Ranking"));
    ui->playerTableView->setModel(playersModel); // Assuming you have a QTableView named playerTableView

    // Connect signals and slots
    connect(ui->addPlayerButton, &QPushButton::clicked, this, &PlayerUI::addPlayer);
    connect(ui->deletePlayerButton, &QPushButton::clicked, this, &PlayerUI::deletePlayer);
    connect(ui->updatePlayerButton, &QPushButton::clicked, this, &PlayerUI::updatePlayer);
    connect(ui->playerTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &PlayerUI::loadPlayerDetails);

    // Update the player list
    updatePlayerList();
}

PlayerUI::~PlayerUI() {
    delete ui;
    delete playersModel;
}

void PlayerUI::addPlayer() {
    QString name = ui->playerNameLineEdit->text();
    int ranking = ui->playerRankingSpinBox->value();

    // Basic input validation (you can add more)
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Player name cannot be empty.");
        return;
    }

    // Create a Player object
    Tournament::Player newJoueur(name, ranking);

    // Emit signal to notify MainWindow
    emit playerAdded(newJoueur);

    // Clear input fields
    ui->playerNameLineEdit->clear();
    ui->playerRankingSpinBox->setValue(0);

    // Update the player list
    updatePlayerList();
}

void PlayerUI::deletePlayer() {
    QModelIndexList selectedIndexes = ui->playerTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No player selected.");
        return;
    }

    QString playerName = selectedIndexes.at(0).data(Qt::DisplayRole).toString();

    // Confirmation Dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Player",
                                                              "Are you sure you want to delete this player?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit playerDeleted(playerName);
        updatePlayerList();
        clearPlayerDetails();
    }
}

void PlayerUI::updatePlayer() {
    QModelIndexList selectedIndexes = ui->playerTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Error", "No player selected.");
        return;
    }

    QString name = ui->playerNameLineEdit->text();
    int ranking = ui->playerRankingSpinBox->value();

    // Basic input validation (you can add more)
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Player name cannot be empty.");
        return;
    }

    // Create a Player object
    Tournament::Player updatedJoueur(name, ranking);

    // Emit signal to notify MainWindow
    emit playerUpdated(updatedJoueur);

    // Update the player list
    updatePlayerList();
}

void PlayerUI::loadPlayerDetails(const QModelIndex& index) {
    if (!index.isValid()) {
        clearPlayerDetails();
        return;
    }

    // Get the data from the selected row
    QString name = index.siblingAtColumn(0).data(Qt::DisplayRole).toString();
    int ranking = index.siblingAtColumn(1).data(Qt::DisplayRole).toInt();

    // Display the data in the details section
    ui->playerNameLineEdit->setText(name);
    ui->playerRankingSpinBox->setValue(ranking);
}

void PlayerUI::clearPlayerDetails() {
    ui->playerNameLineEdit->clear();
    ui->playerRankingSpinBox->setValue(0);
}

void PlayerUI::updatePlayerList() {
    // Get players from MainWindow's PlayerManager
    QList<Tournament::Player> players = dynamic_cast<MainWindow*>(parent())->getGestionJoueurs()->getPlayers(db);

    playersModel->clear();
    for (const Tournament::Player& joueur : players) {
        int row = playersModel->rowCount();
        playersModel->insertRow(row);
        playersModel->setData(playersModel->index(row, 0), joueur.getName());
        playersModel->setData(playersModel->index(row, 1), joueur.getRang());
    }
}
