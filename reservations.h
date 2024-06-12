#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include "places.h"
#include "clients.h"
#include "parties.h"
#include "terrains.h"
#include <string>
#include <vector>

class Reservation {
public:
    Reservation(Client* client, Partie* partie, Terrain* terrain, int row, int col);

    // Getters
    Client* getClient() const;
    Partie* getPartie() const;
    Terrain* getTerrain() const;
    int getRow() const;
    int getCol() const;

    // Display reservation details
    void afficher() const;

private:
    Client* client;
    Partie* partie;
    Terrain* terrain;
    int row;
    int col;
};

class GestionReservations {
private:
    std::vector<Reservation> reservations;

public:
    // Constructor
    GestionReservations() {}

    // Add a reservation
    void ajouterReservation(const Reservation& reservation);

    // Remove a reservation
    void supprimerReservation(Client* client, Partie* partie, int row, int col);

    // Search for a reservation
    Reservation* rechercherReservation(Client* client, Partie* partie, int row, int col);

    // Display all reservations
    void afficherReservations() const;

    // Get the list of reservations
    const std::vector<Reservation>& getReservations() const;

    // Sort reservations by client name
    void trierReservationsParClient();
};

#endif // RESERVATIONS_H
