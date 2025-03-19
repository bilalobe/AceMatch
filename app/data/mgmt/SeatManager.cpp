#include "SeatManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <format>
#include <ranges>

SeatManager::SeatManager(const QSqlDatabase& db)
    : db(db)
{
    // Database is now stored as a member variable
}

SeatManager::~SeatManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

Result<int> SeatManager::addSeat(int seatId, bool isAvailable) {
    QSqlQuery query(db);
    const auto status = isAvailable ? "Available" : "Taken";
    
    query.prepare("INSERT INTO Seats (seatId, status) VALUES (:seatId, :status)");
    query.bindValue(":seatId", seatId);
    query.bindValue(":status", status);

    if (!query.exec()) {
        qDebug() << "Error adding seat:" << query.lastError();
        return std::unexpected(QueryError("INSERT INTO Seats", query.lastError().text().toStdString()));
    }
    
    const int newId = query.lastInsertId().toInt();
    emit seatAdded(newId, seatId, isAvailable);
    
    return newId;
}

Result<bool> SeatManager::removeSeat(int seatId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Seats WHERE id = :seatId");
    query.bindValue(":seatId", seatId);

    if (!query.exec()) {
        qDebug() << "Error deleting seat:" << query.lastError();
        return std::unexpected(QueryError("DELETE FROM Seats", query.lastError().text().toStdString()));
    }
    
    if (query.numRowsAffected() == 0) {
        return std::unexpected(NotFoundError("Seat", seatId));
    }
    
    emit seatDeleted(seatId);
    return true;
}

Result<bool> SeatManager::updateSeat(int seatId, bool newIsAvailable) {
    QSqlQuery query(db);
    const auto status = newIsAvailable ? "Available" : "Taken";
    
    query.prepare("UPDATE Seats SET status = :newStatus WHERE id = :seatId");
    query.bindValue(":newStatus", status);
    query.bindValue(":seatId", seatId);

    if (!query.exec()) {
        qDebug() << "Error updating seat:" << query.lastError();
        return std::unexpected(QueryError("UPDATE Seats", query.lastError().text().toStdString()));
    }
    
    if (query.numRowsAffected() == 0) {
        return std::unexpected(NotFoundError("Seat", seatId));
    }
    
    emit seatUpdated(seatId, newIsAvailable);
    return true;
}

QList<Seat> SeatManager::getSeats() const {
    QList<Seat> seats;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Seats");

    while (query.next()) {
        int id = query.value("id").toInt();
        int sId = query.value("seatId").toInt();
        QString status = query.value("status").toString();

        // Simple positioning calculation
        const int row = id % 10;
        const int col = id / 10;
        QPointF center(col * 30.0, row * 30.0);
        qreal size = 20.0;
        
        seats.append(Seat(id, center, size, status == "Available"));
    }
    
    return seats;
}

Result<Seat> SeatManager::getSeatById(int seatId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Seats WHERE id = :seatId");
    query.bindValue(":seatId", seatId);

    if (!query.exec()) {
        qDebug() << "Error querying seat:" << query.lastError();
        return std::unexpected(QueryError("SELECT FROM Seats", query.lastError().text().toStdString()));
    }
    
    if (!query.next()) 
        return std::unexpected(NotFoundError("Seat", seatId));
    
    int sId = query.value("seatId").toInt();
    QString status = query.value("status").toString();
    
    const int row = sId % 10;
    const int col = sId / 10;
    QPointF center(col * 30.0, row * 30.0);
    qreal size = 20.0;
            
    return Seat(seatId, center, size, status == "Available");
}

QList<Seat> SeatManager::searchSeats(std::string_view searchTerm) const {
    QList<Seat> foundSeats;
    QSqlQuery query(db);
    QString qSearchTerm = QString::fromStdString(std::string(searchTerm));
    
    query.prepare("SELECT * FROM Seats WHERE seatId LIKE :searchTerm OR status LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + qSearchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error searching seats:" << query.lastError();
        return foundSeats;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int sId = query.value("seatId").toInt();
        QString status = query.value("status").toString();

        const int row = id % 10;
        const int col = id / 10;
        QPointF center(col * 30.0, row * 30.0);
        qreal size = 20.0;
        
        foundSeats.append(Seat(id, center, size, status == "Available"));
        emit seatFound(id, sId, status == "Available");
    }
    
    return foundSeats;
}
