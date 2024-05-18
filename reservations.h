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
  Reservation(Client* client, Partie* partie); 
  
    Client* getClient() const { return client; }
    Partie* getPartie() const { return partie; }
    Terrain* getTerrain() const { return terrain; }
    void afficher() const;
    void setTerrain(Terrain* terrain) { this->terrain = terrain; }

private:
    Client* client;
    Partie* partie;
    Terrain* terrain;
};
class GestionReservations {
public:
  void ajouterReservation(Reservation reservation);
  void supprimerReservation(Client* client, Partie* partie);
  Reservation* rechercherReservation(Client* client, Partie* partie);
  const vector<Reservation>& getReservations() const;
  void trierReservationsParClient();

private:
  vector<Reservation> reservations;
};

#endif // RESERVATIONS_H