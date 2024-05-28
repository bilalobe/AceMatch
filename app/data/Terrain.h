#ifndef TERRAIN_H
#define TERRAIN_H

#include <QString>
#include <QList>
#include <QSqlDatabase>

class Terrain
{
public:
    Terrain(int id = -1, const QString& nom = "", const QString& type = "") : id(id), nom(nom), type(type) {} // Inline constructor
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getType() const { return type; }

private:
    int id;
    QString nom;
    QString type;
};

#endif // TERRAIN_H