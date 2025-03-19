#ifndef TICKET_H
#define TICKET_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Client.h"
#include "Match.h"
#include "Seat.h"

class Ticket
{
public:
    Ticket(int id = -1, const Client& client = Client(), const Match& match = Match(), const Seat& seat = Seat(), double price = 0.0, const QString& status = "")
        : id(id), client(client), match(match), place(place), price(price), status(status) {} // Inline constructor
    int getId() const { return id; }
    const Client& getClient() const { return client; }
    const Match& getMatch() const { return match; }
    const Seat& getPlace() const { return place; }
    double getPrice() const { return price; }
    QString getStatus() const { return status; }

private:
    int id;
    Client client;
    Match match;
    Seat place;
    double price;
    QString status;
};

#endif // TICKET_H