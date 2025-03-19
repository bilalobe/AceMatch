#ifndef TICKETMANAGER_H
#define TICKETMANAGER_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Ticket.h"

class PlayerManager;
class ClientManager;
class SeatManager;

class TicketManager : public QObject
{
    Q_OBJECT

public:
    TicketManager(const QSqlDatabase& db, PlayerManager* playerManager, 
                   ClientManager* clientManager, SeatManager* seatManager);
    ~TicketManager();

    bool addTicket(int clientId, int matchId, int seatId, double price, const QString& status);
    bool removeTicket(int ticketId); 
    bool updateTicket(int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus);
    QList<Ticket> getTickets() const;
    void searchTicket(const QString& searchTerm);
    Ticket getTicketById(int ticketId) const;

signals:
    void ticketFound(int id, const Client& client, const Match& match, const Seat& place, double price, const QString& status);

private:
    QSqlDatabase db;
    PlayerManager* playerManager;
    ClientManager* clientManager;
    SeatManager* seatManager;
};

#endif // TICKETMANAGER_H
