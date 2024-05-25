#include "Terrain.h"

Terrain::Terrain(int id, const QString& nom, const QString& type) :
    id(id),
    nom(nom),
    type(type)
{
}

int Terrain::getId() const
{
    return id;
}


QString Terrain::getNomType() const
{
    return nom + " (" + type + ")";
}