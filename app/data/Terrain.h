#ifndef TERRAIN_H
#define TERRAIN_H

#include <QString>
#include <QList>
#include <QSqlDatabase>

class Terrain
{
public:
    Terrain(int id = -1, const QString& nom = "", const QString& type = "");
    int getId() const { return id; }
    QString getNomType() const { return nom + " (" + type + ")"; }


private:
    int id;
    QString nom;
    QString type;
};

#endif // TERRAINS_H