#ifndef RESERVATIONS_H
#define RESERVATIONS_H
#include "places.h"
#include "clients.h"
#include "parties.h"
#include <string>
#include <vector>

using namespace std;

class Reservation {
public:
    Reservation(Client* client, Partie* partie, Terrain* terrain);

    Client* getClient() const { return client; }
    Partie* getPartie() const { return partie; }
    Terrain* getTerrain() const { return terrain; }
    void afficher() const;

private:
    Client* client;
    Partie* partie;
    Terrain* terrain;
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
  void supprimerReservation(Client* client, Partie* partie);

  // Search for a reservation
  Reservation* rechercherReservation(Client* client, Partie* partie);

  // Display all reservations
  void afficherReservations() const;

  // Get the list of reservations
  const std::vector<Reservation>& getReservations() const;

  // Sort reservations by client name
  void trierReservationsParClient();
};

#endif // GESTION_RESERVATIONS_H