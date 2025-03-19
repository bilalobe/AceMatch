#ifndef GESTIONSEATS_H
#define GESTIONSEATS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include <expected>       // C++23 for error handling
#include <string_view>    // C++17/23 for non-owning string view
#include <ranges>         // C++20/23 for range operations
#include <span>           // C++20 for non-owning array view
#include "..\Seat.h"
#include "Errors.h"       // Custom error types

class GestionPlaces;

// Custom result type for operations that can fail
template<typename T>
using Result = std::expected<T, DatabaseError>;

class GestionSeats : public QObject
{
    Q_OBJECT

public:
    GestionSeats(const QSqlDatabase& db, GestionPlaces* gestionPlaces);
    ~GestionSeats();

    // Modern C++23 methods with std::expected for error handling
    Result<int> ajouterSeat(int placeId, bool isAvailable);
    Result<bool> supprimerSeat(int seatId); 
    Result<bool> modifierSeat(int seatId, bool newIsAvailable);
    
    // Method to get all seats with ranges support
    QList<Seat> getSeats() const;
    
    // Find seat by ID with better error handling
    Result<Seat> getSeatById(int seatId) const;
    
    // Update status with modern error handling
    Result<bool> updateSeatStatus(int seatId, bool isAvailable);
    
    // Search using string_view and ranges
    QList<Seat> searchSeats(std::string_view searchTerm) const;

signals:
    void seatAdded(int id, int placeId, bool isAvailable);
    void seatDeleted(int id);
    void seatUpdated(int id, bool isAvailable);
    void seatStatusChanged(int id, bool isAvailable);
    void seatFound(int id, int placeId, bool isAvailable);

private:
    QSqlDatabase db;
    GestionPlaces* gestionPlaces;
    
    // C++23 deducing this for concise helper methods
    auto formatSeatQuery(this auto&& self, std::string_view queryStr) const;
};

#endif // GESTIONSEATS_H
