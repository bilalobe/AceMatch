#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include "clients.h"
#include "parties.h"

#include <string>
#include <vector>

using namespace std;

class Reservation {
public:
  Reservation();
  Reservation(Client* client, Partie* partie);
  Client* getClient() const;
  Partie* getPartie() const;
  void setClient(Client* client);
  void setPartie(Partie* partie);

private:
  Client* client;
  Partie* partie;
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