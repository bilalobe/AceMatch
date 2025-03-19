#include "GestionPlaces.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionPlaces::GestionPlaces(const QSqlDatabase &db)
    : db(db)
{
    // Database is now stored as a member variable
}

GestionPlaces::~GestionPlaces()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionPlaces::ajouterPlace(const QString &nom, int capacity)
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

bool GestionPlaces::supprimerPlace(int placeId)
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

bool GestionPlaces::modifierPlace(int placeId, const QString &newName, int newCapacity)
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

bool GestionPlaces::modifierPlaceCapacity(int placeId, int newCapacity)
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

QList<Place> GestionPlaces::getPlaces() const
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

Result<Place> GestionPlaces::getPlaceById(int placeId) const
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Places WHERE id = :placeId");
    query.bindValue(":placeId", placeId);

    if (!query.exec()) {
        qDebug() << "Error querying place:" << query.lastError();
        return std::unexpected(QueryError("SELECT FROM Places", query.lastError().text().toStdString()));
    }
    
    if (!query.next()) {
        return std::unexpected(NotFoundError("Place", placeId));
    }
    
    return Place(
        query.value("id").toInt(),
        query.value("nom").toString(),
        query.value("capacity").toInt()
    );
}

QList<Place> GestionPlaces::searchPlace(const QString &searchText) const
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
            emit placeFound(id, nom, capacity);
        }
    }
    else
    {
        qDebug() << "Error searching places:" << query.lastError();
    }

    return places;
}
