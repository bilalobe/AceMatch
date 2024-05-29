#include "GestionSeats.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionSeats::GestionSeats(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

GestionSeats::~GestionSeats()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionSeats::ajouterSeat(const QSqlDatabase& db, int placeId, bool isAvailable) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Seats (placeId, status) VALUES (:placeId, :status)");
    query.bindValue(":placeId", placeId);
    query.bindValue(":status", isAvailable ? "Available" : "Taken"); 

    if (!query.exec()) {
        qDebug() << "Error adding seat:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionSeats::supprimerSeat(const QSqlDatabase& db, int seatId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Seats WHERE id = :seatId");
    query.bindValue(":seatId", seatId);

    if (!query.exec()) {
        qDebug() << "Error deleting seat:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionSeats::modifierSeat(const QSqlDatabase& db, int seatId, bool newIsAvailable) {
    QSqlQuery query(db);
    query.prepare("UPDATE Seats SET status = :newStatus WHERE id = :seatId");
    query.bindValue(":newStatus", newIsAvailable ? "Available" : "Taken");
    query.bindValue(":seatId", seatId);

    if (!query.exec()) {
        qDebug() << "Error updating seat:" << query.lastError();
        return false;
    }
    return true;
}

QList<Seat> GestionSeats::getSeats(const QSqlDatabase& db) const {
    QList<Seat> seats;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Seats"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        int placeId = query.value("placeId").toInt();
        QString status = query.value("status").toString();

        // Assuming you have a way to get Place objects by ID
        Place place = gestionPlaces->getPlaceById(db, placeId); 

        // Assuming you have a way to get the seat's position (x, y) and size
        // (You'll need to define this logic based on your seat layout)
               QPointF center = QPointF(0, 0); // Replace with the correct position
        qreal size = 20.0; // Replace with the correct size 

        seats.append(Seat(id, center, size, status == "Available")); // Assuming "Available" is the status for an available seat
    }
    return seats;
}

Seat GestionSeats::getSeatById(const QSqlDatabase& db, int seatId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Seats WHERE id = :seatId");
    query.bindValue(":seatId", seatId);

    if (query.exec() && query.next()) {
        int placeId = query.value("placeId").toInt();
        QString status = query.value("status").toString();
        // ... (Get seat position and size) ... 

        return Seat(seatId, QPointF(0, 0), 20.0, status == "Available"); // Replace with correct position and size 
    } else {
        qDebug() << "Error getting seat by ID:" << query.lastError();
        return Seat();
    }
}

bool GestionSeats::updateSeatStatus(const QSqlDatabase& db, int seatId, const QString& newStatus) {
    QSqlQuery query(db);
    query.prepare("UPDATE Seats SET status = :newStatus WHERE id = :seatId");
    query.bindValue(":newStatus", newStatus);
    query.bindValue(":seatId", seatId);

    if (!query.exec()) {
        qDebug() << "Error updating seat status:" << query.lastError();
        return false;
    }
    return true;
}
