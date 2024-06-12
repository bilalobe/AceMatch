#ifndef GESTION_TERRAINS.H
#define GESTION_TERRAINS.H

#include "Terrain.h"

class GestionTerrains
{
private:
  std::vector<Terrain> terrains;

public:
  void ajouterTerrain(Terrain terrain);
  void afficherTerrains();
  bool supprimerTerrain(TypeTerrain type, int longueur, int largeur);
  Terrain *rechercherTerrain(TypeTerrain type, int longueur, int largeur) const;
};


#endif // GESTION_TERRAINS.H