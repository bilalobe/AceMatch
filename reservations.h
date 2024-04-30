#ifndef RESERVATIONS_H
#define RESERVATIONS_H
#include "places.h"
#include <string>
#include <vector>

using namespace std;

class Reservation {
public:
  Reservation(){}
  Reservation(Joueur* joueur, Partie* partie, Place* place) : joueur(joueur), partie(partie), place(place) {}
  Joueur* getJoueur() const{ return joueur; }
  Partie* getPartie() const{ return partie; }
  Place* getPlace() const{ return place; }
  void setJoueur(Joueur* joueur){this->joueur = joueur;}
  void setPartie(Partie* partie) {this->partie = partie;}
  void setPlace(Place* place) {this->place = place;}

private:
  Joueur* joueur;
  Partie* partie;
  Place* place;
};

class GestionReservations {
public:
  void ajouterReservation(Reservation reservation){
    reservations.push_back(reservation);
  }
  void supprimerReservation(Joueur* joueur, Partie* partie, Place* place){
    for (Reservation& reservation : reservations) {
      if (reservation.getJoueur() == joueur && reservation.getPartie() == partie && reservation.getPlace() == place) {
        reservations.erase(remove(reservations.begin(), reservations.end(), reservation), reservations.end());
        break;
      }
    }
  }
  Reservation* rechercherReservation(Joueur* joueur, Partie* partie, Place* place){
    for (Reservation& reservation : reservations) {
      if (reservation.getJoueur() == joueur && reservation.getPartie() == partie && reservation.getPlace() == place) {
        return &reservation;
      }
    }
    return nullptr;
  }
  const vector<Reservation>& getReservations() const{
    return reservations;
  }
  void trierReservationsParJoueur(){
    sort(reservations.begin(), reservations.end(), [](const Reservation& a, const Reservation& b) {
      return a.getJoueur()->getNom() < b.getJoueur()->getNom();
    });
  }

private:
  vector<Reservation> reservations;
};

#endif // RESERVATIONS_H