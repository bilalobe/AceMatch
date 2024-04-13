#ifndef PARTIES_H
#define PARTIES_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "personne.h"
#include "joueurs.h"
#include "championnats.h"
using namespace std;
int previousRoundMaxMatchNumber = 0; // Initialize this after completing each round


enum TypePartie {
  SIMPLE,
  DOUBLE,
};

enum ResultatPartie {
  VICTOIRE,
  DEFAITE,
   MATCH_NUL,
};

class Partie {
public:
    static int nextMatchNumber; // Track match numbers
    int numero;
    TypePartie type;
    string nomJoueur1;
    string nomJoueur2;
    ResultatPartie resultat1;
    ResultatPartie resultat2;

    Partie(TypePartie type, string nomJoueur1, string nomJoueur2) {
      this->type = type;
      this->nomJoueur1 = nomJoueur1;
      this->nomJoueur2 = nomJoueur2;
      resultat1 =  MATCH_NUL;
      resultat2 =  MATCH_NUL;
      numero = nextMatchNumber++; // Assign and increment the ID
    }

    void afficher() const { // Use const for methods that don't modify the object
      cout << "Type: " << (type == SIMPLE ? "Simple" : "Double") << endl;
      cout << "Joueur 1: " << nomJoueur1 << endl;
      cout << "Joueur 2: " << nomJoueur2 << endl;
      cout << "Résultat 1: " << (resultat1 == VICTOIRE ? "Victoire" : "Défaite") << endl;
      cout << "Résultat 2: " << (resultat2 == VICTOIRE ? "Victoire" : "Défaite") << endl;
    }

    void setResultat(string nomJoueur, int resultatAsInt) {
        ResultatPartie actualResultat;
        switch (resultatAsInt) {
        case 0: actualResultat =  MATCH_NUL; break;
        case 1: actualResultat = VICTOIRE; break;
        case 2: actualResultat = DEFAITE; break;
        default: break; 
        }

        if (nomJoueur == nomJoueur1) {
            resultat1 = actualResultat; 
        } else if (nomJoueur == nomJoueur2) {
            resultat2 = actualResultat; 
        }
    }

    ResultatPartie getResultat1() const {
        return resultat1;
    }
    ResultatPartie getResultat2() const {
        return resultat2;
    }
    string getNomJoueur1() const {
        return nomJoueur1;
    }
    string getNomJoueur2() const {
        return nomJoueur2;
    }
    void setNomJoueur1(string nomJoueur1) {
        this->nomJoueur1 = nomJoueur1;
    }
    void setNomJoueur2(string nomJoueur2) {
        this->nomJoueur2 = nomJoueur2;
    }
};

class GestionParties {
public:
    vector<Partie> parties;
    vector<Partie> getParties() {
        return parties;
    }
        vector<Partie> getPreviousRoundMatches() {
        vector<Partie> previousRoundMatches;

        for (Partie partie : parties) {
            if (partie.numero <= previousRoundMaxMatchNumber) {
                previousRoundMatches.push_back(partie);
            }
        }
        return previousRoundMatches;
    } 
    bool isPartieFromPreviousRound(Partie partie) {
    return partie.numero <= previousRoundMaxMatchNumber;
    }

    int getPreviousRoundMaxMatchNumber() {
        return previousRoundMaxMatchNumber;
    }
    void setParties(vector<Partie> parties) {
        this->parties = parties;
    }
    void ajouterPartie(Partie partie) {
        parties.push_back(partie);
    }

    void afficherParties() {
        for (Partie partie : parties) {
            partie.afficher();
            cout << endl;
        }
    }
    void supprimerPartie(TypePartie type, string nomJoueur1, string nomJoueur2) {
        for (int i = 0; i < parties.size(); i++) {
            if (parties[i].type == type &&
                parties[i].nomJoueur1 == nomJoueur1 &&
                parties[i].nomJoueur2 == nomJoueur2) {
                parties.erase(parties.begin() + i);
                break;
            }
        }
    }
};
Partie partie;
Championnat championnat;
GestionParties gestionParties;

class PlanificationParties {
public: 
int vector<Joueur> getWinnersFromPreviousRound() {
    vector<Joueur> winners;

    // Retrieve the list of played matches from the previous round
    vector<Partie> previousRoundMatches = gestionParties.getPreviousRoundMatches(); 

    // Iterate through the matches to determine the winners
    for (Partie partie : previousRoundMatches) {
        if (partie.getResultat1() == VICTOIRE) {
            winners.push_back(Joueur(partie.getNomJoueur1()));
        } else if (partie.getResultat2() == VICTOIRE) {
            winners.push_back(Joueur(partie.getNomJoueur2()));
        } 
        // Else (Match is a draw): Add logic to handle draws if applicable
    }

    return winners;
}

void creerPartiesEliminatoires() {
    // Retrieve the list of enrolled players from the championnat object
    vector<Joueur> joueursInscrits = championnat.getJoueursInscrits();

    // Create a new match for each pair of players
    for (int i = 0; i < joueursInscrits.size(); i++) {
        for (int j = i + 1; j < joueursInscrits.size(); j++) {
            Partie partie(SIMPLE, joueursInscrits[i].getNom(), joueursInscrits[j].getNom());
            gestionParties.ajouterPartie(partie);
        }
    }
}

void creerParties16emes() {
    // Retrieve the winners from the previous round (e.g., round of 32)
    vector<Joueur> vainqueurs = getWinnersFromPreviousRound(); // You'll need to implement this

    // Create a new match for each pair of winners
    for (int i = 0; i < vainqueurs.size(); i++) {
        for (int j = i + 1; j < vainqueurs.size(); j++) {
            Partie partie(SIMPLE, vainqueurs[i].getNom(), vainqueurs[j].getNom());
            gestionParties.ajouterPartie(partie);
        }
    }
}

void attribuerJoueursParties() {
    // Retrieve the list of matches from the gestionParties object
    vector<Partie> matches = gestionParties.getParties();

    // Retrieve the list of enrolled players from the championnat object
    vector<Joueur> joueursInscrits = championnat.getJoueursInscrits();

    // Randomly assign players to matches
    for (Partie& partie : matches) {
        // Shuffle the list of players to randomize the assignment
        std::random_shuffle(joueursInscrits.begin(), joueursInscrits.end());

        // Assign the first two players to the match
        partie.setNomJoueur1(joueursInscrits[0].getNom());
        partie.setNomJoueur2(joueursInscrits[1].getNom());
    }
}

};


#endif
