// GestionClients.cpp
#include "GestionClients.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionClients::GestionClients(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

GestionClients::~GestionClients()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionClients::ajouterClient(const QSqlDatabase& db, const QString& nom, const QString& email, const QString& phoneNumber) {
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

bool GestionClients::supprimerClient(const QSqlDatabase& db, int clientId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Clients WHERE id = :clientId");
    query.bindValue(":clientId", clientId);

    if (!query.exec()) {
        qDebug() << "Error deleting client:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionClients::modifierClient(const QSqlDatabase& db, int clientId, const QString& newName, const QString& newEmail, const QString& newPhoneNumber) {
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

void GestionClients::searchClient(const QSqlDatabase &db, const QString &searchTerm)
{
        QSqlQuery query(db);
    query.prepare("SELECT * FROM Clients WHERE nom LIKE :searchTerm OR email LIKE :searchTerm OR phoneNumber LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error searching client:" << query.lastError();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString nom = query.value("nom").toString();
        QString email = query.value("email").toString();
        QString phoneNumber = query.value("phoneNumber").toString();

        // Emit a signal to notify the UI about the found client
        emit clientFound(id, nom, email, phoneNumber);
    }
}

QList<Client> GestionClients::getClients(const QSqlDatabase& db) const {
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

Client GestionClients::getClientById(const QSqlDatabase& db, int clientId) const {
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

