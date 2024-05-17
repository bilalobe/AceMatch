#ifndef RESERVATIONS_H
#define RESERVATIONS_H
#include <string>
#include <vector>
#include "clients.h"
#include "parties.h"
using namespace std;

class Reservation {
public:
  Reservation();
  void afficher() const;
  Reservation(Client* client, Partie* partie);
  Client* getClient() const;
  Partie* getPartie() const;
  // Remove Place: void setPlace(Place* place);

private:
  Client* client;
  Partie* partie;
  // Remove Place: Place* place;
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