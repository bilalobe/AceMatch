#include "championnats.h"
#include <iostream>
#include <algorithm>
#include "tickets.h"

using namespace std;

//  Constructor
Championnat::Championnat(const string& nom, int annee, int nbTours)
    : nom(nom), annee(annee), nbTours(nbTours) {}

// Method to add players to the tournament
void Championnat::inscrireJoueur(const Joueur& joueur) {
  joueursInscrits.push_back(joueur);
}

// Method to get the list of enrolled players
const vector<Joueur>& Championnat::getJoueursInscrits() const {
  return joueursInscrits;
}

// Constructor for ChampionnatSimple
ChampionnatSimple::ChampionnatSimple(const string& nom, int annee, int nbTours)
    : Championnat(nom, annee, nbTours) {}

// Method to add players to the tournament
void ChampionnatSimple::ajouterJoueur(const Joueur& joueur) {
  joueurs.push_back(joueur);
}

// Method to remove players from the tournament
void ChampionnatSimple::supprimerJoueur(const string& nom) {
  for (int i = 0; i < joueurs.size(); i++) {
    if (joueurs[i].nom == nom) {
      joueurs.erase(joueurs.begin() + i);
      break;
    }
  }
}

// Method to add matches to the tournament
void ChampionnatSimple::ajouterPartie(const Partie& partie) {
  parties.push_back(partie);
}

// Method to remove matches from the tournament
void ChampionnatSimple::supprimerPartie(int numero) {
  for (int i = 0; i < parties.size(); i++) {
    if (parties[i].numero == numero) {
      parties.erase(parties.begin() + i);
      break;
    }
  }
}

// Method to add tickets to the tournament
void ChampionnatSimple::ajouterTicket(const Ticket& ticket) {
  tickets.push_back(ticket);
}

// Method to remove tickets from the tournament
void ChampionnatSimple::supprimerTicket(int numero) {
  for (int i = 0; i < tickets.size(); i++) {
    if (tickets[i].numeroTicket == numero) {
      tickets.erase(tickets.begin() + i);
      break;
    }
  }
}

// Method to display the tournament information
void ChampionnatSimple::afficherChampionnat() {
  cout << "Championnat: " << nom << endl;
  cout << "Annee: " << annee << endl;
  cout << "Joueurs: " << endl;
  for (Joueur joueur : joueurs) {
    cout << "Name: " << joueur.getNom() << endl;
    cout << "Ranking: " << joueur.getClassement() << endl;
    cout << "Wins: " << joueur.nbVictoires << endl;
    cout << "Losses: " << joueur.nbDefaites << endl;
  }
  for (Partie partie : parties) {
    partie.afficher();
  }
  cout << "Tickets: " << endl;
  for (Ticket ticket : tickets) {
    ticket.afficher();
  }
}