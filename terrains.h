#ifndef TERRAINS_H
#define TERRAINS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum TypeTerrain {
  DUR,
  TERRE_BATTUE,
  GAZON
};

class Terrain {
public:
  TypeTerrain type;
  int longueur;
  int largeur;

public:
  Terrain(TypeTerrain type, int longueur, int largeur);
  void afficher(); 
};

class GestionTerrains {
public:
  vector<Terrain> terrains;
  void ajouterTerrain(Terrain terrain);
  void afficherTerrains();
  bool supprimerTerrain(TypeTerrain type, int longueur, int largeur);
  Terrain* rechercherTerrain(TypeTerrain type, int longueur, int largeur) const; 
};

#endif