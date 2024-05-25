#ifndef GESTIONTICKETS_H
#define GESTIONTICKETS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Ticket.h" 

class GestionTickets
{
public:
    GestionTickets(const QSqlDatabase& db);
    ~GestionTickets();

    bool ajouterTicket(const QSqlDatabase& db, int clientId, int matchId, int placeId, double price, const QString& status);
    bool supprimerTicket(const QSqlDatabase& db, int ticketId); 
    bool modifierTicket(const QSqlDatabase& db, int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus);
    QList<Ticket> getTickets(const QSqlDatabase& db) const; 
};

#endif // GESTIONTICKETS_H