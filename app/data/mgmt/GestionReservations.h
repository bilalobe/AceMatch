#ifndef GESTIONRESERVATIONS_H
#define GESTIONRESERVATIONS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "..\Reservation.h"

class GestionReservations
{
public:
    GestionReservations(const QSqlDatabase& db);
    ~GestionReservations();

    bool ajouterReservation(const QSqlDatabase& db, int clientId, int placeId, const QDateTime& dateTime);
    bool supprimerReservation(const QSqlDatabase& db, int reservationId); 
    bool modifierReservation(const QSqlDatabase& db, int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime);
    void searchReservations(const QSqlDatabase& db, const QString& searchTerm);
    QList<Reservation> getReservations(const QSqlDatabase& db) const; 
};

#endif // GESTIONRESERVATIONS_H
