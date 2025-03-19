#include "ClientManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ClientManager::ClientManager(const QSqlDatabase& db)
    : db(db)
{
    // Database is now stored as a member variable
}

ClientManager::~ClientManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool ClientManager::addClient(const QString& name, const QString& email, const QString& phoneNumber) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Clients (name, email, phoneNumber) VALUES (:name, :email, :phoneNumber)");
    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":phoneNumber", phoneNumber);

    if (!query.exec()) {
        qDebug() << "Error adding client:" << query.lastError();
        return false;
    }
    return true;
}

bool ClientManager::removeClient(int clientId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Clients WHERE id = :clientId");
    query.bindValue(":clientId", clientId);

    if (!query.exec()) {
        qDebug() << "Error deleting client:" << query.lastError();
        return false;
    }
    return true;
}

bool ClientManager::updateClient(int clientId, const QString& newName, const QString& newEmail, const QString& newPhoneNumber) {
    QSqlQuery query(db);
    query.prepare("UPDATE Clients SET name = :newName, email = :newEmail, phoneNumber = :newPhoneNumber WHERE id = :clientId");
    query.bindValue(":newName", newName);
    query.bindValue(":newEmail", newEmail);
    query.bindValue(":newPhoneNumber", newPhoneNumber);
    query.bindValue(":clientId", clientId);

    if (!query.exec()) {
        qDebug() << "Error updating client:" << query.lastError();
        return false;
    }
    return true;
}

QList<Client> ClientManager::getClients() const {
    QList<Client> clients;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Clients");

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString email = query.value("email").toString();
        QString phoneNumber = query.value("phoneNumber").toString();

        clients.append(Client(id, name, email, phoneNumber));
    }
    return clients;
}

Client ClientManager::getClientById(int clientId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Clients WHERE id = :clientId");
    query.bindValue(":clientId", clientId);

    if (query.exec() && query.next()) {
        return Client(query.value("id").toInt(), query.value("name").toString(), query.value("email").toString(), query.value("phoneNumber").toString());
    } else {
        qDebug() << "Error getting client by ID:" << query.lastError();
        return Client();
    }
}

QList<Client> ClientManager::searchClients(const QString& searchTerm) const {
    QList<Client> results;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Clients WHERE name LIKE :term OR email LIKE :term OR phoneNumber LIKE :term");
    query.bindValue(":term", "%" + searchTerm + "%");
    
    if (!query.exec()) {
        qDebug() << "Error searching clients:" << query.lastError();
        return results;
    }
    
    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString email = query.value("email").toString();
        QString phoneNumber = query.value("phoneNumber").toString();
        results.append(Client(id, name, email, phoneNumber));
    }
    
    return results;
}