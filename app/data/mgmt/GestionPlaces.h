#ifndef GESTIONPLACES_H
#define GESTIONPLACES_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include <expected>
#include "..\Place.h"
#include "Errors.h"

template<typename T>
using Result = std::expected<T, DatabaseError>;

class GestionPlaces : public QObject
{
    Q_OBJECT

public:
    GestionPlaces(const QSqlDatabase& db);
    ~GestionPlaces();

    bool ajouterPlace(const QString& nom, int capacity);
    bool supprimerPlace(int placeId);
    bool modifierPlace(int placeId, const QString& newName, int newCapacity);
    bool modifierPlaceCapacity(int placeId, int newCapacity);
    QList<Place> getPlaces() const; 
    
    // Updated to return Result<Place> for better error handling
    Result<Place> getPlaceById(int placeId) const;
    
    QList<Place> searchPlace(const QString& searchTerm) const;

signals:
    void placeFound(int id, const QString& nom, int capacity);

private:
    QSqlDatabase db;
};

#endif // GESTIONPLACES_H
