#ifndef GESTIONTERRAINS_H
#define GESTIONTERRAINS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Court.h"

class CourtManager : public QObject
{
    Q_OBJECT

public:
    CourtManager(const QSqlDatabase& db);
    ~CourtManager();

    bool addTerrain(const QString& name, const QString& type);
    bool removeTerrain(int terrainId); 
    bool updateTerrain(int terrainId, const QString& newName, const QString& newType);
    QList<Court> getCourts() const;
    Court getCourtById(int terrainId) const;
    QList<Court> searchTerrains(const QString& searchTerm) const;

signals:
    void terrainAdded(int id, const QString& name, const QString& type);
    void terrainUpdated(int id, const QString& name, const QString& type);
    void terrainDeleted(int id);
    void terrainFound(int id, const QString& name, const QString& type);

private:
    QSqlDatabase db;
};

#endif // GESTIONTERRAINS_H
