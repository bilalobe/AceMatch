#include "GestionClients.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionClients::GestionClients(const QSqlDatabase& db)
    : db(db)
{
    // Database is now stored as a member variable
}

GestionClients::~GestionClients()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionClients::ajouterClient(const QString& nom, const QString& email, const QString& phoneNumber) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Clients (nom, email, phoneNumber) VALUES (:nom, :email, :phoneNumber)");
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":phoneNumber", phoneNumber);

    if (!query.exec()) {
        qDebug() << "Error adding client:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionClients::supprimerClient(int clientId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Clients WHERE id = :clientId");
    query.bindValue(":clientId", clientId);

    if (!query.exec()) {
        qDebug() << "Error deleting client:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionClients::modifierClient(int clientId, const QString& newName, const QString& newEmail, const QString& newPhoneNumber) {
    QSqlQuery query(db);
    query.prepare("UPDATE Clients SET nom = :newName, email = :newEmail, phoneNumber = :newPhoneNumber WHERE id = :clientId");
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

QList<Client> GestionClients::getClients() const {
    QList<Client> clients;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Clients");

    while (query.next()) {
        int id = query.value("id").toInt();
        QString nom = query.value("nom").toString();
        QString email = query.value("email").toString();
        QString phoneNumber = query.value("phoneNumber").toString();

        clients.append(Client(id, nom, email, phoneNumber));
    }
    return clients;
}

Client GestionClients::getClientById(int clientId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Clients WHERE id = :clientId");
    query.bindValue(":clientId", clientId);

    if (query.exec() && query.next()) {
        return Client(query.value("id").toInt(), query.value("nom").toString(), query.value("email").toString(), query.value("phoneNumber").toString());
    } else {
        qDebug() << "Error getting client by ID:" << query.lastError();
        return Client();
    }
}

QList<Client> GestionClients::searchClients(const QString& searchTerm) const {
    QList<Client> results;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Clients WHERE nom LIKE :term OR email LIKE :term OR phoneNumber LIKE :term");
    query.bindValue(":term", "%" + searchTerm + "%");
    
    if (!query.exec()) {
        qDebug() << "Error searching clients:" << query.lastError();
        return results;
    }
    
    while (query.next()) {
        int id = query.value("id").toInt();
        QString nom = query.value("nom").toString();
        QString email = query.value("email").toString();
        QString phoneNumber = query.value("phoneNumber").toString();
        results.append(Client(id, nom, email, phoneNumber));
    }
    
    return results;
}