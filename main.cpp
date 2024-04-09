#include "Joueurs.h"
#include "Reservations.h"
#include "Scores.h"
#include "Parties.h"
#include "Terrains.h"

using namespace std;

int main() {

  // **Gestion des joueurs**

  Joueur joueur1("Roger Federer", 1);
  Joueur joueur2("Rafael Nadal", 2);
  Joueur joueur3("Novak Djokovic", 3);

  GestionJoueurs gestionJoueurs;
  gestionJoueurs.ajouterJoueur(joueur1);
  gestionJoueurs.ajouterJoueur(joueur2);
  gestionJoueurs.ajouterJoueur(joueur3);

  // **Gestion des réservations**

  time_t dateHeureDebut;
  time_t dateHeureFin = dateHeureDebut + 3600;

  // Déclaration et instanciation de Terrain1
  Terrain terrain1(DUR, 10, 20);

  // Déclaration et instanciation de places
  StandardPlace place1(1);
  VipPlace place2(2);

  // Déclaration et instanciation de parties
  Partie partie1(SIMPLE, &joueur1, &joueur2);
  Partie partie2(DOUBLE, &joueur1, &joueur2);

  // Ajout des parties
  GestionParties gestionParties;
  gestionParties.ajouterPartie(partie1);
  gestionParties.ajouterPartie(partie2);

  // Réservations
  Reservation reservation1(&joueur1, &partie1, &place1);
  Reservation reservation2(&joueur2, &partie2, &place2);

  GestionReservations gestionReservations;
  gestionReservations.ajouterReservation(reservation1);
  gestionReservations.ajouterReservation(reservation2);

  // **Affichage des informations**

  gestionJoueurs.afficherJoueurs();
  gestionParties.afficherParties();
  //gestionReservations.afficherReservations(); // Affichage optionnel

  return 0;
}
