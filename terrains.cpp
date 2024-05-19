#include "terrains.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constructor with type, length, and width
Terrain::Terrain(TypeTerrain type, int longueur, int largeur)
    : type(type), longueur(longueur), largeur(largeur), nbPlacesReservees(0) {
    initializeSeatingPlan(longueur, largeur); // Initialize seating plan based on terrain size
}

// Constructor with type, length, width, and reserved seats
Terrain::Terrain(TypeTerrain type, int longueur, int largeur, int nbPlacesReservees)
    : type(type), longueur(longueur), largeur(largeur), nbPlacesReservees(nbPlacesReservees) {
    initializeSeatingPlan(longueur, largeur); // Initialize seating plan based on terrain size
}

// Getter for type
TypeTerrain Terrain::getType() const {
    return type;
}

// Getter for length
int Terrain::getLongueur() const {
    return longueur;
}

// Getter for width
int Terrain::getLargeur() const {
    return largeur;
}

// Getter for reserved seats
int Terrain::getNbPlacesReservees() const {
    return nbPlacesReservees;
}

// Setter for length
void Terrain::setLongueur(int longueur) {
    this->longueur = longueur;
    initializeSeatingPlan(this->longueur, this->largeur); // Reinitialize seating plan
}

// Setter for width
void Terrain::setLargeur(int largeur) {
    this->largeur = largeur;
    initializeSeatingPlan(this->longueur, this->largeur); // Reinitialize seating plan
}

// Setter for reserved seats
void Terrain::setNbPlacesReservees(int nbPlacesReservees) {
    this->nbPlacesReservees = nbPlacesReservees;
}

// Setter for all attributes except reserved seats
void Terrain::setTerrain(TypeTerrain type, int longueur, int largeur) {
    this->type = type;
    this->longueur = longueur;
    this->largeur = largeur;
    initializeSeatingPlan(longueur, largeur); // Reinitialize seating plan
}

// Setter for all attributes including reserved seats
void Terrain::setTerrain(TypeTerrain type, int longueur, int largeur, int nbPlacesReservees) {
    this->type = type;
    this->longueur = longueur;
    this->largeur = largeur;
    this->nbPlacesReservees = nbPlacesReservees;
    initializeSeatingPlan(longueur, largeur); // Reinitialize seating plan
}

// Display terrain details
void Terrain::afficher() const {
    cout << "Type de terrain: " << (type == DUR ? "Dur" : (type == TERRE_BATTUE ? "Terre battue" : "Gazon")) << endl;
    cout << "Longueur: " << longueur << endl;
    cout << "Largeur: " << largeur << endl;
    cout << "Nombre de places réservées: " << nbPlacesReservees << endl;
}

#include "terrains.h"
#include <iostream>

Terrain::Terrain(TypeTerrain type, int longueur, int largeur)
    : type(type), longueur(longueur), largeur(largeur) {}


// GestionTerrains methods

// Add a terrain
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
        if (it->getType() == type && it->getLongueur() == longueur && it->getLargeur() == largeur) {
            terrains.erase(it);
            return true; // Terrain found and deleted
        }
    }
    return false; // Terrain not found
}

// Search for a terrain
Terrain* GestionTerrains::rechercherTerrain(TypeTerrain type, int longueur, int largeur) const {
    for (const auto& terrain : terrains) {
        if (terrain.getType() == type && terrain.getLongueur() == longueur && terrain.getLargeur() == largeur) {
            return const_cast<Terrain*>(&terrain);
        }
    }
    return nullptr;
}
