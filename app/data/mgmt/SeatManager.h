#ifndef SEATMANAGER_H
#define SEATMANAGER_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include <expected>       // C++23 for error handling
#include <string_view>
#include "..\Seat.h"
#include "Errors.h"       // Custom error types

template<typename T>
using Result = std::expected<T, DatabaseError>;

class SeatManager : public QObject
{
    Q_OBJECT

public:
    // Now only takes a QSqlDatabase
    SeatManager(const QSqlDatabase& db);
    ~SeatManager();

    // Modern C++23 methods with std::expected for error handling
    Result<int> addSeat(int seatId, bool isAvailable);
    Result<bool> removeSeat(int seatId); 
    Result<bool> updateSeat(int seatId, bool newIsAvailable);
    QList<Seat> getSeats() const;
    Result<Seat> getSeatById(int seatId) const;

    // Search using string_view
    QList<Seat> searchSeats(std::string_view searchTerm) const;

signals:
    void seatAdded(int id, int seatId, bool isAvailable);
    void seatDeleted(int id);
    void seatUpdated(int id, bool isAvailable);
    void seatFound(int id, int seatId, bool isAvailable);

private:
    QSqlDatabase db;
};

#endif // SEATMANAGER_H
