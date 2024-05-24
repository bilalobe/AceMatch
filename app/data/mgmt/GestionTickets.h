// GestionTickets.h
#ifndef GESTIONTICKETS_H
#define GESTIONTICKETS_H



class GestionTickets {
public:
    // ... (Other methods) ...

    bool ajouterTicket(QSqlDatabase& db, int clientId, int matchId, int placeId, double price, const QString& status);
    bool supprimerTicket(QSqlDatabase& db, int ticketId); 
    bool modifierTicket(QSqlDatabase& db, int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus);
    QList<Ticket> getTickets(const QSqlDatabase& db) const; 
};

#endif // GESTIONTICKETS_H