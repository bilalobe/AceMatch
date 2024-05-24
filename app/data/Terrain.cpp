#include "Terrain.h"

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

