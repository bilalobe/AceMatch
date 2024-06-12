#include "GestionReservations.h"
#include "GestionClients.h"
#include "GestionPlaces.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionReservations::GestionReservations(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

GestionReservations::~GestionReservations()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionReservations::ajouterReservation(const QSqlDatabase& db, int clientId, int placeId, const QDateTime& dateTime) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Reservations (clientId, placeId, dateTime) VALUES (:clientId, :placeId, :dateTime)");
    query.bindValue(":clientId", clientId);
    query.bindValue(":placeId", placeId);
    query.bindValue(":dateTime", dateTime);

    if (!query.exec()) {
        qDebug() << "Error adding reservation:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionReservations::supprimerReservation(const QSqlDatabase& db, int reservationId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Reservations WHERE id = :reservationId");
    query.bindValue(":reservationId", reservationId);

    if (!query.exec()) {
        qDebug() << "Error deleting reservation:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionReservations::modifierReservation(const QSqlDatabase& db, int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime) {
    QSqlQuery query(db);
    query.prepare("UPDATE Reservations SET clientId = :newClientId, placeId = :newPlaceId, dateTime = :newDateTime WHERE id = :reservationId");
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

QList<Reservation> GestionReservations::getReservations(const QSqlDatabase& db) const {
    QList<Reservation> reservations;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Reservations"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int placeId = query.value("placeId").toInt();
        QDateTime dateTime = query.value("dateTime").toDateTime();

        // Assuming you have a way to get Client and Place objects by ID
        Client client = gestionClients->getClientById(db, clientId); 
        Place place = gestionPlaces->getPlaceById(db, placeId); 

        reservations.append(Reservation(id, client, place, dateTime)); 
    }
    return reservations;
}

void GestionReservations::searchReservations(const QSqlDatabase &db, const QString &searchTerm)
{
        QSqlQuery query(db);
    query.prepare("SELECT * FROM Reservations WHERE clientId LIKE :searchTerm OR placeId LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error searching reservation:" << query.lastError();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int placeId = query.value("placeId").toInt();
        QDateTime dateTime = query.value("dateTime").toDateTime();

        // Assuming you have a way to get Client and Place objects by ID
        Client client = gestionClients->getClientById(db, clientId); 
        Place place = gestionPlaces->getPlaceById(db, placeId); 

        // Emit a signal to notify the UI about the found reservation
        emit reservationFound(id, client, place, dateTime);
    }
}
