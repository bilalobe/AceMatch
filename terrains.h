#ifndef TERRAINS_H
#define TERRAINS_H

#include <iostream>
#include <vector>

using namespace std;

enum TypeTerrain {
   TERRE_BATTUE,
    DUR,
    SYNTHETIQUE
};

class Terrain {
public:
  TypeTerrain type;
  int capacite;
  int x;
  int y;


   Terrain(TypeTerrain type, int x, int y) : type(type), x(x), y(y), capacite(0) {
    switch(type) {
    case TERRE_BATTUE: capacite = 50; break;
    case DUR: capacite = 30; break;
    case SYNTHETIQUE: capacite = 150; break;
    }
   }
  int getCapacite() const { 
        return capacite;
    }
  void setX(int x) {
    this->x = x;
  }

  int getX() const {
    return x;
  }

  void setY(int y) {
    this->y = y;
  }

  int getY() const {
    return y;
  }

  void afficher() {
    cout << "Type: " << type << endl;
    cout << "Position: (" << x << ", " << y << ")" << endl;
  }
};

class GestionTerrains {
public:
  vector<Terrain> terrains;

  void ajouterTerrain(Terrain terrain) {
    terrains.push_back(terrain);
  }

  void supprimerTerrain(int x, int y) {
    for (int i = 0; i < terrains.size(); i++) {
      if (terrains[i].getX() == x && terrains[i].getY() == y) {
        terrains.erase(terrains.begin() + i);
        break;
      }
    }
  }

  void afficherTerrains() {
    for (Terrain terrain : terrains) {
      terrain.afficher();
      cout << endl;
    }
  }
};

#endif