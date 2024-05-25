// GestionReservations.h
#ifndef GESTIONRESERVATIONS_H
#define GESTIONRESERVATIONS_H

// ... (Other includes) ...

class GestionReservations {
public:
    // ... (Other methods) ...

    bool ajouterReservation(QSqlDatabase& db, int clientId, int placeId, const QDateTime& dateTime);
    bool supprimerReservation(QSqlDatabase& db, int reservationId); 
    bool modifierReservation(QSqlDatabase& db, int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime);
    QList<Reservation> getReservations(const QSqlDatabase& db) const; 
};

#endif // GESTIONRESERVATIONS_H