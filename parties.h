#ifndef PARTIES_H
#define PARTIES_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

#include "personne.h"
#include "joueurs.h"
#include "championnats.h"

using namespace std;

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
    resultat1 = MATCH_NUL;
    resultat2 = MATCH_NUL;
    numero = nextMatchNumber++; // Assign and increment the ID
  }

  void afficher() const { // Use const for methods that don't modify the object
    cout << "Type: " << (type == SIMPLE ? "Simple" : "Double") << endl;
    cout << "Joueur 1: " << nomJoueur1 << endl;
    cout << "Joueur 2: " << nomJoueur2 << endl;
    cout << "Résultat 1: " << (resultat1 == VICTOIRE ? "Victoire" : "Défaite") << endl;
    cout << "Résultat 2: " << (resultat2 == VICTOIRE ? "Victoire" : "Défaite") << endl;
  }

  void setResultat(const std::string& nomJoueur, int resultatAsInt) {
    if (resultatAsInt < 0 || resultatAsInt > 2) {
      throw std::invalid_argument("Invalid result value. Must be between 0 and 2.");
    }
    ResultatPartie actualResultat = static_cast<ResultatPartie>(resultatAsInt);
    switch (resultatAsInt) {
    case 0:
      actualResultat = MATCH_NUL;
      break;
    case 1:
      actualResultat = VICTOIRE;
      break;
    case 2:
      actualResultat = DEFAITE;
      break;
    default:
      break;
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
private:
  int previousRoundMaxMatchNumber = 0; // Initialize this after completing each round

public:
  vector<Partie> parties;
  vector<Partie> getParties() {
    return parties;
  }
  vector<Partie> getPreviousRoundMatches() {
    vector<Partie> previousRoundMatches;
    for (const Partie& partie : parties) {
      if (partie.numero <= previousRoundMaxMatchNumber) {
        previousRoundMatches.push_back(partie);
      }
    }
    return previousRoundMatches;
  }
  bool isPartieFromPreviousRound(Partie partie) {
    return partie.numero <= previousRoundMaxMatchNumber;
  }

  int getPreviousRoundMaxMatchNumber() const {
    return previousRoundMaxMatchNumber;
  }

  void setPreviousRoundMaxMatchNumber(int newMax) {
    previousRoundMaxMatchNumber = newMax;
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
      if (parties[i].type == type && parties[i].nomJoueur1 == nomJoueur1 &&
          parties[i].nomJoueur2 == nomJoueur2) {
        parties.erase(parties.begin() + i);
        break;
      }
    }
  }
};

class PlanificationParties {
public:
  vector<Joueur> PlanificationParties::getWinnersFromPreviousRound() {
    vector<Joueur> winners;

    // Retrieve the list of played matches from the previous round
    vector<Partie> previousRoundMatches = gestionParties.getPreviousRoundMatches();

    // Iterate through matches and identify winners
    for (Partie partie : previousRoundMatches) {
      if (partie.getResultat1() == VICTOIRE) {
        winners.push_back(Joueur(partie.getNomJoueur1()));
      } else if (partie.getResultat2() == VICTOIRE) {
        winners.push_back(Joueur(partie.getNomJoueur2()));
      } else {
        // Handle draws (optional, logic not provided)
        // You can throw an exception or implement logic to handle draws here
        // For example, if you want both players to advance:
        // winners.push_back(Joueur(partie.getNomJoueur1()));
        // winners.push_back(Joueur(partie.getNomJoueur2()));
      }
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

  void attribuerJoueursParties() {
    // Retrieve the list of matches from the gestionParties object
    vector<Partie> matches = gestionParties.getParties();

    // Retrieve the list of enrolled players from the championnat object
    vector<Joueur> joueursInscrits = championnat.getJoueursInscrits();

    // Randomly assign players to matches
    for (Partie& partie : matches) {
      std::random_device rd;
      std::mt19937 g(rd());
      std::shuffle(joueursInscrits.begin(), joueursInscrits.end(), g);
      // Assign the first two players to the match
      partie.setNomJoueur1(joueursInscrits[0].getNom());
      partie.setNomJoueur2(joueursInscrits[1].getNom());
    }
  }

  void creerParties16emes() {
    // Get sorted players based on rankings (assuming you have a ranking system)
    std::vector<Joueur> joueurs = championnat.getJoueursInscrits();
    std::sort(joueurs.begin(), joueurs.end(), [](const Joueur& a, const Joueur& b) {
      return a.getClassement() > b.getClassement(); // Sort by descending ranking
    });

    // Pair players based on rankings
    for (int i = 0; i < joueurs.size() / 2; ++i) {
      Partie partie(SIMPLE, joueurs[i].getNom(), joueurs[joueurs.size() - 1 - i].getNom());
      gestionParties.ajouterPartie(partie);
    }
  }

  void creerPartiesHuitiemesDeFinale() {
    std::vector<Joueur> vainqueurs = getWinnersFromPreviousRound(); // Get winners from previous round

    // (Optional) Update rankings if you have a dynamic ranking system
    // ... (your ranking update logic here)

    // Sort winners based on rankings
    std::sort(vainqueurs.begin(), vainqueurs.end(), [](const Joueur& j1, const Joueur& j2) {
      return j1.getClassement() > j2.getClassement();
    });

    // Pair and create matches
    for (int i = 0; i < vainqueurs.size(); i += 2) { // Increment by 2 to pair players
      Partie partie(SIMPLE, vainqueurs[i].getNom(), vainqueurs[i + 1].getNom());
      gestionParties.ajouterPartie(partie);
    }
  }

  void creerPartiesQuartsDeFinale() {
    std::vector<Joueur> vainqueurs = getWinnersFromPreviousRound();

    std::sort(vainqueurs.begin(), vainqueurs.end(), [](const Joueur& j1, const Joueur& j2) {
      return j1.getClassement() > j2.getClassement();
    });

    // Pair and create matches
    for (int i = 0; i < vainqueurs.size(); i += 2) { // Assuming even number of players (adjust logic for odd numbers if needed)
      Partie partie(SIMPLE, vainqueurs[i].getNom(), vainqueurs[i + 1].getNom());
      gestionParties.ajouterPartie(partie);
    }
  }

  void creerPartiesDemiFinales() {
    // Retrieve the list of winners from the previous round (e.g., round of 8)
    vector<Joueur> vainqueurs = getWinnersFromPreviousRound();

    // Create a new match for each pair of winners
    for (int i = 0; i < vainqueurs.size(); i++) {
      for (int j = i + 1; j < vainqueurs.size(); j++) {
        Partie partie(SIMPLE, vainqueurs[i].getNom(), vainqueurs[j].getNom());
        gestionParties.ajouterPartie(partie);
      }
    }
  }

  void creerPartieFinale() {
    // Retrieve the list of winners from the previous round (e.g., round of 4)
    vector<Joueur> vainqueurs = getWinnersFromPreviousRound();

    // Check if there are exactly two winners (assuming semifinals)
    if (vainqueurs.size() != 2) {
      throw runtime_error("Unexpected number of winners in semifinals.");
    }

    // Create a new match for the two winners
    Partie partie(SIMPLE, vainqueurs[0].getNom(), vainqueurs[1].getNom());
    gestionParties.ajouterPartie(partie);
  }
};

#endif
