#include <iostream>
#include <algorithm>

using namespace std;


// Constructor for ChampionnatSimple
ChampionnatSimple::ChampionnatSimple(const string& nom, int annee, int nbTours)
    : Championnat(nom, annee, nbTours) { // Call the base class constructor
      setNom(nom); // Use the setters to initialize private members
      setAnnee(annee);
      setNbTours(nbTours);
    }

// Method to add players to the tournament
void ChampionnatSimple::ajouterJoueur(const Joueur& joueur) {
  joueurs.push_back(joueur);
}

// Method to remove players from the tournament
void ChampionnatSimple::supprimerJoueur(const string& nom) {
  for (int i = 0; i < joueurs.size(); i++) {
    if (joueurs[i].nom == getNom()) {
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
    if (parties[i].getNumero() == numero) {
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
    if (tickets[i].getNumeroTicket() == numero) {
      tickets.erase(tickets.begin() + i);
      break;
    }
  }
}

// Method to display the tournament information
void ChampionnatSimple::afficherChampionnat() {
  cout << "Championnat: " << getNom() << endl; // Use the getter
  cout << "Annee: " << getAnnee() << endl; // Use the getter
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
