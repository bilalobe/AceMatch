#ifndef CHAMPIONNATS_H
#define CHAMPIONNATS_H

#include <vector>
#include <string>
#include "parties.h"
#include "tickets.h"
#include "joueurs.h"  

using namespace std;
class Championnat {
  public:
    string nom;
    int annee;
    vector<Joueur> joueurs;
    vector<Partie> parties;
    vector<Ticket> tickets;
    // Inside the Championnat class
vector<Joueur> Championnat::getJoueursInscrits() const {
    return joueurs;
}

    Championnat(string nom, int annee) {
      this->nom = nom;
      this->annee = annee;
    }

    void ajouterJoueur(Joueur joueur) {
      joueurs.push_back(joueur);
    }

    void supprimerJoueur(string nom) {
      for (int i = 0; i < joueurs.size(); i++) {
        if (joueurs[i].nom == nom) {
          joueurs.erase(joueurs.begin() + i);
          break;
        }
      }
    }

    void ajouterPartie(Partie partie) {
      parties.push_back(partie);
    }

    void supprimerPartie(int numero) {
      for (int i = 0; i < parties.size(); i++) {
        if (parties[i].numero == numero) {
          parties.erase(parties.begin() + i);
          break;
        }
      }
    }

    void ajouterTicket(Ticket ticket) {
      tickets.push_back(ticket);
    }

    void supprimerTicket(int numero) {
      for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i].numero == numero) {
          tickets.erase(tickets.begin() + i);
          break;
        }
      }
    }

    void afficherChampionnat() {
      cout << "Championnat: " << nom << endl;
      cout << "Annee: " << annee << endl;
      cout << "Joueurs: " << endl;
      for (Joueur joueur : joueurs) {
        joueur.afficher(&joueur);
      }
      cout << "Parties: " << endl;
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
