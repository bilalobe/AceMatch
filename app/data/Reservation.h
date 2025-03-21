#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QDateTime>
#include "Client.h"
#include "Seat.h"

class Reservation
{
public:
    Reservation(int id = -1, const Client& client = Client(), const Seat& place = Seat(), const QDateTime& dateTime = QDateTime())
        : id(id), client(client), place(place), dateTime(dateTime) {} // Inline constructor
    int getId() const { return id; }
    const Client& getClient() const { return client; }
    const Seat& getPlace() const { return place; }
    QDateTime getDateTime() const { return dateTime; }

private:
    int id;
    Client client;
    Seat place;
    QDateTime dateTime;
};

#endif // RESERVATION_H