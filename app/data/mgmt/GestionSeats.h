#ifndef GESTIONSEATS_H
#define GESTIONSEATS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Seat.h" 

class GestionSeats
{
public:
    GestionSeats(const QSqlDatabase& db);
    ~GestionSeats();

    bool ajouterSeat(const QSqlDatabase& db, int placeId, bool isAvailable);
    bool supprimerSeat(const QSqlDatabase& db, int seatId); 
    bool modifierSeat(const QSqlDatabase& db, int seatId, bool newIsAvailable);
    QList<Seat> getSeats(const QSqlDatabase& db) const; 
    Seat getSeatById(const QSqlDatabase& db, int seatId) const; 
    bool updateSeatStatus(const QSqlDatabase& db, int seatId, const QString& newStatus);
};

#endif // GESTIONSEATS_H