#include "ReservationManager.h"
#include "ClientManager.h"
#include "SeatManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ReservationManager::ReservationManager(const QSqlDatabase& db, ClientManager* clientManager, SeatManager* seatManager, QObject* parent)
    : QObject(parent), db(db), clientManager(clientManager), seatManager(seatManager)
{
    // Database is now stored as a member variable
}

ReservationManager::~ReservationManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool ReservationManager::addReservation(int clientId, int seatId, const QDateTime& dateTime) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Reservations (clientId, seatId, dateTime) VALUES (:clientId, :seatId, :dateTime)");
    query.bindValue(":clientId", clientId);
    query.bindValue(":seatId", seatId);
    query.bindValue(":dateTime", dateTime);

    if (!query.exec()) {
        qDebug() << "Error adding reservation:" << query.lastError();
        return false;
    }
    
    int newId = query.lastInsertId().toInt();
    Client client = clientManager->getClientById(clientId);
    Seat seat = seatManager->getSeatById(seatId);
    emit reservationFound(newId, client, place, dateTime);
    
    return true;
}

bool ReservationManager::removeReservation(int reservationId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Reservations WHERE id = :reservationId");
    query.bindValue(":reservationId", reservationId);

    if (!query.exec()) {
        qDebug() << "Error deleting reservation:" << query.lastError();
        return false;
    }
    return true;
}

bool ReservationManager::updateReservation(int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime) {
    QSqlQuery query(db);
    query.prepare("UPDATE Reservations SET clientId = :newClientId, seatId = :newPlaceId, dateTime = :newDateTime WHERE id = :reservationId");
    query.bindValue(":newClientId", newClientId);
    query.bindValue(":newPlaceId", newPlaceId);
    query.bindValue(":newDateTime", newDateTime);
    query.bindValue(":reservationId", reservationId);

    if (!query.exec()) {
        qDebug() << "Error updating reservation:" << query.lastError();
        return false;
    }
    return true;
}

QList<Reservation> ReservationManager::getReservations() const {
    QList<Reservation> reservations;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Reservations"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int seatId = query.value("seatId").toInt();
        QDateTime dateTime = query.value("dateTime").toDateTime();

        // Assuming you have a way to get Client and Seat objects by ID
        Client client = clientManager->getClientById(clientId); 
        Seat seat = seatManager->getSeatById(seatId); 

        reservations.append(Reservation(id, client, place, dateTime)); 
    }
    return reservations;
}

void ReservationManager::searchReservations(const QString &searchTerm)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Reservations WHERE clientId LIKE :searchTerm OR seatId LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error searching reservation:" << query.lastError();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int seatId = query.value("seatId").toInt();
        QDateTime dateTime = query.value("dateTime").toDateTime();

        // Get related objects using the stored manager pointers
        Client client = clientManager->getClientById(clientId); 
        Seat place = seatManager->getSeatById(seatId); 

        // Emit a signal to notify the UI about the found reservation
        emit reservationFound(id, client, place, dateTime);
    }
}
