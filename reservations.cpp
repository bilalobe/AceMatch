#include "reservations.h"
#include "terrains.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

Reservation::Reservation(Client* client, Partie* partie, Terrain* terrain)
    : client(client), partie(partie), terrain(terrain) {}

void Reservation::afficher() const {
    cout << "Client: " << client->getNom() << endl;
    cout << "Match: " << partie->getNomJoueur1() << " vs. " << partie->getNomJoueur2() << endl;
    cout << "Terrain: " << terrain->getType() << endl;
}
// Getters for Reservation
Client* Reservation::getClient() const {
  return client;
}
Partie* Reservation::getPartie() const {
  return partie;
}

// Add a reservation
void GestionReservations::ajouterReservation(const Reservation& reservation) {
  reservations.push_back(reservation);
}

// Remove a reservation
void GestionReservations::supprimerReservation(Client* client, Partie* partie) {
  auto it = std::find_if(reservations.begin(), reservations.end(), 
                         [&client, &partie](const Reservation& res) {
                           return res.getClient() == client && res.getPartie() == partie;
                         });
  if (it != reservations.end()) {
    reservations.erase(it);
  }
}

// Search for a reservation
Reservation* GestionReservations::rechercherReservation(Client* client, Partie* partie) {
  auto it = std::find_if(reservations.begin(), reservations.end(),
                         [&client, &partie](const Reservation& res) {
                           return res.getClient() == client && res.getPartie() == partie;
                         });
  if (it != reservations.end()) {
    return &(*it); // Return a pointer to the found Reservation
  }
  return nullptr;
}

// Get the list of reservations
const vector<Reservation>& GestionReservations::getReservations() const {
  return reservations;
}

// Sort reservations by client name
void GestionReservations::trierReservationsParClient() {
  sort(reservations.begin(), reservations.end(), [](const Reservation& a, const Reservation& b) {
    return a.getClient()->getNom() < b.getClient()->getNom();
  });
}

void Reservation::afficher() const {
    cout << "Client: " << client->getNom() << endl;
    cout << "Match: " << partie->getNomJoueur1() << " vs. " << partie->getNomJoueur2() << endl;
    cout << "Terrain: " << terrain->getType() << endl;
}