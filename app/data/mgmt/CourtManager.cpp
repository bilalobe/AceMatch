#include "CourtManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

CourtManager::CourtManager(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

CourtManager::~CourtManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool CourtManager::addTerrain(const QSqlDatabase& db, const QString& name, const QString& type) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Terrains (name, type) VALUES (:name, :type)");
    query.bindValue(":name", name);
    query.bindValue(":type", type);

    if (!query.exec()) {
        qDebug() << "Error adding court:" << query.lastError();
        return false;
    }
    return true;
}

bool CourtManager::removeTerrain(const QSqlDatabase& db, int terrainId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Terrains WHERE id = :courtId");
    query.bindValue(":courtId", terrainId);

    if (!query.exec()) {
        qDebug() << "Error deleting court:" << query.lastError();
        return false;
    }
    return true;
}

bool CourtManager::updateTerrain(const QSqlDatabase& db, int terrainId, const QString& newName, const QString& newType) {
    QSqlQuery query(db);
    query.prepare("UPDATE Terrains SET name = :newName, type = :newType WHERE id = :courtId");
    query.bindValue(":newName", newName);
    query.bindValue(":newType", newType);
    query.bindValue(":courtId", terrainId);

    if (!query.exec()) {
        qDebug() << "Error updating court:" << query.lastError();
        return false;
    }
    return true;
}

QList<Court> CourtManager::getCourts(const QSqlDatabase& db) const {
    QList<Court> terrains;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Terrains"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString type = query.value("type").toString(); 

        terrains.append(Court(id, name, type)); 
    }
    return terrains;
}