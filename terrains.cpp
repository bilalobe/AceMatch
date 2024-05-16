#include "terrains.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constructor for Terrain
Terrain::Terrain(TypeTerrain type, int longueur, int largeur)
    : type(type), longueur(longueur), largeur(largeur) {}

// Display a terrain's details
void Terrain::afficher() {
  cout << "Type: " << (type == DUR ? "Dur" : type == TERRE_BATTUE ? "Terre battue" : "Gazon") << endl;
  cout << "Longueur: " << longueur << endl;
  cout << "Largeur: " << largeur << endl;
}

// GestionTerrains implementation
GestionTerrains::GestionTerrains() {}

// Add a terrain
void GestionTerrains::ajouterTerrain(Terrain terrain) {
  terrains.push_back(terrain);
}

// Display all terrains
void GestionTerrains::afficherTerrains() {
  for (Terrain terrain : terrains) {
    terrain.afficher();
    cout << endl;
  }
}

// Remove a terrain
bool GestionTerrains::supprimerTerrain(TypeTerrain type, int longueur, int largeur) {
  for (int i = 0; i < terrains.size(); i++) {
    if (terrains[i].type == type && terrains[i].longueur == longueur && terrains[i].largeur == largeur) {
      terrains.erase(terrains.begin() + i);
      return true; // Terrain found and deleted
    }
  }
  return false; // Terrain not found
}

// Search for a terrain
Terrain* GestionTerrains::rechercherTerrain(TypeTerrain type, int longueur, int largeur) const {
  for (int i = 0; i < terrains.size(); i++) {
    if (terrains[i].type == type && terrains[i].longueur == longueur && terrains[i].largeur == largeur) {
      return const_cast<Terrain*>(&terrains[i]);
    }
  }
  return nullptr; 
}