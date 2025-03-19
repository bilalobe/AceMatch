#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Client.h"

class ClientManager : public QObject
{
    Q_OBJECT

public:
    ClientManager(const QSqlDatabase& db);
    ~ClientManager();

    bool addClient(const QString& name, const QString& email, const QString& phoneNumber);
    bool removeClient(int clientId); 
    bool updateClient(int clientId, const QString& newName, const QString& newEmail, const QString& newPhoneNumber);
    QList<Client> getClients() const; 
    Client getClientById(int clientId) const;
    QList<Client> searchClients(const QString& searchTerm) const;

signals:
    void clientAdded(int id, const QString& name, const QString& email, const QString& phoneNumber);
    void clientDeleted(int id);
    void clientUpdated(int id, const QString& newName, const QString& newEmail, const QString& newPhoneNumber);
    void clientFound(int id, const QString& name, const QString& email, const QString& phoneNumber);

private:
    QSqlDatabase db;
};

#endif // CLIENTMANAGER_H
