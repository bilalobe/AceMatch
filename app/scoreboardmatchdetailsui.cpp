#include "scoreboardmatchdetailsui.h"
#include "ui_scoreboardmatchdetailsui.h"
#include <QMessageBox>

ScoreboardMatchDetailsUI::ScoreboardMatchDetailsUI(QWidget *parent, const QSqlDatabase& database)
    : QWidget(parent), ui(new Ui::ScoreboardMatchDetailsUI), db(database)
{
    ui->setupUi(this);

    // Get access to GestionJoueurs
    gestionJoueurs = dynamic_cast<MainWindow*>(parent)->getGestionJoueurs();
    if (!gestionJoueurs) {
        qDebug() << "Error: Could not access GestionJoueurs.";
        return;
    }

    // Create Scoreboard instance
    scoreboard = new Scoreboard(this);
    ui->scoreboardLayout->addWidget(scoreboard); // Assuming "scoreboardLayout" is the name of the layout on the left side

    // Populate Match Combo Box
    updateMatchComboBox();

    // Connect signals and slots:
    connect(ui->matchComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ScoreboardMatchDetailsUI::loadMatchDetails);
}

ScoreboardMatchDetailsUI::~ScoreboardMatchDetailsUI()
{
    delete ui;
}

void ScoreboardMatchDetailsUI::updateMatchComboBox() {
    ui->matchComboBox->clear();
    QList<Match> matches = gestionJoueurs->getMatches(db);
    for (const Match& match : matches) {
        QString matchDescription = QString("%1 vs %2").arg(match.getJoueur1().getNom(), match.getJoueur2().getNom());
        ui->matchComboBox->addItem(matchDescription, match.getId()); // Store the match ID as user data
    }
}

void ScoreboardMatchDetailsUI::loadMatchDetails() {
    int matchId = ui->matchComboBox->currentData().toInt(); 
    Match match = gestionJoueurs->getMatchById(db, matchId); 

    if (match.getId() != -1) { // Assuming -1 means the match was not found
        displayMatchDetails(match);
        emit matchSelected(matchId);
    } else {
        clearMatchDetails();
        QMessageBox::warning(this, "Error", "Match not found.");
    }
}

void ScoreboardMatchDetailsUI::displayMatchDetails(const Match& match) {
    ui->player1NameLabel->setText(match.getJoueur1().getNom());
    ui->player2NameLabel->setText(match.getJoueur2().getNom());
    ui->player1ScoreLabel->setText(QString::number(match.getScore1()));
    ui->player2ScoreLabel->setText(QString::number(match.getScore2()));

    // Update scoreboard
    scoreboard->setPlayer1Name(match.getJoueur1().getNom());
    scoreboard->setPlayer2Name(match.getJoueur2().getNom());
    scoreboard->setScore1(match.getScore1());
    scoreboard->setScore2(match.getScore2());

    // ... (Set values for other match details fields) ...
}

void ScoreboardMatchDetailsUI::clearMatchDetails() {
    ui->player1NameLabel->clear();
    ui->player2NameLabel->clear();
    ui->player1ScoreLabel->clear();
    ui->player2ScoreLabel->clear();

    // Clear scoreboard
    scoreboard->clear();

    // ... (Clear other match details fields) ...
}