#ifndef GESTIONPLACES_H
#define GESTIONPLACES_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "..\Place.h"

class GestionPlaces
{
public:
    GestionPlaces(const QSqlDatabase& db);
    ~GestionPlaces();

    bool ajouterPlace(const QSqlDatabase& db, const QString& nom, int capacity);
    bool supprimerPlace(const QSqlDatabase& db, int placeId);
    bool modifierPlace(const QSqlDatabase& db, int placeId, const QString& newName, int newCapacity);
    bool modifierPlaceCapacity(const QSqlDatabase& db, int placeId, int newCapacity);
    void searchPlace(const QSqlDatabase& db, const QString& searchTerm);
    QList<Place> getPlaces(const QSqlDatabase& db) const; 
    Place getPlaceById(const QSqlDatabase& db, int placeId) const;

private:
    // QSqlDatabase db; // No need for this member anymore, as the database is passed as an argument

};

#endif // GESTIONPLACES_H
