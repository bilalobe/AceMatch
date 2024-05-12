#ifndef CHAMPIONNATS_H
#define CHAMPIONNATS_H

#include <vector>
#include <string>
#include "parties.h"
#include "tickets.h"
#include "joueurs.h"  
#include "scores.h"

using namespace std;

class Championnat {
public:
    Championnat() {} // Default constructor
    
  std::string nom; // Tournament name
  int annee; // Tournament year
  int nbTours; // Number of rounds in the tournament (e.g., 4 for quarterfinals)
  std::vector<Joueur> joueursInscrits; // Enrolled players
  std::vector<Partie> parties; // Played matches
  std::vector<Ticket> tickets; // Tickets sold

  // Constructor
  Championnat(const std::string& nom, int annee, int nbTours) : nom(nom), annee(annee), nbTours(nbTours) {}
  
  
  // Method to add players to the tournament
  void inscrireJoueur(const Joueur& joueur) {
    joueursInscrits.push_back(joueur);
  }

  // Method to get the list of enrolled players
  const std::vector<Joueur>& getJoueursInscrits() const {
    return joueursInscrits;
  }
};

class ChampionnatSimple : public Championnat {
public:
  std::vector<Joueur> joueurs; // Players in the tournament

  // Constructor
  ChampionnatSimple(const std::string& nom, int annee, int nbTours) : Championnat(nom, annee, nbTours) {}

  // Method to add players to the tournament
  void ajouterJoueur(const Joueur& joueur) {
    joueurs.push_back(joueur);
  }

  // Method to remove players from the tournament
  void supprimerJoueur(const std::string& nom) {
    for (int i = 0; i < joueurs.size(); i++) {
      if (joueurs[i].nom == nom) {
        joueurs.erase(joueurs.begin() + i);
        break;
      }
    }
  }

  // Method to add matches to the tournament
  void ajouterPartie(const Partie& partie) {
    parties.push_back(partie);
  }

  // Method to remove matches from the tournament
  void supprimerPartie(int numero) {
    for (int i = 0; i < parties.size(); i++) {
      if (parties[i].numero == numero) {
        parties.erase(parties.begin() + i);
        break;
      }
    }
  }

  // Method to add tickets to the tournament
  void ajouterTicket(const Ticket& ticket) {
    tickets.push_back(ticket);
  }

  // Method to remove tickets from the tournament
  void supprimerTicket(int numero) {
    for (int i = 0; i < tickets.size(); i++) {
      if (tickets[i].numero == numero) {
        tickets.erase(tickets.begin() + i);
        break;
      }
    }
  }

  // Method to display the tournament information
  void afficherChampionnat() {
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
};

#endif
