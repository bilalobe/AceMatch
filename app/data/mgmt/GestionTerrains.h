#ifndef GESTIONTERRAINS_H
#define GESTIONTERRAINS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Terrain.h" 

class GestionTerrains
{
public:
    GestionTerrains(const QSqlDatabase& db);
    ~GestionTerrains();

    bool ajouterTerrain(const QSqlDatabase& db, const QString& nom, const QString& type);
    bool supprimerTerrain(const QSqlDatabase& db, int terrainId); 
    bool modifierTerrain(const QSqlDatabase& db, int terrainId, const QString& newName, const QString& newType);
    QList<Terrain> getTerrains(const QSqlDatabase& db) const; 
};

#endif // GESTIONTERRAINS_H