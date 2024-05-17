#include "reservations.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Constructor for Reservation
Reservation::Reservation(Client* client, Partie* partie)
    : client(client), partie(partie) {}

// Getters for Reservation
Client* Reservation::getClient() const {
  return client;
}
Partie* Reservation::getPartie() const {
  return partie;
}


// GestionReservations implementation
GestionReservations::GestionReservations() {}

// Add a reservation
void GestionReservations::ajouterReservation(Reservation reservation) {
  reservations.push_back(reservation);
}

// Remove a reservation
void GestionReservations::supprimerReservation(Client* client, Partie* partie) {
  for (int i = 0; i < reservations.size(); i++) {
    if (reservations[i].getClient() == client && reservations[i].getPartie() == partie) {
      reservations.erase(reservations.begin() + i);
      break;
    }
  }
}

// Search for a reservation
Reservation* GestionReservations::rechercherReservation(Client* client, Partie* partie) {
  for (int i = 0; i < reservations.size(); i++) {
    if (reservations[i].getClient() == client && reservations[i].getPartie() == partie) {
      return &reservations[i];
    }
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
    return a.getClient()->nom < b.getClient()->nom;
  });
}