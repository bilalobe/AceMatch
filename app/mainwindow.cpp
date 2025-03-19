#include "mainwindow.h"
#include "data/mgmt/ClientManager.h"
#include "data/mgmt/PaymentManager.h"
#include "data/mgmt/SeatManager.h"
#include "data/mgmt/ReservationManager.h"
#include "data/mgmt/CourtManager.h"
#include "data/mgmt/TicketManager.h"
#include "qtoolbar.h"
#include "ui/headers/SettingsDialog.h"
#include "qsqlerror.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QTranslator>
#include <QInputDialog>
#include <QMap>
#include <QPair>
#include <algorithm> 

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize Database
    initializeDatabase();

    // Load Language Settings
    loadInitialLanguage();

    // Load Stylesheet
    loadStylesheet();

    // Initialize Gestion Classes
    initializeGestionClasses();

    // Create UI Components
    createUIComponents();

    // Setup Tabs
    setupTabs();

    // Setup Menu Bar
    setupMenuBar();

    // Setup Toolbar
    setupToolbar();

    // Connect Signals and Slots
    connectSignalsAndSlots();

    // Update UI Elements
    updateAllUI(); 
}

// --- Helper Functions ---

void MainWindow::initializeDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tournament.db");
    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError();
        QMessageBox::critical(this, "Database Error", "Could not connect to database.");
        return; // Or handle the error more gracefully
    }
}

void MainWindow::loadInitialLanguage() {
    QString settings;
    QString languageCode = settings.value("language", QLocale::system().name()).toString();
    loadLanguage(languageCode);
}

void MainWindow::loadStylesheet() {
    QFile styleFile(":/styles/styles.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = styleFile.readAll();
        this->setStyleSheet(styleSheet);
    } else {
        qDebug() << "Error loading stylesheet:" << styleFile.errorString();
    }
}

void MainWindow::initializeGestionClasses() {
    playerManager = new PlayerManager(db);
    matchManager = new MatchManager(db);
    clientManager = new ClientManager(db);
    seatManager = new SeatManager(db);
    reservationManager = new ReservationManager(db);
    courtManager = new CourtManager(db);
    ticketManager = new TicketManager(db);
    scoreManager = new ScoreManager(db);
    paymentManager = new PaymentManager(db);
}

void MainWindow::createUIComponents() {
    playerBox = new PlayerBox(this, db);
    matchUI = new MatchUI(this, db);
    playerProfileUI = new PlayerProfileUI(this, db);
    scoreboardMatchDetailsUI = new ScoreboardMatchDetailsUI(this, db);
    seatsUI = new PlacesUI(this, db);
    reservationsUI = new ReservationsUI(this, db);
    courtsUI = new TerrainUI(this, db);
    ticketsUI = new TicketsUI(this, db);
    scoreUI = new ScoreUI(this, db);
    clientsUI = new ClientsUI(this, db);
    seatsUI = new SeatsUI(this, db); 
}

void MainWindow::setupTabs() {
    QTabWidget *tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    addTab(tabWidget, playerBox, tr("Players"));
    addTab(tabWidget, matchUI, tr("Matches"));

    // Standings Tab
    QWidget* standingsTab = new QWidget();
    QVBoxLayout* standingsLayout = new QVBoxLayout(standingsTab);
    standingsTableView = new QTableView(standingsTab);
    standingsLayout->addWidget(standingsTableView);
    tabWidget->addTab(standingsTab, tr("Standings"));
    standingsModel = new QStandardItemModel(0, 2, standingsTab);
    standingsModel->setHeaderData(0, Qt::Horizontal, tr("Player"));
    standingsModel->setHeaderData(1, Qt::Horizontal, tr("Wins"));
    standingsTableView->setModel(standingsModel);

    addTab(tabWidget, scoreboardMatchDetailsUI, tr("Scoreboard & Match Details"));
    addTab(tabWidget, playerProfileUI, tr("Player Profile"));

    // Tournament Management Tab with Mini-Tabs
    QTabWidget *tournamentTabWidget = new QTabWidget(this);
    QWidget *tournamentTab = new QWidget();
    QVBoxLayout *tournamentLayout = new QVBoxLayout(tournamentTab);
    tournamentLayout->addWidget(tournamentTabWidget);
    tabWidget->addTab(tournamentTab, tr("Tournament Management"));

    tournamentTabWidget->addTab(clientsUI, tr("Clients"));
    tournamentTabWidget->addTab(seatsUI, tr("Places"));
    tournamentTabWidget->addTab(reservationsUI, tr("Reservations"));
    tournamentTabWidget->addTab(courtsUI, tr("Terrains"));
    tournamentTabWidget->addTab(ticketsUI, tr("Tickets"));
    tournamentTabWidget->addTab(scoreUI, tr("Scores"));
    tournamentTabWidget->addTab(seatsUI, tr("Seats"));
}

void MainWindow::setupMenuBar() {
    QMenuBar *menuBar = this->menuBar();

    // File Menu
    fileMenu = menuBar->addMenu(tr("File"));
    actionNew_Tournament = fileMenu->addAction(tr("New Tournament"));
    actionNew_Tournament->setIcon(QIcon(":/icons/tournament.svg"));
    actionSave = fileMenu->addAction(tr("Save"));
    actionSave->setIcon(QIcon(":/icons/content-save.svg"));
    actionLoad = fileMenu->addAction(tr("Load"));
    actionLoad->setIcon(QIcon(":/icons/tray-arrow-up.svg"));
    actionExport_Data = fileMenu->addAction(tr("Export Data"));
    actionExport_Data->setIcon(QIcon(":/icons/file-export.svg"));
    actionImport_Data = fileMenu->addAction(tr("Import Data"));
    actionImport_Data->setIcon(QIcon(":/icons/file-import.svg"));

    // Edit Menu 
    editMenu = menuBar->addMenu(tr("Edit")); 

    // View Menu 
    viewMenu = menuBar->addMenu(tr("View"));

    // Settings Menu 
    settingsMenu = menuBar->addMenu(tr("Settings"));
    actionSettings = settingsMenu->addAction(tr("Settings")); 
    // Add Icon: actionSettings->setIcon(QIcon(":/icons/settings.svg")); 

    // Language Menu 
    QMenu* languageMenu = menuBar->addMenu(tr("Language"));
    QAction* actionEnglish = languageMenu->addAction(tr("English"));
    QAction* actionFrench = languageMenu->addAction(tr("French"));

    // Help Menu
    helpMenu = menuBar->addMenu(tr("Help"));
    actionAbout = helpMenu->addAction(tr("About")); 
    // Add Icon: actionAbout->setIcon(QIcon(":/icons/about.svg"));
}

void MainWindow::setupToolbar() {
    QToolBar* toolbar = addToolBar(tr("Toolbar"));

    // Add New Player Action to Toolbar:
    QAction* actionNewPlayer = toolbar->addAction(QIcon(":/icons/plus.svg"), tr("New Player")); 
    connect(actionNewPlayer, &QAction::triggered, playerBox, &PlayerBox::addPlayer); 

    // Add New Match Action to Toolbar
    QAction* actionNewMatch = toolbar->addAction(QIcon(":/icons/plus.svg"), tr("New Match")); 
    connect(actionNewMatch, &QAction::triggered, matchUI, &MatchUI::createMatch); 

    // Search Bar
    QLineEdit* searchBar = new QLineEdit(this);
    toolbar->addWidget(searchBar);
    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::handleSearchTextChanged);
}

void MainWindow::connectSignalsAndSlots() {
    // File Menu Actions
    connect(actionNew_Tournament, &QAction::triggered, this, &MainWindow::handleNewTournament);
    connect(actionSave, &QAction::triggered, this, &MainWindow::handleSave);
    connect(actionLoad, &QAction::triggered, this, &MainWindow::handleLoad);
    connect(actionExport_Data, &QAction::triggered, this, &MainWindow::handleExportData);
    connect(actionImport_Data, &QAction::triggered, this, &MainWindow::handleImportData);
    connect(actionSettings, &QAction::triggered, this, &MainWindow::handleSettings); // Connect "Settings" action
    connect(actionAbout, &QAction::triggered, this, &MainWindow::handleAbout);

    // Language Actions
    connect(actionEnglish, &QAction::triggered, this, &MainWindow::changeLanguageToEnglish);
    connect(actionFrench, &QAction::triggered, this, &MainWindow::changeLanguageToFrench);

    // UI Component Signals
    connect(playerBox, &PlayerBox::playerAdded, this, &MainWindow::handlePlayerAdded);
    connect(playerBox, &PlayerBox::playerRemoved, this, &MainWindow::handlePlayerRemoved);
    connect(playerBox, &PlayerBox::playerUpdated, this, &MainWindow::handlePlayerUpdated);
    connect(playerBox, &PlayerBox::playerSearched, this, &MainWindow::handlePlayerSearched);

    connect(matchUI, &MatchUI::matchCreated, this, &MainWindow::handleMatchCreated);
    connect(matchUI, &MatchUI::matchDeleted, this, &MainWindow::handleMatchDeleted);
    connect(matchUI, &MatchUI::matchUpdated, this, &MainWindow::handleMatchUpdated);

    connect(playerProfileUI, &PlayerProfileUI::playerProfileUpdated, this, &MainWindow::handlePlayerProfileUpdated);

    connect(seatsUI, &PlacesUI::placeAdded, this, &MainWindow::handlePlaceAdded);
    connect(placesUI, &PlacesUI::placeDeleted, this, &MainWindow::handlePlaceDeleted);
    connect(placesUI, &PlacesUI::placeUpdated, this, &MainWindow::handlePlaceUpdated);

    connect(reservationsUI, &ReservationsUI::reservationAdded, this, &MainWindow::handleReservationAdded);
    connect(reservationsUI, &ReservationsUI::reservationDeleted, this, &MainWindow::handleReservationDeleted);
    connect(reservationsUI, &ReservationsUI::reservationUpdated, this, &MainWindow::handleReservationUpdated);

    connect(courtsUI, &TerrainUI::terrainAdded, this, &MainWindow::handleTerrainAdded);
    connect(terrainsUI, &TerrainUI::terrainDeleted, this, &MainWindow::handleTerrainDeleted);
    connect(terrainsUI, &TerrainUI::terrainUpdated, this, &MainWindow::handleTerrainUpdated);

    connect(ticketsUI, &TicketsUI::ticketAdded, this, &MainWindow::handleTicketAdded);
    connect(ticketsUI, &TicketsUI::ticketDeleted, this, &MainWindow::handleTicketDeleted);
    connect(ticketsUI, &TicketsUI::ticketUpdated, this, &MainWindow::handleTicketUpdated);

    connect(scoreUI, &ScoreUI::scoreAdded, this, &MainWindow::handleScoreAdded);
    connect(scoreUI, &ScoreUI::scoreDeleted, this, &MainWindow::handleScoreDeleted);
    connect(scoreUI, &ScoreUI::scoreUpdated, this, &MainWindow::handleScoreUpdated);

    connect(scoreboardMatchDetailsUI, &ScoreboardMatchDetailsUI::matchSelected, this, &MainWindow::handleMatchSelected);

    connect(clientsUI, &ClientsUI::clientAdded, this, &MainWindow::handleClientAdded);
    connect(clientsUI, &ClientsUI::clientDeleted, this, &MainWindow::handleClientDeleted);
    connect(clientsUI, &ClientsUI::clientUpdated, this, &MainWindow::handleClientUpdated);

    connect(seatsUI, &SeatsUI::seatSelected, this, &MainWindow::handleSeatSelected);
    connect(seatsUI, &SeatsUI::seatStatusChanged, this, &MainWindow::handleSeatStatusChanged);
}

void MainWindow::addTab(QTabWidget* tabWidget, QWidget* widget, const QString& label) {
    QWidget* newTab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(newTab);
    layout->addWidget(widget);
    tabWidget->addTab(newTab, label);
}

// ... (Implement all the handle* slots, updateStandings, updateAllUI, and other methods as needed) ...

// Destructor for MainWindow
MainWindow::~MainWindow()
{
    delete ui;

    // Delete Gestion* objects
    delete playerManager;
    delete seatManager;
    delete reservationManager;
    delete courtManager;
    delete ticketManager;
    delete scoreManager;
    delete clientManager;
    delete paymentManager;

    // Delete UI components
    delete playerBox;
    delete matchUI;
    delete playerProfileUI;
    delete scoreboardMatchDetailsUI;
    delete placesUI;
    delete reservationsUI;
    delete terrainsUI;
    delete ticketsUI;
    delete scoreUI;

    // Close database connection
    if (db.isOpen())
    {
        db.close();
    }
}

// Menu Bar Slots

void MainWindow::handleNewTournament() {
    // Clear the database tables for a new tournament
    QSqlQuery query(db);
    QStringList tables = db.tables();

    // Start a transaction to ensure all operations are executed or none are.
    db.transaction();

    for (const QString &table : tables) {
        if (!query.exec(QString("DELETE FROM %1").arg(table))) {
            qDebug() << "Error deleting data from" << table << ":" << query.lastError().text();
            db.rollback(); // Roll back the transaction if any error occurs.
            QMessageBox::warning(this, tr("Error"), tr("Failed to create new tournament. Could not clear database."));
            return; 
        }

        // Reset the auto-increment counter for each table
        if (!query.exec(QString("DELETE FROM sqlite_sequence WHERE name='%1'").arg(table))) {
            qDebug() << "Error resetting auto-increment for" << table << ":" << query.lastError().text();
            db.rollback();
            QMessageBox::warning(this, tr("Error"), tr("Failed to create new tournament. Could not reset auto-increment."));
            return; 
        }
    }

    db.commit(); // Commit the changes if all operations were successful.

    // Clear UI elements
    updateAllUI();

    // Optionally, you can also ask for the tournament name
    bool ok;
    QString tournamentName = QInputDialog::getText(this, tr("New Tournament"), tr("Enter Tournament Name:"), QLineEdit::Normal, "", &ok);


    if (ok && !tournamentName.isEmpty()) {
        // You can save the tournament name or use it in your UI

        ui->setWindowTitle(QString("Tournament Manager - %1").arg(tournamentName)); 
    }

    statusBar()->showMessage(tr("New tournament created."));
}

void MainWindow::updateAllUI() {
    playerBox->updatePlayerList();
    matchUI->updateMatchList();
    matchUI->updatePlayerComboBoxes();
    playerProfileUI->updatePlayerComboBox();
    scoreboardMatchDetailsUI->updateMatchComboBox();
    seatsUI->updatePlacesList();
    reservationsUI->updateReservationsList();
    reservationsUI->updateClientComboBox();
    reservationsUI->updatePlaceComboBox();
    courtsUI->updateTerrainsList();
    ticketsUI->updateTicketsList();
    ticketsUI->updateClientComboBox();
    ticketsUI->updateMatchComboBox();
    ticketsUI->updatePlaceComboBox();
    scoreUI->updateScoresList();
    scoreUI->updateMatchComboBox();
    clientsUI->updateClientsList();
    seatsUI->updateSeatsTable();
    updateStandings();
}

void MainWindow::handleSave()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Tournament"), "", tr("Database Files (*.db)"));
    if (!fileName.isEmpty())
    {
        if (backupDatabase("tournament.db", fileName))
        {
            QMessageBox::information(this, tr("Success"), tr("Tournament saved successfully."));
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Failed to save tournament."));
        }
    }
}

void MainWindow::handleLoad()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Tournament"), "", tr("Database Files (*.db)"));
    if (!fileName.isEmpty())
    {
        if (restoreDatabase(fileName, "tournament.db"))
        {
            QMessageBox::information(this, tr("Success"), tr("Tournament loaded successfully."));
            updateAllUI();
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Failed to load tournament."));
        }
    }
}

void MainWindow::changeLanguageToEnglish()
{
    loadLanguage("en");
}

void MainWindow::changeLanguageToFrench()
{
    loadLanguage("fr");
}

void MainWindow::changeLanguageToSpanish()
{
    loadLanguage("es");
}

void MainWindow::changeLanguageToGerman()
{
    loadLanguage("de");
}


void MainWindow::loadLanguage(const QString &languageCode)
{
    QTranslator translator;
    if (translator.load(QString(":/translations/app_%1.qm").arg(languageCode)))
    {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this); // Retranslate UI elements

        // Update UI elements that need to be refreshed
    }
    else
    {
        qDebug() << "Error loading translation file for:" << languageCode;
    }
}

// Lang
// Other Slots and Utility functions remain unchanged...

// Utility functions for database backup and restore
bool MainWindow::backupDatabase(const QString &sourceFile, const QString &destinationFile)
{
    QFile source(sourceFile);
    if (source.exists())
    {
        return source.copy(destinationFile);
    }
    return false;
}

bool MainWindow::restoreDatabase(const QString &backupFile, const QString &destinationFile)
{
    QFile backup(backupFile);
    if (backup.exists())
    {
        QFile::remove(destinationFile); // Remove existing database file
        return backup.copy(destinationFile);
    }
    return false;
}
// Other Slots

void MainWindow::handleSearchTextChanged(const QString &searchTerm)
{
    playerBox->searchPlayer(searchTerm);
    matchUI->searchMatch(searchTerm);
    seatsUI->searchPlace(searchTerm);
    playerProfileUI->searchPlayerProfile(searchTerm);
    reservationsUI->searchReservations(searchTerm);
    courtsUI->searchTerrains(searchTerm);
    ticketsUI->searchTickets(searchTerm);
    scoreUI->searchScores(searchTerm);

    // Implement filtering for the standings table
}

void MainWindow::handleMatchSelected(int matchId)
{
    Match match = matchManager->getMatch(db, matchId);
    // Update other UI elements based on the selected match, like "Match Details" in another tab
    matchUI->displayMatchDetails(match);
    seatsUI->displayAvailablePlaces(match);
    playerProfileUI->displayPlayerProfile(match.getPlayer1());
    playerProfileUI->displayPlayerProfile(match.getPlayer2());
    ticketsUI->displayTickets(match);
    scoreUI->displayScore(match);
}

void MainWindow::updateStandings()
{
    QList<Player> players = playerManager->getPlayers(db);
    QMap<QString, int> playerWins;

    // Calculate wins from match data
    QList<Match> matches = matchManager->getMatches(db);
    for (const Match &match : matches)
    {
        if (match.getScore1() > match.getScore2())
        {
            playerWins[match.getPlayer1().getName()]++;
        }
        else if (match.getScore2() > match.getScore1())
        {
            playerWins[match.getPlayer2().getName()]++;
        }
        else
        {
            // Tie:  award 0.5 points to both players
            playerWins[match.getPlayer1().getName()] += 0.5;
            playerWins[match.getPlayer2().getName()] += 0.5;
        }
    }

    // Sort players by wins, handle ties alphabetically
    QList<QPair<QString, int>> sortedPlayers;
    for (const QString &playerName : playerWins.keys())
    {
        sortedPlayers.append(qMakePair(playerName, playerWins[playerName]));
    }
    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
              [](const QPair<QString, int> &a, const QPair<QString, int> &b)
              {
                  if (a.second != b.second)
                  {
                      return a.second > b.second;
                  }
                  else
                  {
                      return a.first < b.first;
                  }
              });

    // Update the standings table view model
    standingsModel->removeRows(0, standingsModel->rowCount()); // Clear existing rows
    for (int i = 0; i < sortedPlayers.size(); ++i)
    {
        standingsModel->insertRow(i);
        standingsModel->setData(standingsModel->index(i, 0), sortedPlayers[i].first);
        standingsModel->setData(standingsModel->index(i, 1), sortedPlayers[i].second);
    }
}

// Implement logic for each of the following stub slots

void MainWindow::handlePlayerAdded(const QString &name, int ranking)
{
    if (playerManager->addJoueur(db, name, ranking))
    {
        playerBox->updatePlayerList();
        playerProfileUI->updatePlayerComboBox();
        matchUI->updatePlayerComboBoxes();
        statusBar()->showMessage("Player added successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to add player.");
    }
}

void MainWindow::handlePlayerRemoved(const QString &name)
{
    if (playerManager->removeJoueur(db, name))
    {
        playerBox->updatePlayerList();
        playerProfileUI->updatePlayerComboBox();
        matchUI->updatePlayerComboBoxes();
        statusBar()->showMessage("Player removed successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to remove player.");
    }
}

void MainWindow::handlePlayerUpdated(const QString &name, int newRanking)
{
    if (playerManager->updateJoueur(db, name, newRanking))
    {
        playerBox->updatePlayerList();
        playerProfileUI->updatePlayerComboBox();
        matchUI->updatePlayerComboBoxes();
        statusBar()->showMessage("Player updated successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to update player.");
    }
}

void MainWindow::handlePlayerSearched(const QString &searchTerm)
{
    playerBox->searchPlayer(searchTerm);
}

void MainWindow::handleMatchCreated(const QString &player1Name, const QString &player2Name, int score1, int score2)
{
    if (matchManager->createMatch(db, player1Name, player2Name, score1, score2))
    {
        matchUI->updateMatchList();
        updateStandings(); // Update standings if needed
        statusBar()->showMessage("Match created successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to create match.");
    }
}

void MainWindow::handleMatchDeleted(int matchId)
{
    if (matchManager->removeMatch(db, matchId))
    {
        matchUI->updateMatchList();
        updateStandings(); // Update standings if needed
        statusBar()->showMessage("Match deleted successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to delete match.");
    }
}

void MainWindow::handleMatchUpdated(int matchId, int newScore1, int newScore2)
{
    if (matchManager->updateMatch(db, matchId, newScore1, newScore2))
    {
        matchUI->updateMatchList();
        updateStandings(); // Update standings if needed
        statusBar()->showMessage("Match updated successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to update match.");
    }
}

void MainWindow::handlePlayerProfileUpdated(const QString &playerName, int newRanking)
{
    if (playerManager->updateJoueur(db, playerName, newRanking))
    {
        playerBox->updatePlayerList();           // Update player list
        playerProfileUI->updatePlayerComboBox(); // Update player profile combo box
        matchUI->updatePlayerComboBoxes();       // Update player combo boxes
        statusBar()->showMessage("Player profile updated successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to update player profile.");
    }
}

void MainWindow::handlePlaceAdded(const QString &name, int capacity)
{
    if (seatManager->addPlace(db, name, capacity))
    {
        seatsUI->updatePlacesList();
        statusBar()->showMessage("Seat added successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to add seat.");
    }
}

void MainWindow::handlePlaceDeleted(int seatId)
{
    if (seatManager->removePlace(db, seatId))
    {
        placesUI->updatePlacesList();
        statusBar()->showMessage("Seat deleted successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to delete seat.");
    }
}

void MainWindow::handlePlaceUpdated(int seatId, const QString &newName, int newCapacity)
{
    if (seatManager->updatePlace(db, seatId, newName, newCapacity))
    {
        placesUI->updatePlacesList();
        statusBar()->showMessage("Seat updated successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to update seat.");
    }
}

void MainWindow::handleReservationAdded(int clientId, int seatId, const QDateTime &dateTime)
{
    if (reservationManager->addReservation(db, clientId, seatId, dateTime))
    {
        reservationsUI->updateReservationsList();
        statusBar()->showMessage("Reservation added successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to add reservation.");
    }
}

void MainWindow::handleReservationDeleted(int reservationId)
{
    if (reservationManager->removeReservation(db, reservationId))
    {
        reservationsUI->updateReservationsList();
        statusBar()->showMessage("Reservation deleted successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to delete reservation.");
    }
}

void MainWindow::handleReservationUpdated(int reservationId, int newClientId, int newPlaceId, const QDateTime &newDateTime)
{
    if (reservationManager->updateReservation(db, reservationId, newClientId, newPlaceId, newDateTime))
    {
        reservationsUI->updateReservationsList();
        statusBar()->showMessage("Reservation updated successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to update reservation.");
    }
}

void MainWindow::handleTerrainAdded(const QString &name, const QString &type)
{
    if (courtManager->addTerrain(db, name, type))
    {
        courtsUI->updateTerrainsList();
        statusBar()->showMessage("Court added successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to add court.");
    }
}

void MainWindow::handleTerrainDeleted(int terrainId)
{
    if (courtManager->removeTerrain(db, terrainId))
    {
        terrainsUI->updateTerrainsList();
        statusBar()->showMessage("Court deleted successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to delete court.");
    }
}

void MainWindow::handleTerrainUpdated(int terrainId, const QString &newName, const QString &newType)
{
    if (courtManager->updateTerrain(db, terrainId, newName, newType))
    {
        terrainsUI->updateTerrainsList();
        statusBar()->showMessage("Court updated successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to update court.");
    }
}

void MainWindow::handleTicketAdded(int clientId, int matchId, int seatId, double price, const QString &status)
{
    if (ticketManager->addTicket(db, clientId, matchId, seatId, price, status))
    {
        ticketsUI->updateTicketsList();
        statusBar()->showMessage("Ticket added successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to add ticket.");
    }
}

void MainWindow::handleTicketDeleted(int ticketId)
{
    if (ticketManager->removeTicket(db, ticketId))
    {
        ticketsUI->updateTicketsList();
        statusBar()->showMessage("Ticket deleted successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to delete ticket.");
    }
}

void MainWindow::handleTicketUpdated(int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString &newStatus)
{
    if (ticketManager->updateTicket(db, ticketId, newClientId, newMatchId, newPlaceId, newPrice, newStatus))
    {
        ticketsUI->updateTicketsList();
        statusBar()->showMessage("Ticket updated successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to update ticket.");
    }
}

void MainWindow::handleScoreAdded(int matchId, int score1, int score2)
{
    if (scoreManager->addScore(db, matchId, score1, score2))
    {
        scoreUI->updateScoresList();
        statusBar()->showMessage("Score added successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to add score.");
    }
}

void MainWindow::handleScoreDeleted(int scoreId)
{
    if (scoreManager->removeScore(db, scoreId))
    {
        scoreUI->updateScoresList();
        statusBar()->showMessage("Score deleted successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to delete score.");
    }
}

void MainWindow::handleScoreUpdated(int scoreId, int newScore1, int newScore2)
{
    if (scoreManager->updateScore(db, scoreId, newScore1, newScore2))
    {
        scoreUI->updateScoresList();
        statusBar()->showMessage("Score updated successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to update score.");
    }
}

void MainWindow::handleClientAdded(const QString &name, const QString &email, const QString &phoneNumber)
{
    if (clientManager->addClient(db, name, email, phoneNumber))
    {
        clientsUI->updateClientsList();
        statusBar()->showMessage(tr("Client added successfully."));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Failed to add client."));
    }
}

void MainWindow::handleClientDeleted(int clientId)
{
    if (clientManager->removeClient(db, clientId))
    {
        clientsUI->updateClientsList();
        statusBar()->showMessage(tr("Client deleted successfully."));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Failed to delete client."));
    }
}

void MainWindow::handleClientUpdated(int clientId, const QString &newName, const QString &newEmail, const QString &newPhoneNumber)
{
    if (clientManager->updateClient(db, clientId, newName, newEmail, newPhoneNumber))
    {
        clientsUI->updateClientsList();
        statusBar()->showMessage(tr("Client updated successfully."));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Failed to update client."));
    }
}

void MainWindow::handleSeatSelected(int seatId)
{
    // Update other UI elements based on the selected seat
}

void MainWindow::handleSeatStatusChanged(int seatId, bool isAvailable)
{
    if (gestionSeats->updateSeatStatus(db, seatId, isAvailable))
    {
        seatsUI->updateSeatsTable();
        statusBar()->showMessage(tr("Seat status updated."));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Failed to update seat status."));
    }
}

// Update Functions

void MainWindow::updatePlayerBox()
{
    playerBox->updatePlayerList();
}

void MainWindow::updateMatchUI()
{
    matchUI->updateMatchList();
    matchUI->updatePlayerComboBoxes();
}

void MainWindow::updatePlayerProfileUI()
{
    playerProfileUI->updatePlayerComboBox();
}

void MainWindow::updateScoreboardMatchDetailsUI()
{
    scoreboardMatchDetailsUI->updateMatchComboBox();
}

void MainWindow::updatePlacesUI()
{
    seatsUI->updatePlacesList();
}

void MainWindow::updateReservationsUI()
{
    reservationsUI->updateReservationsList();
    reservationsUI->updateClientComboBox();
    reservationsUI->updatePlaceComboBox();
}

void MainWindow::updateTerrainsUI()
{
    courtsUI->updateTerrainsList();
}

void MainWindow::updateTicketsUI()
{
    ticketsUI->updateTicketsList();
    ticketsUI->updateClientComboBox();
    ticketsUI->updateMatchComboBox();
    ticketsUI->updatePlaceComboBox();
}

void MainWindow::updateScoreUI()
{
    scoreUI->updateScoresList();
    scoreUI->updateMatchComboBox();
}

void MainWindow::updateClientsUI()
{
    clientsUI->updateClientsList();
}

void MainWindow::updateSeatsUI()
{
    seatsUI->updateSeatsTable();
}

void MainWindow::handleExportData()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Data"), "", tr("CSV Files (*.csv)"));
    if (!fileName.isEmpty())
    {
        if (exportDatabaseToCSV(fileName))
        {
            QMessageBox::information(this, tr("Success"), tr("Data exported successfully."));
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Failed to export data."));
        }
    }
}

void MainWindow::handleImportData()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import Data"), "", tr("CSV Files (*.csv)"));
    if (!fileName.isEmpty())
    {
        if (importDataFromCSV(fileName))
        {
            QMessageBox::information(this, tr("Success"), tr("Data imported successfully."));
            updateAllUI();
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Failed to import data."));
        }
    }
}


void MainWindow::handleAbout()
{
    QMessageBox::about(this, tr("About Tournament Manager"),
                       tr("This application is designed for managing tennis tournaments."));
}

  
void MainWindow::handleSettings()  
{  
    SettingsDialog settingsDialog(this);  
    if (settingsDialog.exec() == QDialog::Accepted)  
    {  
        QString selectedLanguage = settingsDialog.getSelectedLanguage();  
        loadLanguage(selectedLanguage);  
    }  
}  
  
  
// Utility functions for database backup and restore  
bool MainWindow::backupDatabase(const QString &sourceFile, const QString &destinationFile)  
{  
    QFile source(sourceFile);  
    if (source.exists())  
    {  
        return source.copy(destinationFile);  
    }  
    return false;  
}  
  
bool MainWindow::restoreDatabase(const QString &backupFile, const QString &destinationFile)  
{  
    QFile backup(backupFile);  
    if (backup.exists())  
    {  
        QFile::remove(destinationFile); // Remove the existing database file  
        return backup.copy(destinationFile);  
    }  
    return false;  
}  

// Utility functions for exporting/importing data
bool MainWindow::exportDatabaseToCSV(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    // Export Players
    QSqlQuery query("SELECT * FROM Joueurs");
    out << "Joueurs\n";
    while (query.next())
    {
        out << query.value(0).toString() << ","
            << query.value(1).toString() << ","
            << query.value(2).toString() << "\n";
    }

    // Export other tables similarly...

    file.close();
    return true;
}

bool MainWindow::importDataFromCSV(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);        // Import Players
    QString line = in.readLine(); // Skip header line
    while (!in.atEnd())
    {
        line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() == 3)
        {
            playerManager->addJoueur(db, fields[0], fields[1].toInt());
        }
    }

    // Import other tables similarly...

    file.close();
    return true;
}

