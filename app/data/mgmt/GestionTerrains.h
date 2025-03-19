#ifndef GESTIONTERRAINS_H
#define GESTIONTERRAINS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Terrain.h"

class GestionTerrains : public QObject
{
    Q_OBJECT

public:
    GestionTerrains(const QSqlDatabase& db);
    ~GestionTerrains();

    bool ajouterTerrain(const QString& nom, const QString& type);
    bool supprimerTerrain(int terrainId); 
    bool modifierTerrain(int terrainId, const QString& newName, const QString& newType);
    QList<Terrain> getTerrains() const;
    Terrain getTerrainById(int terrainId) const;
    QList<Terrain> searchTerrains(const QString& searchTerm) const;

signals:
    void terrainAdded(int id, const QString& nom, const QString& type);
    void terrainUpdated(int id, const QString& nom, const QString& type);
    void terrainDeleted(int id);
    void terrainFound(int id, const QString& nom, const QString& type);

private:
    QSqlDatabase db;
};

#endif // GESTIONTERRAINS_H
