#include "GestionSeats.h"
#include "GestionPlaces.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <format>
#include <ranges>

GestionSeats::GestionSeats(const QSqlDatabase& db, GestionPlaces* gestionPlaces)
    : db(db), gestionPlaces(gestionPlaces)
{
    // Database and dependencies are now stored as member variables
}

GestionSeats::~GestionSeats()
{
    // No need to close the database connection, as it's managed in MainWindow
}

Result<int> GestionSeats::ajouterSeat(int placeId, bool isAvailable) {
    QSqlQuery query(db);
    const auto status = isAvailable ? "Available" : "Taken";
    
    query.prepare("INSERT INTO Seats (placeId, status) VALUES (:placeId, :status)");
    query.bindValue(":placeId", placeId);
    query.bindValue(":status", status);

    if (!query.exec()) {
        qDebug() << "Error adding seat:" << query.lastError();
        return std::unexpected(QueryError("INSERT INTO Seats", query.lastError().text().toStdString()));
    }
    
    // Get the ID of the newly inserted seat
    const int newId = query.lastInsertId().toInt();
    
    // Emit signal about the new seat
    emit seatAdded(newId, placeId, isAvailable);
    
    return newId;
}

Result<bool> GestionSeats::supprimerSeat(int seatId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Seats WHERE id = :seatId");
    query.bindValue(":seatId", seatId);

    if (!query.exec()) {
        qDebug() << "Error deleting seat:" << query.lastError();
        return std::unexpected(QueryError("DELETE FROM Seats", query.lastError().text().toStdString()));
    }
    
    // Check if any rows were actually deleted
    if (query.numRowsAffected() == 0) {
        return std::unexpected(NotFoundError("Seat", seatId));
    }
    
    // Emit signal about the deleted seat
    emit seatDeleted(seatId);
    
    return true;
}

Result<bool> GestionSeats::modifierSeat(int seatId, bool newIsAvailable) {
    QSqlQuery query(db);
    const auto status = newIsAvailable ? "Available" : "Taken";
    
    query.prepare("UPDATE Seats SET status = :newStatus WHERE id = :seatId");
    query.bindValue(":newStatus", status);
    query.bindValue(":seatId", seatId);

    if (!query.exec()) {
        qDebug() << "Error updating seat:" << query.lastError();
        return std::unexpected(QueryError("UPDATE Seats", query.lastError().text().toStdString()));
    }
    
    // Check if any rows were actually updated
    if (query.numRowsAffected() == 0) {
        return std::unexpected(NotFoundError("Seat", seatId));
    }
    
    // Emit signal about the updated seat
    emit seatUpdated(seatId, newIsAvailable);
    
    return true;
}

// Helper method using C++23's deducing this
auto GestionSeats::formatSeatQuery(this auto&& self, std::string_view queryStr) const {
    // Format query string with consistent error handling
    // This is a placeholder implementation
    return queryStr;
}

QList<Seat> GestionSeats::getSeats() const {
    QList<Seat> seats;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Seats");

    while (query.next()) {
        int id = query.value("id").toInt();
        int placeId = query.value("placeId").toInt();
        QString status = query.value("status").toString();

        // Get the associated place using the GestionPlaces dependency
        Result<Place> placeResult = gestionPlaces->getPlaceById(placeId);
        
        // Use if-with-initializer from C++17
        if (Place place; placeResult.has_value()) {
            place = placeResult.value();
            
            // Create seat with calculated position based on place layout
            // This is a simplified example - real positioning would be more sophisticated
            const int row = id % 10;
            const int col = id / 10;
            QPointF center(col * 30.0, row * 30.0);
            qreal size = 20.0;
            
            seats.append(Seat(id, center, size, status == "Available"));
        }
        else {
            qDebug() << "Error getting place for seat:" << placeResult.error().what();
        }
    }
    
    return seats;
}

Result<Seat> GestionSeats::getSeatById(int seatId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Seats WHERE id = :seatId");
    query.bindValue(":seatId", seatId);

    if (!query.exec()) {
        qDebug() << "Error querying seat:" << query.lastError();
        return std::unexpected(QueryError("SELECT FROM Seats", query.lastError().text().toStdString()));
    }
    
    if (!query.next()) {
        return std::unexpected(NotFoundError("Seat", seatId));
    }
    
    int placeId = query.value("placeId").toInt();
    QString status = query.value("status").toString();
    
    // Get the associated place using the GestionPlaces dependency
    Result<Place> placeResult = gestionPlaces->getPlaceById(placeId);
    if (!placeResult.has_value()) {
        return std::unexpected(placeResult.error());
    }
    
    // Create seat with position based on place layout
    const int row = seatId % 10;
    const int col = seatId / 10;
    QPointF center(col * 30.0, row * 30.0);
    qreal size = 20.0;
            
    return Seat(seatId, center, size, status == "Available");
}

Result<bool> GestionSeats::updateSeatStatus(int seatId, bool isAvailable) {
    return modifierSeat(seatId, isAvailable);
}

QList<Seat> GestionSeats::searchSeats(std::string_view searchTerm) const {
    QList<Seat> foundSeats;
    QSqlQuery query(db);
    
    // Convert string_view to QString for Qt API
    QString qSearchTerm = QString::fromStdString(std::string(searchTerm));
    
    query.prepare("SELECT * FROM Seats WHERE placeId LIKE :searchTerm OR status LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + qSearchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error searching seats:" << query.lastError();
        return foundSeats; // Return empty list on error
    }

    // Use ranges and views to transform query results
    while (query.next()) {
        int id = query.value("id").toInt();
        int placeId = query.value("placeId").toInt();
        QString status = query.value("status").toString();

        // Create seat with simple positioning
        const int row = id % 10;
        const int col = id / 10;
        QPointF center(col * 30.0, row * 30.0);
        qreal size = 20.0;
        
        Seat seat(id, center, size, status == "Available");
        foundSeats.append(seat);
        
        // Emit signal about found seat
        emit seatFound(id, placeId, status == "Available");
    }
    
    return foundSeats;
}
