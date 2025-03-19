// PlayerManager.cpp
#include "PlayerManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

PlayerManager::PlayerManager(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

PlayerManager::~PlayerManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool PlayerManager::addJoueur(const QSqlDatabase& db, const QString& name, int rang)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO players (name, rang) VALUES (:name, :rang)");
    query.bindValue(":name", name);
    query.bindValue(":rang", rang);

    if (!query.exec()) {
        qDebug() << "Error adding player: " << query.lastError();
        return false;
    }
    return true;
}

bool PlayerManager::removeJoueur(const QSqlDatabase& db, const QString& name)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM players WHERE name = :name");
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Error removing player: " << query.lastError();
        return false;
    }
    return true;
}

bool PlayerManager::updateJoueur(const QSqlDatabase& db, const QString& name, int nouveauRang)
{
    QSqlQuery query(db);
    query.prepare("UPDATE players SET rang = :rang WHERE name = :name");
    query.bindValue(":name", name);
    query.bindValue(":rang", nouveauRang);

    if (!query.exec()) {
        qDebug() << "Error updating player: " << query.lastError();
        return false;
    }
    return true;
}

QList<Player> PlayerManager::getPlayers(const QSqlDatabase& db) const
{
    QList<Player> players;
    QSqlQuery query(db);
    query.exec("SELECT * FROM joueurs");

    while (query.next()) {
        QString name = query.value(0).toString();
        int rang = query.value(1).toInt();
        players.append(Player(name, rang));
    }

    return joueurs;
}

Player PlayerManager::getJoueurByName(const QSqlDatabase& db, const QString& name) const
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM joueurs WHERE name = :name");
    query.bindValue(":name", name);

    if (query.exec() && query.next()) {
        return Player(query.value("name").toString(), query.value("rang").toInt());
    } else {
        qDebug() << "Error getting player by name:" << query.lastError();
        return Player();
    }
}