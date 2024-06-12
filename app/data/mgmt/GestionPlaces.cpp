#include "GestionPlaces.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionPlaces::GestionPlaces(const QSqlDatabase &db)
// : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

GestionPlaces::~GestionPlaces()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionPlaces::ajouterPlace(const QSqlDatabase &db, const QString &nom, int capacity)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO Places (nom, capacity) VALUES (:nom, :capacity)");
    query.bindValue(":nom", nom);
    query.bindValue(":capacity", capacity);

    if (!query.exec())
    {
        qDebug() << "Error adding place: " << query.lastError();
        return false;
    }
    return true;
}

bool GestionPlaces::supprimerPlace(const QSqlDatabase &db, int placeId)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM Places WHERE id = :placeId");
    query.bindValue(":placeId", placeId);

    if (!query.exec())
    {
        qDebug() << "Error removing place: " << query.lastError();
        return false;
    }
    return true;
}

bool GestionPlaces::modifierPlace(const QSqlDatabase &db, int placeId, const QString &newName, int newCapacity)
{
    QSqlQuery query(db);
    query.prepare("UPDATE Places SET nom = :newName, capacity = :newCapacity WHERE id = :placeId");
    query.bindValue(":newName", newName);
    query.bindValue(":newCapacity", newCapacity);
    query.bindValue(":placeId", placeId);

    if (!query.exec())
    {
        qDebug() << "Error updating place: " << query.lastError();
        return false;
    }
    return true;
}

bool GestionPlaces::modifierPlaceCapacity(const QSqlDatabase & db, int placeId, int newCapacity)
{
       QSqlQuery query(db);
    query.prepare("UPDATE Places SET capacity = :newCapacity WHERE id = :placeId");
    query.bindValue(":newCapacity", newCapacity);
    query.bindValue(":placeId", placeId);

    if (!query.exec())
    {
        qDebug() << "Error updating place capacity: " << query.lastError();
        return false;
    }
    return true;
}



QList<Place> GestionPlaces::getPlaces(const QSqlDatabase &db) const
{
    QList<Place> places;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Places");

    while (query.next())
    {
        int id = query.value("id").toInt();
        QString nom = query.value("nom").toString();
        int capacity = query.value("capacity").toInt();

        places.append(Place(id, nom, capacity));
    }

    return places;
}

Place GestionPlaces::getPlaceById(const QSqlDatabase &db, int placeId) const
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Places WHERE id = :placeId");
    query.bindValue(":placeId", placeId);

    if (query.exec() && query.next())
    {
        return Place(query.value("id").toInt(), query.value("nom").toString(), query.value("capacity").toInt());
    }
    else
    {
        qDebug() << "Error getting place by ID:" << query.lastError();
        return Place();
    }
}

GestionPlaces::searchPlace(const QSqlDatabase &db, const QString &searchText) const
{
    QList<Place> places;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Places WHERE nom LIKE :searchText OR capacity LIKE :searchText");
    query.bindValue(":searchText", "%" + searchText + "%");

    if (query.exec())
    {
        while (query.next())
        {
            int id = query.value("id").toInt();
            QString nom = query.value("nom").toString();
            int capacity = query.value("capacity").toInt();

            places.append(Place(id, nom, capacity));
        }
    }
    else
    {
        qDebug() << "Error searching places:" << query.lastError();
    }

    return places;
}
