#ifndef GESTIONCLIENTS_H
#define GESTIONCLIENTS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Client.h"

class GestionClients : public QObject
{
    Q_OBJECT

public:
    GestionClients(const QSqlDatabase& db);
    ~GestionClients();

    bool ajouterClient(const QString& nom, const QString& email, const QString& phoneNumber);
    bool supprimerClient(int clientId); 
    bool modifierClient(int clientId, const QString& newName, const QString& newEmail, const QString& newPhoneNumber);
    QList<Client> getClients() const; 
    Client getClientById(int clientId) const;
    QList<Client> searchClients(const QString& searchTerm) const;

signals:
    void clientAdded(int id, const QString& nom, const QString& email, const QString& phoneNumber);
    void clientDeleted(int id);
    void clientUpdated(int id, const QString& newName, const QString& newEmail, const QString& newPhoneNumber);
    void clientFound(int id, const QString& nom, const QString& email, const QString& phoneNumber);

private:
    QSqlDatabase db;
};

#endif // GESTIONCLIENTS_H
