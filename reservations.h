#ifndef RESERVATIONS_H
#define RESERVATIONS_H
#include "places.h"
#include <string>
#include <vector>

using namespace std;

class Reservation {
public:
  Reservation(Joueur* joueur, Partie* partie, Place* place);
  Joueur* getJoueur() const;
  Partie* getPartie() const;
  Place* getPlace() const;
  void setJoueur(Joueur* joueur);
  void setPartie(Partie* partie);
  void setPlace(Place* place);
private:
  Joueur* joueur;
  Partie* partie;
  Place* place;
};

class GestionReservations {
public:
  void ajouterReservation(Reservation reservation);
  void supprimerReservation(Joueur* joueur, Partie* partie, Place* place);
  Reservation* rechercherReservation(Joueur* joueur, Partie* partie, Place* place);
  const vector<Reservation>& getReservations() const;
  void trierReservationsParJoueur();

private:
  vector<Reservation> reservations;
};

#endif // RESERVATIONS_H