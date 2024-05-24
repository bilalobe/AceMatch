#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QMap>
#include <QPair>
#include <algorithm> // for std::sort

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Database Connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tournament.db"); // Use your database name
    if (!db.open()) {
        qDebug() << "Error opening database:" << db.lastError();
        QMessageBox::critical(this, "Database Error", "Could not connect to database.");
        return;
    }

    // Initialize Gestion* Classes
    gestionJoueurs = new GestionJoueurs(db);
    gestionPlaces = new GestionPlaces(db);
    gestionReservations = new GestionReservations(db);
    gestionTerrains = new GestionTerrains(db);
    gestionTickets = new GestionTickets(db);

    // Create UI Components
    playerBox = new PlayerBox(this, db);
    matchUI = new MatchUI(this, db);
    playerProfileUI = new PlayerProfileUI(this, db);
    scoreboardMatchDetailsUI = new ScoreboardMatchDetailsUI(this, db);
    placesUI = new PlacesUI(this, db);
    reservationsUI = new ReservationsUI(this, db);
    terrainsUI = new TerrainsUI(this, db);
    ticketsUI = new TicketsUI(this, db);

    // Create Main Tab Widget
    QTabWidget* tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    // Players Tab
    QWidget* playersTab = new QWidget();
    QVBoxLayout* playersLayout = new QVBoxLayout(playersTab);
    playersLayout->addWidget(playerBox);
    tabWidget->addTab(playersTab, "Players");

    // Matches Tab
    QWidget* matchesTab = new QWidget();
    QVBoxLayout* matchesLayout = new QVBoxLayout(matchesTab);
    matchesLayout->addWidget(matchUI);
    tabWidget->addTab(matchesTab, "Matches");

    // Standings Tab 
    QWidget* standingsTab = new QWidget();
    QVBoxLayout* standingsLayout = new QVBoxLayout(standingsTab);
    standingsTableView = new QTableView(standingsTab);
    standingsLayout->addWidget(standingsTableView);
    tabWidget->addTab(standingsTab, "Standings");

    // Create a model for standings data (you'll populate this later)
    standingsModel = new QStandardItemModel(0, 2, standingsTab); // 0 rows, 2 columns
    standingsModel->setHeaderData(0, Qt::Horizontal, tr("Player"));
    standingsModel->setHeaderData(1, Qt::Horizontal, tr("Wins")); // Or other relevant data
    standingsTableView->setModel(standingsModel);

    // Scoreboard & Match Details Tab
    QWidget* detailsTab = new QWidget();
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsTab);
    detailsLayout->addWidget(scoreboardMatchDetailsUI);
    tabWidget->addTab(detailsTab, "Scoreboard & Match Details");

    // Player Profile Tab
    QWidget* profileTab = new QWidget();
    QVBoxLayout* profileLayout = new QVBoxLayout(profileTab);
    profileLayout->addWidget(playerProfileUI);
    tabWidget->addTab(profileTab, "Player Profile");

    // Tournament Management Tab with Mini-Tabs
    QTabWidget* tournamentTabWidget = new QTabWidget(this);
    QWidget* tournamentTab = new QWidget();
    QVBoxLayout* tournamentLayout = new QVBoxLayout(tournamentTab);
    tournamentLayout->addWidget(tournamentTabWidget);
    tabWidget->addTab(tournamentTab, "Tournament Management");

    // Places Mini-Tab
    tournamentTabWidget->addTab(placesUI, "Places");

    // Reservations Mini-Tab
    tournamentTabWidget->addTab(reservationsUI, "Reservations");

    // Terrains Mini-Tab
    tournamentTabWidget->addTab(terrainsUI, "Terrains");

    // Tickets Mini-Tab
    tournamentTabWidget->addTab(ticketsUI, "Tickets");

    // Set tabWidget as the central widget
    setCentralWidget(tabWidget);

    // Status Bar
    statusBar()->showMessage("Ready");

    // Connect Search Bar to MainWindow
    QLineEdit *searchBar = new QLineEdit(this);
    toolbar->addWidget(searchBar);
    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::handleSearchTextChanged);

    // Connect Signals and Slots
    connect(playerBox, &PlayerBox::playerAdded, this, &MainWindow::handlePlayerAdded);
    connect(playerBox, &PlayerBox::playerRemoved, this, &MainWindow::handlePlayerRemoved);
    connect(playerBox, &PlayerBox::playerUpdated, this, &MainWindow::handlePlayerUpdated);
    connect(playerBox, &PlayerBox::playerSearched, this, &MainWindow::handlePlayerSearched);

    connect(matchUI, &MatchUI::matchCreated, this, &MainWindow::handleMatchCreated);
    connect(matchUI, &MatchUI::matchDeleted, this, &MainWindow::handleMatchDeleted);
    connect(matchUI, &MatchUI::matchUpdated, this, &MainWindow::handleMatchUpdated);

    connect(playerProfileUI, &PlayerProfileUI::playerProfileUpdated, this, &MainWindow::handlePlayerProfileUpdated);

    connect(placesUI, &PlacesUI::placeAdded, this, &MainWindow::handlePlaceAdded);
    connect(placesUI, &PlacesUI::placeDeleted, this, &MainWindow::handlePlaceDeleted);
    connect(placesUI, &PlacesUI::placeUpdated, this, &MainWindow::handlePlaceUpdated);

    connect(reservationsUI, &ReservationsUI::reservationAdded, this, &MainWindow::handleReservationAdded);
    connect(reservationsUI, &ReservationsUI::reservationDeleted, this, &MainWindow::handleReservationDeleted);
    connect(reservationsUI, &ReservationsUI::reservationUpdated, this, &MainWindow::handleReservationUpdated);

    connect(terrainsUI, &TerrainsUI::terrainAdded, this, &MainWindow::handleTerrainAdded);
    connect(terrainsUI, &TerrainsUI::terrainDeleted, this, &MainWindow::handleTerrainDeleted);
    connect(terrainsUI, &TerrainsUI::terrainUpdated, this, &MainWindow::handleTerrainUpdated);

    connect(ticketsUI, &TicketsUI::ticketAdded, this, &MainWindow::handleTicketAdded);
    connect(ticketsUI, &TicketsUI::ticketDeleted, this, &MainWindow::handleTicketDeleted);
    connect(ticketsUI, &TicketsUI::ticketUpdated, this, &MainWindow::handleTicketUpdated);

    // Update UI Elements
    updateStandings();
    // ... (Update other UI elements like player lists, combo boxes, etc.) ...
}

MainWindow::~MainWindow()
{
    delete ui;

    // Delete Gestion* objects
    delete gestionJoueurs;
    delete gestionPlaces;
    delete gestionReservations;
    delete gestionTerrains;
    delete gestionTickets;

    // Delete UI components
    delete playerBox;
    delete matchUI;
    delete playerProfileUI;
    delete scoreboardMatchDetailsUI;
    delete placesUI;
    delete reservationsUI;
    delete terrainsUI;
    delete ticketsUI;

    // Close database connection
    if (db.isOpen()) {
        db.close();
    }
}

// ... (Implementation of slots: handleMatchCreated, handleMatchDeleted, 
//      handleMatchUpdated, handlePlayerProfileUpdated, handlePlaceAdded, 
//      handlePlaceDeleted, handlePlaceUpdated, and other slots as needed) ...

void MainWindow::handlePlayerAdded(const QString& name, int ranking) {
    if (gestionJoueurs->ajouterJoueur(db, name, ranking)) {
        // Update UI 
        playerBox->updatePlayerList(); 
        playerProfileUI->updatePlayerComboBox();
        matchUI->updatePlayerComboBoxes(); 
        statusBar()->showMessage("Player added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add player.");
    }
}

void MainWindow::handlePlayerRemoved(const QString& nom) {
    if (gestionJoueurs->supprimerJoueur(db, nom)) {
        // Update UI
        playerBox->updatePlayerList();
        playerProfileUI->updatePlayerComboBox();
        matchUI->updatePlayerComboBoxes(); 
        statusBar()->showMessage("Player removed successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to remove player.");
    }
}

void MainWindow::handlePlayerUpdated(const QString& nom, int newRanking) {
    if (gestionJoueurs->modifierJoueur(db, nom, newRanking)) {
        // Update UI
        playerBox->updatePlayerList();
        playerProfileUI->updatePlayerComboBox();
        matchUI->updatePlayerComboBoxes(); 
        statusBar()->showMessage("Player updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update player.");
    }
}

void MainWindow::handleMatchCreated(const QString& player1Name, const QString& player2Name, int score1, int score2) {
    if (gestionJoueurs->creerMatch(db, player1Name, player2Name, score1, score2)) {
        matchUI->updateMatchList();
        updateStandings(); // Update standings if needed
        statusBar()->showMessage("Match created successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to create match.");
    }
}

void MainWindow::handleMatchDeleted(int matchId) {
    if (gestionJoueurs->supprimerMatch(db, matchId)) {
        matchUI->updateMatchList();
        updateStandings(); // Update standings if needed
        statusBar()->showMessage("Match deleted successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete match.");
    }
}

void MainWindow::handleMatchUpdated(int matchId, int newScore1, int newScore2) {
    if (gestionJoueurs->modifierMatch(db, matchId, newScore1, newScore2)) {
        matchUI->updateMatchList();
        updateStandings(); // Update standings if needed
        statusBar()->showMessage("Match updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update match.");
    }
}

void MainWindow::handlePlayerProfileUpdated(const QString& playerName, int newRanking) {
    if (gestionJoueurs->modifierJoueur(db, playerName, newRanking)) {
        playerBox->updatePlayerList(); // Update player list
        matchUI->updatePlayerComboBoxes(); // Update player combo boxes
        playerProfileUI->updatePlayerComboBox(); // Update player profile combo box
        statusBar()->showMessage("Player profile updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update player profile.");
    }
}

void MainWindow::handlePlaceAdded(const QString& name, int capacity) {
    if (gestionPlaces->ajouterPlace(db, name, capacity)) {
        placesUI->updatePlacesList();
        statusBar()->showMessage("Place added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add place.");
    }
}

void MainWindow::handlePlaceDeleted(int placeId) {
    if (gestionPlaces->supprimerPlace(db, placeId)) {
        placesUI->updatePlacesList();
        statusBar()->showMessage("Place deleted successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete place.");
    }
}

void MainWindow::handlePlaceUpdated(int placeId, const QString& newName, int newCapacity) {
    if (gestionPlaces->modifierPlace(db, placeId, newName, newCapacity)) {
        placesUI->updatePlacesList();
        statusBar()->showMessage("Place updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update place.");
    }
}

void MainWindow::handleReservationAdded(int clientId, int placeId, const QDateTime& dateTime) {
    if (gestionReservations->ajouterReservation(db, clientId, placeId, dateTime)) {
        reservationsUI->updateReservationsList();
        statusBar()->showMessage("Reservation added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add reservation.");
    }
}

void MainWindow::handleReservationDeleted(int reservationId) {
    if (gestionReservations->supprimerReservation(db, reservationId)) {
        reservationsUI->updateReservationsList();
        statusBar()->showMessage("Reservation deleted successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete reservation.");
    }
}

void MainWindow::handleReservationUpdated(int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime) {
    if (gestionReservations->modifierReservation(db, reservationId, newClientId, newPlaceId, newDateTime)) {
        reservationsUI->updateReservationsList();
        statusBar()->showMessage("Reservation updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update reservation.");
    }
}

void MainWindow::handleTerrainAdded(const QString& name, const QString& type) {
    if (gestionTerrains->ajouterTerrain(db, name, type)) {
        terrainsUI->updateTerrainsList();
        statusBar()->showMessage("Terrain added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add terrain.");
    }
}

void MainWindow::handleTerrainDeleted(int terrainId) {
    if (gestionTerrains->supprimerTerrain(db, terrainId)) {
        terrainsUI->updateTerrainsList();
        statusBar()->showMessage("Terrain deleted successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete terrain.");
    }
}

void MainWindow::handleTerrainUpdated(int terrainId, const QString& newName, const QString& newType) {
    if (gestionTerrains->modifierTerrain(db, terrainId, newName, newType)) {
        terrainsUI->updateTerrainsList();
        statusBar()->showMessage("Terrain updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update terrain.");
    }
}

void MainWindow::handleTicketAdded(int clientId, int matchId, int placeId, double price, const QString& status) {
    if (gestionTickets->ajouterTicket(db, clientId, matchId, placeId, price, status)) {
        ticketsUI->updateTicketsList();
        statusBar()->showMessage("Ticket added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add ticket.");
    }
}

void MainWindow::handleTicketDeleted(int ticketId) {
    if (gestionTickets->supprimerTicket(db, ticketId)) {
        ticketsUI->updateTicketsList();
        statusBar()->showMessage("Ticket deleted successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete ticket.");
    }
}

void MainWindow::handleTicketUpdated(int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus) {
    if (gestionTickets->modifierTicket(db, ticketId, newClientId, newMatchId, newPlaceId, newPrice, newStatus)) {
        ticketsUI->updateTicketsList();
        statusBar()->showMessage("Ticket updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update ticket.");
    }
}

void MainWindow::handleSearchTextChanged(const QString& searchTerm) {
    // Filter Players
    playerBox->searchPlayer(searchTerm);

    // Filter Matches
    matchUI->searchMatch(searchTerm);

    // Filter Standings
    // ... (Implement filtering for the standings table) ...

    // Filter Player Profile
    // ... (Implement filtering for player profile) ...

    // Filter Places
    // ... (Implement filtering for places) ...

    // Filter Reservations
    // ... (Implement filtering for reservations) ...

    // Filter Terrains
    // ... (Implement filtering for terrains) ...

    // Filter Tickets
    // ... (Implement filtering for tickets) ...
}

void MainWindow::updateStandings() {
    QList<Joueur> players = gestionJoueurs->getJoueurs(db);
    QMap<QString, int> playerWins; 

    // Calculate wins from match data
    QList<Match> matches = gestionJoueurs->getMatches(db); 
    for (const Match& match : matches) {
        if (match.getScore1() > match.getScore2()) {
            playerWins[match.getJoueur1().getNom()]++; 
        } else if (match.getScore2() > match.getScore1()) {
            playerWins[match.getJoueur2().getNom()]++; 
        } 
        // Handle ties as needed based on your tournament rules
    }

    // Sort players by wins (descending order)
    QList<QPair<QString, int>> sortedPlayers;
    for (const QString& playerName : playerWins.keys()) {
        sortedPlayers.append(qMakePair(playerName, playerWins[playerName]));
    }
    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
              [](const QPair<QString, int>& a, const QPair<QString, int>& b) {
                  return a.second > b.second; 
              });

    // Update the standings table view model
    standingsModel->removeRows(0, standingsModel->rowCount()); // Clear existing rows
    for (int i = 0; i < sortedPlayers.size(); ++i) {
        standingsModel->insertRow(i);
        standingsModel->setData(standingsModel->index(i, 0), sortedPlayers[i].first);
        standingsModel->setData(standingsModel->index(i, 1), sortedPlayers[i].second);
    }
}