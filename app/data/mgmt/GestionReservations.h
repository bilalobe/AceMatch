#ifndef GESTIONRESERVATIONS_H
#define GESTIONRESERVATIONS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Reservation.h"

class GestionClients;
class GestionPlaces;

class GestionReservations : public QObject
{
    Q_OBJECT

public:
    GestionReservations(const QSqlDatabase& db, GestionClients* gestionClients, GestionPlaces* gestionPlaces, QObject* parent = nullptr);
    ~GestionReservations();

    bool ajouterReservation(int clientId, int placeId, const QDateTime& dateTime);
    bool supprimerReservation(int reservationId); 
    bool modifierReservation(int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime);
    void searchReservations(const QString& searchTerm);
    QList<Reservation> getReservations() const;
    Reservation getReservationById(int reservationId) const;

signals:
    void reservationFound(int id, const Client& client, const Place& place, const QDateTime& dateTime);

private:
    QSqlDatabase db;
    GestionClients* gestionClients;
    GestionPlaces* gestionPlaces;
};

#endif // GESTIONRESERVATIONS_H
