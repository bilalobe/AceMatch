#include "Championnat.h"

Championnat::Championnat(const string& nom, int annee, int nbTours)
  : nom(nom), annee(annee), nbTours(nbTours), tennisChampionship(new TennisChampionship()) {} // Initialize tennisChampionship in the initializer list

// Method to add players to the tournament
void Championnat::inscrireJoueur(const Joueur& joueur) {
  joueursInscrits.push_back(joueur);
}

// Method to get the list of enrolled players
const std::vector<Joueur>& Championnat::getJoueursInscrits() const {
  return joueursInscrits;
}
