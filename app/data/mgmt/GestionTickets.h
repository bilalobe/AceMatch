#ifndef GESTIONTICKETS_H
#define GESTIONTICKETS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Ticket.h"

class GestionJoueurs;
class GestionClients;
class GestionPlaces;

class GestionTickets : public QObject
{
    Q_OBJECT

public:
    GestionTickets(const QSqlDatabase& db, GestionJoueurs* gestionJoueurs, 
                   GestionClients* gestionClients, GestionPlaces* gestionPlaces);
    ~GestionTickets();

    bool ajouterTicket(int clientId, int matchId, int placeId, double price, const QString& status);
    bool supprimerTicket(int ticketId); 
    bool modifierTicket(int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus);
    QList<Ticket> getTickets() const;
    void searchTicket(const QString& searchTerm);
    Ticket getTicketById(int ticketId) const;

signals:
    void ticketFound(int id, const Client& client, const Match& match, const Place& place, double price, const QString& status);

private:
    QSqlDatabase db;
    GestionJoueurs* gestionJoueurs;
    GestionClients* gestionClients;
    GestionPlaces* gestionPlaces;
};

#endif // GESTIONTICKETS_H
