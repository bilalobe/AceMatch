#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>

#include "playerbox.h"
#include "matchui.h"
#include "playerprofileui.h"
#include "scoreboardmatchdetailsui.h"
#include "placesui.h"
#include "reservationsui.h"
#include "terrainsui.h"
#include "ticketsui.h"
#include "scoreui.h"
#include "clientsui.h" // Include ClientsUI

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handlePlayerAdded(const QString& name, int ranking);
    void handlePlayerRemoved(const QString& nom);
    void handlePlayerUpdated(const QString& nom, int newRanking);
    void handlePlayerSearched(const QString& searchTerm);

    void handleMatchCreated(const QString& player1Name, const QString& player2Name, int score1, int score2);
    void handleMatchDeleted(int matchId);
    void handleMatchUpdated(int matchId, int newScore1, int newScore2);

    void handlePlayerProfileUpdated(const QString& playerName, int newRanking);

    void handlePlaceAdded(const QString& name, int capacity);
    void handlePlaceDeleted(int placeId);
    void handlePlaceUpdated(int placeId, const QString& newName, int newCapacity);

    void handleReservationAdded(int clientId, int placeId, const QDateTime& dateTime);
    void handleReservationDeleted(int reservationId);
    void handleReservationUpdated(int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime);

    void handleTerrainAdded(const QString& name, const QString& type);
    void handleTerrainDeleted(int terrainId);
    void handleTerrainUpdated(int terrainId, const QString& newName, const QString& newType);

    void handleTicketAdded(int clientId, int matchId, int placeId, double price, const QString& status);
    void handleTicketDeleted(int ticketId);
    void handleTicketUpdated(int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus);

    void handleScoreAdded(int matchId, int score1, int score2);
    void handleScoreDeleted(int scoreId);
    void handleScoreUpdated(int scoreId, int newScore1, int newScore2);

    void handleMatchSelected(int matchId);
    void handleSearchTextChanged(const QString& searchTerm); 
    void updateStandings();
    void handleClientAdded(const QString& nom, const QString& email, const QString& phoneNumber);
    void handleClientDeleted(int clientId);
    void handleClientUpdated(int clientId, const QString& newName, const QString& newEmail, const QString& newPhoneNumber);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    PlayerBox* playerBox;
    MatchUI* matchUI;
    PlayerProfileUI* playerProfileUI;
    ScoreboardMatchDetailsUI* scoreboardMatchDetailsUI;
    PlacesUI* placesUI;
    ReservationsUI* reservationsUI;
    TerrainsUI* terrainsUI;
    TicketsUI* ticketsUI;
    ScoreUI* scoreUI;
    ClientsUI* clientsUI; // Add ClientsUI

    QStandardItemModel* standingsModel;
    QTableView* standingsTableView;

    GestionJoueurs* gestionJoueurs;
    GestionMatch* gestionMatch;
    GestionClients* gestionClients;
    GestionPlaces* gestionPlaces;
    GestionReservations* gestionReservations;
    GestionTerrains* gestionTerrains;
    GestionTickets* gestionTickets; 
    GestionScore* gestionScore;
    GestionPaiements* gestionPaiements; 
};

#endif // MAINWINDOW_H