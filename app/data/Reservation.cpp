#include "Reservation.h"

Reservation::Reservation(int id, const Client& client, const Place& place, const QDateTime& dateTime) :
    id(id),
    client(client),
    place(place),
    dateTime(dateTime)
{
}

int Reservation::getId() const
{
    return id;
}

const Client& Reservation::getClient() const
{
    return client;
}

const Place& Reservation::getPlace() const
{
    return place;
}

QDateTime Reservation::getDateTime() const
{
    return dateTime;
}


