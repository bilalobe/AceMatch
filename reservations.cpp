#include "reservations.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "joueurs.h" 
#include "parties.h" 
#include "places.h" 

using namespace std;

// Constructor for Reservation
Reservation::Reservation(Joueur* joueur, Partie* partie, Place* place)
    : joueur(joueur), partie(partie), place(place) {}

// Getters for Reservation
Joueur* Reservation::getJoueur() const {
  return joueur;
}
Partie* Reservation::getPartie() const {
  return partie;
}
Place* Reservation::getPlace() const {
  return place;
}

// Setters for Reservation
void Reservation::setJoueur(Joueur* joueur) {
  this->joueur = joueur;
}
void Reservation::setPartie(Partie* partie) {
  this->partie = partie;
}
void Reservation::setPlace(Place* place) {
  this->place = place;
}

// GestionReservations implementation
GestionReservations::GestionReservations() {}

// Add a reservation
void GestionReservations::ajouterReservation(Reservation reservation) {
  reservations.push_back(reservation);
}

// Remove a reservation
void GestionReservations::supprimerReservation(Joueur* joueur, Partie* partie, Place* place) {
  for (int i = 0; i < reservations.size(); i++) {
    if (reservations[i].getJoueur() == joueur && reservations[i].getPartie() == partie &&
        reservations[i].getPlace() == place) {
      reservations.erase(reservations.begin() + i);
      break;
    }
  }
}

// Search for a reservation
Reservation* GestionReservations::rechercherReservation(Joueur* joueur, Partie* partie, Place* place) {
  for (int i = 0; i < reservations.size(); i++) {
    if (reservations[i].getJoueur() == joueur && reservations[i].getPartie() == partie &&
        reservations[i].getPlace() == place) {
      return &reservations[i];
    }
  }
  return nullptr;
}

// Get the list of reservations
const vector<Reservation>& GestionReservations::getReservations() const {
  return reservations;
}

// Sort reservations by player name
void GestionReservations::trierReservationsParJoueur() {
  sort(reservations.begin(), reservations.end(), [](const Reservation& a, const Reservation& b) {
    return a.getJoueur()->getNom() < b.getJoueur()->getNom();
  });
}