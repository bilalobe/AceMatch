#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Reservation.h"

class ClientManager;
class SeatManager;

class ReservationManager : public QObject
{
    Q_OBJECT

public:
    ReservationManager(const QSqlDatabase& db, ClientManager* clientManager, SeatManager* seatManager, QObject* parent = nullptr);
    ~ReservationManager();

    bool addReservation(int clientId, int seatId, const QDateTime& dateTime);
    bool removeReservation(int reservationId); 
    bool updateReservation(int reservationId, int newClientId, int newPlaceId, const QDateTime& newDateTime);
    void searchReservations(const QString& searchTerm);
    QList<Reservation> getReservations() const;
    Reservation getReservationById(int reservationId) const;

signals:
    void reservationFound(int id, const Client& client, const Seat& place, const QDateTime& dateTime);

private:
    QSqlDatabase db;
    ClientManager* clientManager;
    SeatManager* seatManager;
};

#endif // RESERVATIONMANAGER_H
