#include "TicketManager.h"
#include "PlayerManager.h"
#include "ClientManager.h"
#include "SeatManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TicketManager::TicketManager(const QSqlDatabase& db, PlayerManager* playerManager, 
                              ClientManager* clientManager, SeatManager* seatManager)
    : db(db), playerManager(playerManager), clientManager(clientManager), seatManager(seatManager)
{
    // Database is now stored as a member variable
}

TicketManager::~TicketManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool TicketManager::addTicket(int clientId, int matchId, int seatId, double price, const QString& status) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Tickets (clientId, matchId, seatId, price, status) VALUES (:clientId, :matchId, :seatId, :price, :status)");
    query.bindValue(":clientId", clientId);
    query.bindValue(":matchId", matchId);
    query.bindValue(":seatId", seatId);
    query.bindValue(":price", price);
    query.bindValue(":status", status);

    if (!query.exec()) {
        qDebug() << "Error adding ticket:" << query.lastError();
        return false;
    }
    return true;
}

bool TicketManager::removeTicket(int ticketId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Tickets WHERE id = :ticketId");
    query.bindValue(":ticketId", ticketId);

    if (!query.exec()) {
        qDebug() << "Error deleting ticket:" << query.lastError();
        return false;
    }
    return true;
}

bool TicketManager::updateTicket(int ticketId, int newClientId, int newMatchId, int newPlaceId, double newPrice, const QString& newStatus) {
    QSqlQuery query(db);
    query.prepare("UPDATE Tickets SET clientId = :newClientId, matchId = :newMatchId, seatId = :newPlaceId, price = :newPrice, status = :newStatus WHERE id = :ticketId");
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

QList<Ticket> TicketManager::getTickets() const {
    QList<Ticket> tickets;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Tickets"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int matchId = query.value("matchId").toInt();
        int seatId = query.value("seatId").toInt();
        double price = query.value("price").toDouble(); 
        QString status = query.value("status").toString();

        // Get related objects using the stored manager pointers
        Client client = clientManager->getClientById(clientId); 
        Match match = playerManager->getMatchById(matchId);
        Seat seat = seatManager->getSeatById(seatId);

        tickets.append(Ticket(id, client, match, place, price, status)); 
    }
    return tickets;
}

void TicketManager::searchTicket(const QString &searchTerm)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Tickets WHERE clientId LIKE :searchTerm OR matchId LIKE :searchTerm OR seatId LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error searching ticket:" << query.lastError();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int matchId = query.value("matchId").toInt();
        int seatId = query.value("seatId").toInt();
        double price = query.value("price").toDouble(); 
        QString status = query.value("status").toString();

        // Get related objects using the stored manager pointers
        Client client = clientManager->getClientById(clientId); 
        Match match = playerManager->getMatchById(matchId);
        Seat seat = seatManager->getSeatById(seatId);

        // Emit signal with found ticket
        emit ticketFound(id, client, match, place, price, status);
    }
}

Ticket TicketManager::getTicketById(int ticketId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Tickets WHERE id = :ticketId");
    query.bindValue(":ticketId", ticketId);

    if (query.exec() && query.next()) {
        int id = query.value("id").toInt();
        int clientId = query.value("clientId").toInt();
        int matchId = query.value("matchId").toInt();
        int seatId = query.value("seatId").toInt();
        double price = query.value("price").toDouble(); 
        QString status = query.value("status").toString();

        // Get related objects using the stored manager pointers
        Client client = clientManager->getClientById(clientId); 
        Match match = playerManager->getMatchById(matchId);
        Seat seat = seatManager->getSeatById(seatId);

        return Ticket(id, client, match, place, price, status);
    }
    
    qDebug() << "Error retrieving ticket with ID:" << ticketId;
    return Ticket();
}
