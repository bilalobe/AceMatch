#include "terrains.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constructor with type, length, and width
Terrain::Terrain(TypeTerrain type, int longueur, int largeur) : 
  type(type), longueur(longueur), largeur(largeur), nbPlacesReservees(0) {
  initializeSeatingPlan(longueur, largeur); // Initialize seating plan based on terrain size
}

// Constructor with type, length, width, and reserved seats
Terrain::Terrain(TypeTerrain type, int longueur, int largeur, int nbPlacesReservees) :
  type(type), longueur(longueur), largeur(largeur), nbPlacesReservees(nbPlacesReservees) {
  initializeSeatingPlan(longueur, largeur); // Initialize seating plan based on terrain size
}

// Getter for type
TypeTerrain Terrain::getType() const {
  return type;
}

// Getters for dimensions and reserved seats
void Terrain::getLongueur(int& longueur) const {
  longueur = this->longueur;
}

void Terrain::getLargeur(int& largeur) const {
  largeur = this->largeur;
}

void Terrain::getNbPlacesReservees(int& nbPlacesReservees) const {
  nbPlacesReservees = this->nbPlacesReservees;
}

// Setters for dimensions and reserved seats
void Terrain::setLongueur(int longueur) {
  this->longueur = longueur;
  initializeSeatingPlan(this->longueur, this->largeur); // Reinitialize seating plan
}

void Terrain::setLargeur(int largeur) {
  this->largeur = largeur;
  initializeSeatingPlan(this->longueur, this->largeur); // Reinitialize seating plan
}

void Terrain::setNbPlacesReservees(int nbPlacesReservees) {
  this->nbPlacesReservees = nbPlacesReservees;
}

void Terrain::setTerrain(TypeTerrain type, int longueur, int largeur) {
  this->type = type;
  this->longueur = longueur;
  this->largeur = largeur;
  initializeSeatingPlan(longueur, largeur); // Reinitialize seating plan
}

void Terrain::setTerrain(TypeTerrain type, int longueur, int largeur, int nbPlacesReservees) {
  this->type = type;
  this->longueur = longueur;
  this->largeur = largeur;
  this->nbPlacesReservees = nbPlacesReservees;
  initializeSeatingPlan(longueur, largeur); // Reinitialize seating plan
}



void Terrain::afficher() const {
  cout << "Type de terrain: " << (type == DUR ? "Dur" : (type == TERRE_BATTUE ? "Terre battue" : "Gazon")) << endl;
  cout << "Longueur: " << longueur << endl;
  cout << "Largeur: " << largeur << endl;
  cout << "Nombre de places réservées: " << nbPlacesReservees << endl;
}

// Seating plan methods
void Terrain::initializeSeatingPlan(int rows, int cols) {
  seatingPlan.resize(rows);
  for (int i = 0; i < rows; ++i) {
    seatingPlan[i].resize(cols, false); // Initially, all seats are available
  }
}

bool Terrain::isSeatAvailable(int row, int col) const {
  if (row < 0 || row >= seatingPlan.size() || col < 0 || col >= seatingPlan[0].size()) {
    return false; 
  }
  return !seatingPlan[row][col]; // true if the seat is available (not reserved)
}

void Terrain::reserveSeat(int row, int col) {
  if (isSeatAvailable(row, col)) {
    seatingPlan[row][col] = true;
    ++nbPlacesReservees;
  }
}

void Terrain::releaseSeat(int row, int col) {
  if (!isSeatAvailable(row, col)) {
    seatingPlan[row][col] = false; 
    --nbPlacesReservees;
  }
}

// GestionTerrains methods
void GestionTerrains::ajouterTerrain(Terrain terrain) {
  terrains.push_back(terrain);
}

// Display all terrains
void GestionTerrains::afficherTerrains() {
  for (const Terrain& terrain : terrains) {
    terrain.afficher();
    cout << endl;
  }
}

// Remove a terrain
bool GestionTerrains::supprimerTerrain(TypeTerrain type, int longueur, int largeur) {
  for (auto it = terrains.begin(); it != terrains.end(); ++it) {
    int tLongueur, tLargeur;
    it->getLongueur(tLongueur);
    it->getLargeur(tLargeur);
    if (it->getType() == type && tLongueur == longueur && tLargeur == largeur) {
      terrains.erase(it);
      return true; // Terrain found and deleted
    }
  }
  return false; // Terrain not found
}

// Search for a terrain
Terrain* GestionTerrains::rechercherTerrain(TypeTerrain type, int longueur, int largeur) const {
  for (const auto& terrain : terrains) {
    int tLongueur, tLargeur;
    terrain.getLongueur(tLongueur);
    terrain.getLargeur(tLargeur);
    if (terrain.getType() == type && tLongueur == longueur && tLargeur == largeur) {
      return const_cast<Terrain*>(&terrain);
    }
  }
  return nullptr; 
}
