#include "GestionTerrains.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionTerrains::GestionTerrains(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

GestionTerrains::~GestionTerrains()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionTerrains::ajouterTerrain(const QSqlDatabase& db, const QString& nom, const QString& type) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Terrains (nom, type) VALUES (:nom, :type)");
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);

    if (!query.exec()) {
        qDebug() << "Error adding terrain:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionTerrains::supprimerTerrain(const QSqlDatabase& db, int terrainId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Terrains WHERE id = :terrainId");
    query.bindValue(":terrainId", terrainId);

    if (!query.exec()) {
        qDebug() << "Error deleting terrain:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionTerrains::modifierTerrain(const QSqlDatabase& db, int terrainId, const QString& newName, const QString& newType) {
    QSqlQuery query(db);
    query.prepare("UPDATE Terrains SET nom = :newName, type = :newType WHERE id = :terrainId");
    query.bindValue(":newName", newName);
    query.bindValue(":newType", newType);
    query.bindValue(":terrainId", terrainId);

    if (!query.exec()) {
        qDebug() << "Error updating terrain:" << query.lastError();
        return false;
    }
    return true;
}

QList<Terrain> GestionTerrains::getTerrains(const QSqlDatabase& db) const {
    QList<Terrain> terrains;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Terrains"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        QString nom = query.value("nom").toString();
        QString type = query.value("type").toString(); 

        terrains.append(Terrain(id, nom, type)); 
    }
    return terrains;
}