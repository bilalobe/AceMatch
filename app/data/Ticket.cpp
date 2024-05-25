#include "Ticket.h"

Ticket::Ticket(int id, const Client& client, const Match& match, const Place& place, double price, const QString& status) :
    id(id),
    client(client),
    match(match),
    place(place),
    price(price),
    status(status)
{
}

int Ticket::getId() const
{
    return id;
}

const Client& Ticket::getClient() const
{
    return client;
}

const Match& Ticket::getMatch() const
{
    return match;
}

const Place& Ticket::getPlace() const
{
    return place;
}

double Ticket::getPrice() const
{
    return price;
}

QString Ticket::getStatus() const
{
    return status;
}
