// GestionClients.h
#ifndef GESTIONCLIENTS_H
#define GESTIONCLIENTS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Client.h"

class GestionClients
{
public:
    GestionClients(const QSqlDatabase& db);
    ~GestionClients();

    bool ajouterClient(const QSqlDatabase& db, const QString& nom, const QString& email, const QString& phoneNumber);
    bool supprimerClient(const QSqlDatabase& db, int clientId); 
    bool modifierClient(const QSqlDatabase& db, int clientId, const QString& newName, const QString& newEmail, const QString& newPhoneNumber);
    void searchClient(const QSqlDatabase& db, const QString& searchTerm);
    QList<Client> getClients(const QSqlDatabase& db) const; 
    Client getClientById(const QSqlDatabase& db, int clientId) const; 
};

#endif // GESTIONCLIENTS_H