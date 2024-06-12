#ifndef GESTION_RESERVATIONS.H
#define GESTION_RESERVATIONS.H

#include <vector>
#include "Reservation.h"
#include "Client.h"
#include "Partie.h"

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

#endif