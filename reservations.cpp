#include "reservations.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor
Reservation::Reservation(Client* client, Partie* partie, Terrain* terrain, int row, int col)
    : client(client), partie(partie), terrain(terrain), row(row), col(col) {}

// Getter methods
Client* Reservation::getClient() const {
    return client;
}

Partie* Reservation::getPartie() const {
    return partie;
}

Terrain* Reservation::getTerrain() const {
    return terrain;
}

int Reservation::getRow() const {
    return row;
}

int Reservation::getCol() const {
    return col;
}

// Display reservation details
void Reservation::afficher() const {
    cout << "Client: " << client->getNom() << endl;
    cout << "Match: " << partie->getNomJoueur1() << " vs. " << partie->getNomJoueur2() << endl;
    cout << "Terrain: " << terrain->getType() << endl;
    cout << "Row: " << row << endl;
    cout << "Column: " << col << endl;
}

// Add a reservation
void GestionReservations::ajouterReservation(const Reservation& reservation) {
    reservations.push_back(reservation);
}

 void GestionReservations::supprimerReservation(Client* client, Partie* partie, int row, int col) {
   auto it = std::find_if(reservations.begin(), reservations.end(),
                          [&client, &partie, row, col](const Reservation& res) {
                            return res.getClient() == client && res.getPartie() == partie && res.getRow() == row && res.getCol() == col;
                          });
   if (it != reservations.end()) {
     // Release the seat in the Terrain
     it->getTerrain()->releaseSeat(row, col);
     reservations.erase(it);
   }
 }

 // Search for a reservation
 Reservation* GestionReservations::rechercherReservation(Client* client, Partie* partie, int row, int col) {
   auto it = std::find_if(reservations.begin(), reservations.end(),
                          [&client, &partie, row, col](const Reservation& res) {
                            return res.getClient() == client && res.getPartie() == partie && res.getRow() == row && res.getCol() == col;
                          });
   if (it != reservations.end()) {
     return &(*it); // Return a pointer to the found Reservation
   }
   return nullptr;
 }
// Display all reservations
void GestionReservations::afficherReservations() const {
    for (const auto& reservation : reservations) {
        reservation.afficher();
        cout << endl;
    }
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
