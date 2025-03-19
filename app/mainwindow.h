#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>

// UI Classes

#include "data/mgmt/SeatManager.h"
#include "ui/headers/matchui.h"
#include "ui/headers/playerbox.h"
#include "ui/headers/playerprofileui.h"
#include "ui/headers/scoreboardmatchdetailsui.h"
#include "ui/headers/seatsui.h"
#include "ui/headers/reservationsui.h"
#include "ui/headers/courtsui.h"
#include "ui/headers/ticketsui.h"
#include "ui/headers/scoreui.h"
#include "ui/headers/clientsui.h"
#include "ui/headers/seatsui.h"

// Data Management Classes
#include "data/mgmt/PlayerManager.h"
#include "data/mgmt/MatchManager.h"
#include "data/mgmt/ClientManager.h"
#include "data/mgmt/SeatManager.h"
#include "data/mgmt/ReservationManager.h"
#include "data/mgmt/CourtManager.h"
#include "data/mgmt/TicketManager.h"
#include "data/mgmt/ScoreManager.h"
#include "data/mgmt/PaymentManager.h"

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
    PlayerManager* getGestionJoueurs() const { return playerManager; }
    MatchManager* getGestionMatch() const { return matchManager; }
    ClientManager* getGestionClients() const { return clientManager; }
    SeatManager* getGestionPlaces() const { return seatManager; }
    ReservationManager* getGestionReservations() const { return reservationManager; }
    CourtManager* getGestionCourts() const { return courtManager; }
    TicketManager* getGestionTickets() const { return ticketManager; }
    ScoreManager* getGestionScores()   const { return gestionScores; }
    ClientManager* getGestionPaiements() const { return paymentManager; }
    SeatManager* getGestionSeats() const { return gestionSeats; } // Add this getter

private slots:
    // Player Slots
    void handlePlayerAdded(const QString& name, int ranking);
    void handlePlayerRemoved(const QString& name);
    void handlePlayerUpdated(const QString& name, int newRanking);
    void handlePlayerSearched(const QString& searchTerm);

    // Match Slots
    void handleMatchCreated(const QString& player1Name, const QString& player2Name, int score1, int score2);
    void handleMatchDeleted(int matchId);
    void handleMatchUpdated(int matchId, int newScore1, int newScore2);

    // Player Profile Slots
    void handlePlayerProfileUpdated(const QString& playerName, int newRanking);

    // Places Slots
    void handlePlaceAdded(const QString& name, int capacity);
    void handlePlaceDeleted(int seatId);
    void handlePlaceUpdated(int seatId, const QString& newName, int newCapacity);

    // Reservations Slots
    void handleReservationAdded(int clientId, int seatId, const QDateTime& dateTime);
    void handleReservationDeleted(int reservationId);
    void handleReservationUpdated(int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime);

    // Courts Slots
    void handleCourtAdded(const QString& name, const QString& type);
    void handleCourtDeleted(int CourtId);
    void handleCourtUpdated(int CourtId, const QString& newName, const QString& newType);

    // Tickets Slots
    void handleTicketAdded(int clientId, int matchId, int seatId, double price, const QString& status);
    void handleTicketDeleted(int ticketId);
    void handleTicketUpdated(int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus);

    // Score Slots
    void handleScoreAdded(int matchId, int score1, int score2);
    void handleScoreDeleted(int scoreId);
    void handleScoreUpdated(int scoreId, int newScore1, int newScore2);

    // Client Slots
    void handleClientAdded(const QString& name, const QString& email, const QString& phoneNumber);
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
    CourtUI* CourtsUI;
    TicketsUI* ticketsUI;
    ScoreUI* scoreUI;
    ClientsUI* clientsUI;
    SeatsUI* seatsUI;

    // Standings UI Elements
    QStandardItemModel* standingsModel;
    QTableView* standingsTableView;

    // Data Management Classes
    PlayerManager* playerManager;
    MatchManager* matchManager;
    ClientManager* clientManager;
    SeatManager* seatManager;
    ReservationManager* reservationManager;
    CourtManager* courtManager;
    TicketManager* ticketManager;
    ScoreManager* gestionScores;
    PaymentManager* paymentManager;
    SeatManager* gestionSeats;

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
