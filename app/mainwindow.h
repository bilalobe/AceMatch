#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>

// UI Classes

#include "data/mgmt/GestionSeats.h"
#include "ui/headers/matchui.h"
#include "ui/headers/playerbox.h"
#include "ui/headers/playerprofileui.h"
#include "ui/headers/scoreboardmatchdetailsui.h"
#include "ui/headers/placesui.h"
#include "ui/headers/reservationsui.h"
#include "ui/headers/terrainsui.h"
#include "ui/headers/ticketsui.h"
#include "ui/headers/scoreui.h"
#include "ui/headers/clientsui.h"
#include "ui/headers/seatsui.h"

// Data Management Classes
#include "data/mgmt/GestionJoueurs.h"
#include "data/mgmt/GestionMatch.h"
#include "data/mgmt/GestionClients.h"
#include "data/mgmt/GestionPlaces.h"
#include "data/mgmt/GestionReservations.h"
#include "data/mgmt/GestionTerrains.h"
#include "data/mgmt/GestionTickets.h"
#include "data/mgmt/GestionScores.h"
#include "data/mgmt/GestionPaiements.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Getters for Gestion* objects (to be used in UI classes)
    GestionJoueurs* getGestionJoueurs() const { return gestionJoueurs; }
    GestionMatch* getGestionMatch() const { return gestionMatch; }
    GestionClients* getGestionClients() const { return gestionClients; }
    GestionPlaces* getGestionPlaces() const { return gestionPlaces; }
    GestionReservations* getGestionReservations() const { return gestionReservations; }
    GestionTerrains* getGestionTerrains() const { return gestionTerrains; }
    GestionTickets* getGestionTickets() const { return gestionTickets; }
    GestionScore* getGestionScores()   const { return gestionScores; }
    GestionClients* getGestionPaiements() const { return gestionPaiements; }
    GestionSeats* getGestionSeats() const { return gestionSeats; } // Add this getter

private slots:
    // Player Slots
    void handlePlayerAdded(const QString& name, int ranking);
    void handlePlayerRemoved(const QString& nom);
    void handlePlayerUpdated(const QString& nom, int newRanking);
    void handlePlayerSearched(const QString& searchTerm);

    // Match Slots
    void handleMatchCreated(const QString& player1Name, const QString& player2Name, int score1, int score2);
    void handleMatchDeleted(int matchId);
    void handleMatchUpdated(int matchId, int newScore1, int newScore2);

    // Player Profile Slots
    void handlePlayerProfileUpdated(const QString& playerName, int newRanking);

    // Places Slots
    void handlePlaceAdded(const QString& name, int capacity);
    void handlePlaceDeleted(int placeId);
    void handlePlaceUpdated(int placeId, const QString& newName, int newCapacity);

    // Reservations Slots
    void handleReservationAdded(int clientId, int placeId, const QDateTime& dateTime);
    void handleReservationDeleted(int reservationId);
    void handleReservationUpdated(int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime);

    // Terrains Slots
    void handleTerrainAdded(const QString& name, const QString& type);
    void handleTerrainDeleted(int terrainId);
    void handleTerrainUpdated(int terrainId, const QString& newName, const QString& newType);

    // Tickets Slots
    void handleTicketAdded(int clientId, int matchId, int placeId, double price, const QString& status);
    void handleTicketDeleted(int ticketId);
    void handleTicketUpdated(int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus);

    // Score Slots
    void handleScoreAdded(int matchId, int score1, int score2);
    void handleScoreDeleted(int scoreId);
    void handleScoreUpdated(int scoreId, int newScore1, int newScore2);

    // Client Slots
    void handleClientAdded(const QString& nom, const QString& email, const QString& phoneNumber);
    void handleClientDeleted(int clientId);
    void handleClientUpdated(int clientId, const QString& newName, const QString& newEmail, const QString& newPhoneNumber);

    // Seats Slots
    void handleSeatSelected(int seatId);
    void handleSeatStatusChanged(int seatId, bool isAvailable);

    // Other Slots
    void handleMatchSelected(int matchId);
    void handleSearchTextChanged(const QString& searchTerm);
    void updateStandings();

    // Menu Actions
    void handleNewTournament();
    void handleSave();
    void handleLoad();
    void handleExportData();
    void handleImportData();
    void handleSettings();
    void handleAbout();
    void changeLanguageToEnglish();
    void changeLanguageToFrench();

private: // Helper Functions
    void initializeDatabase();
    void loadInitialLanguage();
    void loadStylesheet();
    void initializeGestionClasses();
    void createUIComponents();
    void setupTabs();
    void setupMenuBar();
    void setupToolbar();
    void connectSignalsAndSlots();
    void updateAllUI();
    void loadLanguage(const QString& languageCode);
    void addTab(QTabWidget* tabWidget, QWidget* widget, const QString& label);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    // UI Components
    PlayerBox* playerBox;
    MatchUI* matchUI;
    PlayerProfileUI* playerProfileUI;
    ScoreboardMatchDetailsUI* scoreboardMatchDetailsUI;
    PlacesUI* placesUI;
    ReservationsUI* reservationsUI;
    TerrainUI* terrainsUI;
    TicketsUI* ticketsUI;
    ScoreUI* scoreUI;
    ClientsUI* clientsUI;
    SeatsUI* seatsUI;

    // Standings UI Elements
    QStandardItemModel* standingsModel;
    QTableView* standingsTableView;

    // Data Management Classes
    GestionJoueurs* gestionJoueurs;
    GestionMatch* gestionMatch;
    GestionClients* gestionClients;
    GestionPlaces* gestionPlaces;
    GestionReservations* gestionReservations;
    GestionTerrains* gestionTerrains;
    GestionTickets* gestionTickets;
    GestionScores* gestionScores;
    GestionPaiements* gestionPaiements;
    GestionSeats* gestionSeats;

    // Menu items
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *settingsMenu;
    QMenu *helpMenu;

    // File menu actions
    QAction *actionNew_Tournament;
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionExport_Data;
    QAction *actionImport_Data;
    QAction *actionSettings;
    QAction *actionAbout;
};

#endif // MAINWINDOW_H
