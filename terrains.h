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
  Terrain(TypeTerrain type, int longueur, int largeur) : type(type), longueur(longueur), largeur(largeur) {}

  void afficher() {
    cout << "Type: " << (type == DUR ? "Dur" : type == TERRE_BATTUE ? "Terre battue" : "Gazon") << endl;
    cout << "Longueur: " << longueur << endl;
    cout << "Largeur: " << largeur << endl;
  }
};

class GestionTerrains {
public:
  vector<Terrain> terrains;

  void ajouterTerrain(Terrain terrain) {
    terrains.push_back(terrain);
  }

  void afficherTerrains() {
    for (Terrain terrain : terrains) {
      terrain.afficher();
      cout << endl;
    }
  }

  void supprimerTerrain(TypeTerrain type, int longueur, int largeur) {
    for (int i = 0; i < terrains.size(); i++) {
      if (terrains[i].type == type && terrains[i].longueur == longueur && terrains[i].largeur == largeur) {
        terrains.erase(terrains.begin() + i);
        break;
      }
    }
  }
};

#endif
