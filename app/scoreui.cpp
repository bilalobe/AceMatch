#include "scoreui.h"
#include "ui_scoreui.h"
#include <QMessageBox>

ScoreUI::ScoreUI(QWidget *parent, const QSqlDatabase& database)
    : QWidget(parent), ui(new Ui::ScoreUI), db(database)
{
    ui->setupUi(this);

    // Initialize the scoresModel
    scoresModel = new QStandardItemModel(0, 4, this); // 4 columns (ID, Match, Score 1, Score 2)
    scoresModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    scoresModel->setHeaderData(1, Qt::Horizontal, tr("Match"));
    scoresModel->setHeaderData(2, Qt::Horizontal, tr("Score 1"));
    scoresModel->setHeaderData(3, Qt::Horizontal, tr("Score 2"));
    ui->scoresTableView->setModel(scoresModel);

    // Set ID field to read-only
    ui->idLineEdit->setReadOnly(true);

    // Update combo box and scores list
    updateMatchComboBox();
    updateScoresList();

    // Connect signals and slots:
    connect(ui->addScoreButton, &QPushButton::clicked, this, &ScoreUI::addScore);
    connect(ui->deleteScoreButton, &QPushButton::clicked, this, &ScoreUI::deleteScore);
    connect(ui->updateScoreButton, &QPushButton::clicked, this, &ScoreUI::updateScore);
    connect(ui->scoresTableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &ScoreUI::loadScoreDetails);
}

ScoreUI::~ScoreUI() {
    delete ui;
    delete scoresModel;
}

void ScoreUI::addScore() {
    int matchId = ui->matchComboBox->currentData().toInt(); 
    int score1 = ui->score1SpinBox->value();
    int score2 = ui->score2SpinBox->value();

    emit scoreAdded(matchId, score1, score2);

    // Clear input fields
    ui->matchComboBox->setCurrentIndex(0); // Reset combo box
    ui->score1SpinBox->setValue(0);
    ui->score2SpinBox->setValue(0);

    // Update the scores list
    updateScoresList();
}

bool GestionScore::supprimerScore(const QSqlDatabase& db, int scoreId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Scores WHERE id = :scoreId");
    query.bindValue(":scoreId", scoreId);

    if (!query.exec()) {
        qDebug() << "Error deleting score:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionScore::modifierScore(const QSqlDatabase& db, int scoreId, int newScore1, int newScore2) {
    QSqlQuery query(db);
    query.prepare("UPDATE Scores SET score1 = :newScore1, score2 = :newScore2 WHERE id = :scoreId");
    query.bindValue(":newScore1", newScore1);
    query.bindValue(":newScore2", newScore2);
    query.bindValue(":scoreId", scoreId);

    if (!query.exec()) {
        qDebug() << "Error updating score:" << query.lastError();
        return false;
    }
    return true;
}

Score GestionScore::getScoreById(const QSqlDatabase& db, int scoreId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Scores WHERE id = :scoreId");
    query.bindValue(":scoreId", scoreId);

    if (query.exec() && query.next()) {
        return Score(query.value("id").toInt(), query.value("matchId").toInt(), query.value("score1").toInt(), query.value("score2").toInt());
    } else {
        qDebug() << "Error getting score by ID:" << query.lastError();
        return Score();
    }
}

void ScoreUI::loadScoreDetails(const QModelIndex& index) {
    if (!index.isValid()) {
        clearScoreDetails();
        return;
    }

    int row = index.row();

    // Get the selected score from your GestionScore (or wherever you store score data)
    Score selectedScore = gestionScore->getScores(db)[row]; 

    ui->idLineEdit->setText(QString::number(selectedScore.getId()));
    // Set selected match in matchComboBox
    int matchIndex = ui->matchComboBox->findData(selectedScore.getMatchId()); 
    if (matchIndex != -1) {
        ui->matchComboBox->setCurrentIndex(matchIndex);
    }
    ui->score1SpinBox->setValue(selectedScore.getScore1());
    ui->score2SpinBox->setValue(selectedScore.getScore2());


    // ... (Set values for other score detail fields) ...
}

void ScoreUI::clearScoreDetails() {
       ui->idLineEdit->clear();
    ui->matchComboBox->setCurrentIndex(0); // Reset combo box
    ui->score1SpinBox->setValue(0);
    ui->score2SpinBox->setValue(0);

}


void ScoreUI::updateScoresList() {
    scoresModel->clear();
    scoresModel->setHorizontalHeaderLabels({"ID", "Match", "Score 1", "Score 2"});

    QList<Score> scores = gestionScore->getScores(db);

    for (const Score& score : scores) {
        int row = scoresModel->rowCount();
        scoresModel->insertRow(row);

        // Use the correct data from your Score class
        scoresModel->setData(scoresModel->index(row, 0), score.getId());
        scoresModel->setData(scoresModel->index(row, 1), gestionJoueurs->getMatchById(db, score.getMatchId()).getNom());
        scoresModel->setData(scoresModel->index(row, 2), score.getScore1());
        scoresModel->setData(scoresModel->index(row, 3), score.getScore2()); 

        // Optional: Store the score ID in the Qt::UserRole of the first column
        scoresModel->setData(scoresModel->index(row, 0), score.getId(), Qt::UserRole); 
    }
}

void ScoreUI::updateMatchComboBox() {
    ui->matchComboBox->clear();
    QList<Match> matches = gestionJoueurs->getMatches(db);
    for (const Match& match : matches) {
        QString matchDescription = QString("%1 vs %2").arg(match.getJoueur1().getNom(), match.getJoueur2().getNom());
        ui->matchComboBox->addItem(matchDescription, match.getId()); // Add match name and ID to combo box
    }
}