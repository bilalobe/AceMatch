
#include "playerbox.h"
#include "qsqldatabase.h"
#include "ui_playerbox.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

PlayerBox::PlayerBox(QWidget *parent, const QSqlDatabase& database)
    : QWidget(parent), ui(new Ui::PlayerBox), db(database)
{
    ui->setupUi(this);

    // Initialize the playersModel
    playersModel = new QStandardItemModel(0, 2, this);
    playersModel->setHeaderData(0, Qt::Horizontal, tr("Nom"));
    playersModel->setHeaderData(1, Qt::Horizontal, tr("Classement"));
    ui->playerTableView->setModel(playersModel); // Assuming you have a QTableView named playerTableView

    // Connect signals and slots
    connect(ui->addPlayerButton, &QPushButton::clicked, this, &PlayerBox::addPlayer);
    connect(ui->deletePlayerButton, &QPushButton::clicked, this, &PlayerBox::deletePlayer);
    connect(ui->updatePlayerButton, &QPushButton::clicked, this, &PlayerBox::updatePlayer);
    connect(ui->playerTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &PlayerBox::loadPlayerDetails);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &PlayerBox::searchPlayer);

    // Update the player list
    updatePlayerList();
}

PlayerBox::~PlayerBox() {
    delete ui;
    delete playersModel;
}

void PlayerBox::addPlayer() {
    QString name = ui->nomLineEdit->text();
    int classement = ui->classementSpinBox->value();

    // Basic input validation (you can add more)
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le name du player ne peut pas être vide.");
        return;
    }

    // Create a Player object
    Tournament::Player newJoueur(name, classement);

    // Insert the player into the database
    QSqlQuery query(db);
    query.prepare("INSERT INTO Joueurs (name, classement) VALUES (:name, :classement)");
    query.bindValue(":name", name);
    query.bindValue(":classement", classement);
    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'insertion du player dans la base de données.");
        return;   }

    // Emit signal to notify MainWindow
    emit playerAdded(newJoueur);

    // Clear input fields
    ui->nomLineEdit->clear();
    ui->classementSpinBox->setValue(0);

    // Update the player list
    updatePlayerList();
}

void PlayerBox::deletePlayer() {
    QModelIndexList selectedIndexes = ui->playerTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun player sélectionné.");
        return;
    }

    QString name = selectedIndexes.at(0).data(Qt::DisplayRole).toString();

    // Confirmation Dialog
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Supprimer le player",
                                                              "Êtes-vous sûr de vouloir supprimer ce player?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Delete the player from the database
        QSqlQuery query(db);
        query.prepare("DELETE FROM Joueurs WHERE name = :name");
        query.bindValue(":name", name);
        if (!query.exec()) {
            QMessageBox::warning(this, "Erreur", "Erreur lors de la suppression du player de la base de données.");
            return;
        }

        emit playerDeleted(name);
        updatePlayerList();
        clearPlayerDetails();
    }
}

void PlayerBox::updatePlayer() {
    QModelIndexList selectedIndexes = ui->playerTableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun player sélectionné.");
        return;
    }

    QString name = ui->nomLineEdit->text();
    int classement = ui->classementSpinBox->value();

    // Basic input validation (you can add more)
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le name du player ne peut pas être vide.");
        return;
    }

    // Create a Player object
    Tournament::Player updatedJoueur(name, classement);

    // Update the player in the database
    QSqlQuery query(db);
    query.prepare("UPDATE Joueurs SET name = :name, classement = :classement WHERE name = :oldNom");   query.bindValue(":name", name);
    query.bindValue(":classement", classement);
    query.bindValue(":oldNom", selectedIndexes.at(0).data(Qt::DisplayRole).toString());
    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la mise à jour du player dans la base de données.");
        return;
    }

    // Emit signal to notify MainWindow
    emit playerUpdated(updatedJoueur);

    // Update the player list
    updatePlayerList();
}

void PlayerBox::loadPlayerDetails(const QModelIndex& index) {
    if (!index.isValid()) {
        clearPlayerDetails();
        return;
    }

    // Get the data from the selected row
    QString name = index.siblingAtColumn(0).data(Qt::DisplayRole).toString();
    int classement = index.siblingAtColumn(1).data(Qt::DisplayRole).toInt();

    // Display the data in the details section
    ui->nomLineEdit->setText(name);
    ui->classementSpinBox->setValue(classement);
}

void PlayerBox::clearPlayerDetails() {
    ui->nomLineEdit->clear();
    ui->classementSpinBox->setValue(0);
}

void PlayerBox::updatePlayerList() {
    // Get players from MainWindow's PlayerManager
    QList<Tournament::Player> players = dynamic_cast<MainWindow*>(parent())->getGestionJoueurs()->getPlayers(db);

    playersModel->clear();
    for (const Tournament::Player& player : players) {
        int row = playersModel->rowCount();
        playersModel->insertRow(row);
        playersModel->setData(playersModel->index(row, 0), joueur.getName());
        playersModel->setData(playersModel->index(row, 1), joueur.getClassement());
    }
}

void PlayerBox::searchPlayer(const QString& searchTerm) {
    playersModel->clear(); // Clear the existing model data
    playersModel->setHorizontalHeaderLabels({"Nom", "Classement"});

    QList<Tournament::Player> players = dynamic_cast<MainWindow*>(parent())->getGestionJoueurs()->getPlayers(db); 

    for (const Tournament::Player& joueur : players) {
        if (joueur.getName().contains(searchTerm, Qt::CaseInsensitive)){
            int row = playersModel->rowCount();
            playersModel->insertRow(row);
            playersModel->setData(playersModel->index(row, 0), joueur.getName());
            playersModel->setData(playersModel->index(row, 1), joueur.getClassement());
        }
    }
}

void PlayerBox::PlayerSelectionChanged() {   // Get the selected player's name
    QString selectedPlayerName = ui->playerTableView->model()->data(ui->playerTableView->selectionModel()->currentIndex()).toString();

    // Emit the signal with the selected player's name
    emit playerSelected(selectedPlayerName);
}

void PlayerBox::on_addPlayerButton_clicked() {
    addPlayer();
}

void PlayerBox::on_deletePlayerButton_clicked() {
    deletePlayer();
}

void PlayerBox::on_updatePlayerButton_clicked() {
    updatePlayer();
}

void PlayerBox::on_searchPlayerLineEdit_textChanged(const QString& searchTerm) {
    searchPlayer(searchTerm);
}

void PlayerBox::on_playerTableView_clicked(const QModelIndex& index) {
    loadPlayerDetails(index);
}

void PlayerBox::on_playerTableView_doubleClicked(const QModelIndex& index) {
    updatePlayer();
}

