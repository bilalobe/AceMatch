#include "GestionTickets.h"
#include "GestionJoueurs.h"
#include "GestionClients.h"
#include "GestionPlaces.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionTickets::GestionTickets(const QSqlDatabase& db, GestionJoueurs* gestionJoueurs, 
                              GestionClients* gestionClients, GestionPlaces* gestionPlaces)
    : db(db), gestionJoueurs(gestionJoueurs), gestionClients(gestionClients), gestionPlaces(gestionPlaces)
{
    // Database is now stored as a member variable
}

GestionTickets::~GestionTickets()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionTickets::ajouterTicket(int clientId, int matchId, int placeId, double price, const QString& status) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Tickets (clientId, matchId, placeId, price, status) VALUES (:clientId, :matchId, :placeId, :price, :status)");
    query.bindValue(":clientId", clientId);
    query.bindValue(":matchId", matchId);
    query.bindValue(":placeId", placeId);
    query.bindValue(":price", price);
    query.bindValue(":status", status);

    if (!query.exec()) {
        qDebug() << "Error adding ticket:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionTickets::supprimerTicket(int ticketId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Tickets WHERE id = :ticketId");
    query.bindValue(":ticketId", ticketId);

    if (!query.exec()) {
        qDebug() << "Error deleting ticket:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionTickets::modifierTicket(int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus) {
    QSqlQuery query(db);
    query.prepare("UPDATE Tickets SET clientId = :newClientId, matchId = :newMatchId, placeId = :newPlaceId, price = :newPrice, status = :newStatus WHERE id = :ticketId");
    query.bindValue(":newClientId", newClientId);
    query.bindValue(":newMatchId", newMatchId);
    query.bindValue(":newPlaceId", newPlaceId);
    query.bindValue(":newPrice", newPrice);
    query.bindValue(":newStatus", newStatus);
    query.bindValue(":ticketId", ticketId);

    if (!query.exec()) {
        qDebug() << "Error updating ticket:" << query.lastError();
        return false;
    }
    return true;
}

QList<Ticket> GestionTickets::getTickets() const {
    QList<Ticket> tickets;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Tickets"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int matchId = query.value("matchId").toInt();
        int placeId = query.value("placeId").toInt();
        double price = query.value("price").toDouble(); 
        QString status = query.value("status").toString();

        // Get related objects using the stored manager pointers
        Client client = gestionClients->getClientById(clientId); 
        Match match = gestionJoueurs->getMatchById(matchId);
        Place place = gestionPlaces->getPlaceById(placeId);

        tickets.append(Ticket(id, client, match, place, price, status)); 
    }
    return tickets;
}

void GestionTickets::searchTicket(const QString &searchTerm)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Tickets WHERE clientId LIKE :searchTerm OR matchId LIKE :searchTerm OR placeId LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error searching ticket:" << query.lastError();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int matchId = query.value("matchId").toInt();
        int placeId = query.value("placeId").toInt();
        double price = query.value("price").toDouble(); 
        QString status = query.value("status").toString();

        // Get related objects using the stored manager pointers
        Client client = gestionClients->getClientById(clientId); 
        Match match = gestionJoueurs->getMatchById(matchId);
        Place place = gestionPlaces->getPlaceById(placeId);

        // Emit signal with found ticket
        emit ticketFound(id, client, match, place, price, status);
    }
}

Ticket GestionTickets::getTicketById(int ticketId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Tickets WHERE id = :ticketId");
    query.bindValue(":ticketId", ticketId);

    if (query.exec() && query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int matchId = query.value("matchId").toInt();
        int placeId = query.value("placeId").toInt();
        double price = query.value("price").toDouble(); 
        QString status = query.value("status").toString();

        // Get related objects using the stored manager pointers
        Client client = gestionClients->getClientById(clientId); 
        Match match = gestionJoueurs->getMatchById(matchId);
        Place place = gestionPlaces->getPlaceById(placeId);

        return Ticket(id, client, match, place, price, status);
    }
    
    qDebug() << "Error retrieving ticket with ID:" << ticketId;
    return Ticket();
}
