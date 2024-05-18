#include "parties.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "joueurs.h"
#include "championnats.h"
#include "scores.h"

using namespace std;

// Static member initialization for next match number
int Partie::nextMatchNumber = 1;

// Constructor for Partie
Partie::Partie(TypePartie type, string nomJoueur1, string nomJoueur2) {
  this->type = type;
  this->nomJoueur1 = nomJoueur1;
  this->nomJoueur2 = nomJoueur2;
  resultat1 = MATCH_NUL;
  resultat2 = MATCH_NUL;
  numero = nextMatchNumber++;
}

// Display a match's details
void Partie::afficher() const {
  cout << "Type: " << (type == SIMPLE ? "Simple" : "Double") << endl;
  cout << "Joueur 1: " << nomJoueur1 << endl;
  cout << "Joueur 2: " << nomJoueur2 << endl;
  cout << "Résultat 1: " << (resultat1 == VICTOIRE ? "Victoire" : "Défaite") << endl;
  cout << "Résultat 2: " << (resultat2 == VICTOIRE ? "Victoire" : "Défaite") << endl;
}

// Set the result of a match
void Partie::setResultat(const string& nomJoueur, int resultatAsInt) {
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

// Get the result for player 1
ResultatPartie Partie::getResultat1() const {
  return resultat1;
}

// Get the result for player 2
ResultatPartie Partie::getResultat2() const {
  return resultat2;
}

// Get the name of player 1
string Partie::getNomJoueur1() const {
  return nomJoueur1;
}

// Get the name of player 2
string Partie::getNomJoueur2() const {
  return nomJoueur2;
}

// Set the name of player 1
void Partie::setNomJoueur1(string nomJoueur1) {
  this->nomJoueur1 = nomJoueur1;
}

// Set the name of player 2
void Partie::setNomJoueur2(string nomJoueur2) {
  this->nomJoueur2 = nomJoueur2;
}

// GestionParties implementation
GestionParties::GestionParties() {}

// Get the list of matches
vector<Partie> GestionParties::getParties() {
  return parties;
}

// Get the list of matches from the previous round
vector<Partie> GestionParties::getPreviousRoundMatches() {
  vector<Partie> previousRoundMatches;
  for (const Partie& partie : parties) {
    if (partie.numero <= previousRoundMaxMatchNumber) {
      previousRoundMatches.push_back(partie);
    }
  }
  return previousRoundMatches;
}

// Check if a match is from the previous round
bool GestionParties::isPartieFromPreviousRound(Partie partie) {
  return partie.numero <= previousRoundMaxMatchNumber;
}

// Get the maximum match number from the previous round
int GestionParties::getPreviousRoundMaxMatchNumber() const {
  return previousRoundMaxMatchNumber;
}

// Set the maximum match number from the previous round
void GestionParties::setPreviousRoundMaxMatchNumber(int newMax) {
  previousRoundMaxMatchNumber = newMax;
}

// Set the list of matches
void GestionParties::setParties(vector<Partie> parties) {
  this->parties = parties;
}

// Add a match
void GestionParties::ajouterPartie(Partie partie) {
  parties.push_back(partie);
  partiesMap[make_pair(partie.nomJoueur1, partie.nomJoueur2)] = &partie;
}

// Display all matches
void GestionParties::afficherParties() {
  for (Partie partie : parties) {
    partie.afficher();
    cout << endl;
  }
}

// Remove a match
void GestionParties::supprimerPartie(TypePartie type, string nomJoueur1, string nomJoueur2) {
  for (int i = 0; i < parties.size(); i++) {
    if (parties[i].type == type && parties[i].nomJoueur1 == nomJoueur1 &&
        parties[i].nomJoueur2 == nomJoueur2) {
      parties.erase(parties.begin() + i);
      break;
    }
  }
}

// Function to retrieve a Partie by player names
Partie* GestionParties::rechercherPartie(const string& nomJoueur1, const string& nomJoueur2) {
  auto it = partiesMap.find(make_pair(nomJoueur1, nomJoueur2));
  if (it != partiesMap.end()) {
    return it->second;
  }
  return nullptr;
}

// Function to retrieve a Partie by match name
Partie* GestionParties::rechercherPartie(const string& matchName) {
  for (Partie& partie : parties) {
    // Check if the match name matches the names of the players in the match
    if ((partie.nomJoueur1 + " vs. " + partie.nomJoueur2 == matchName) ||
        (partie.nomJoueur2 + " vs. " + partie.nomJoueur1 == matchName)) {
      return &partie; // Return a pointer to the found match
    }
  }
  return nullptr; // Match not found
}

// PlanificationParties implementation
class PlanificationParties {
private:
  TennisChampionship* tennisChampionship;

public:
  // Constructor (take TennisChampionship as an argument)
  PlanificationParties(TennisChampionship* tennisChampionship) : tennisChampionship(tennisChampionship) {} 

  vector<Joueur> getWinnersFromPreviousRound() {
    vector<Joueur> winners;

    // Retrieve the list of played matches from the previous round
    vector<Partie> previousRoundMatches = tennisChampionship->gestionParties.getPreviousRoundMatches();

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
    vector<Joueur> joueursInscrits = tennisChampionship->championnat.getJoueursInscrits();

    // Create a new match for each pair of players
    for (int i = 0; i < joueursInscrits.size(); i++) {
      for (int j = i + 1; j < joueursInscrits.size(); j++) {
        TypePartie type = getMatchTypeFromUser();
        Partie partie(type, joueursInscrits[i].getNom(), joueursInscrits[j].getNom());
        tennisChampionship->gestionParties.ajouterPartie(partie);
      }
    }
  }

  void attribuerJoueursParties() {
    // Retrieve the list of matches from the gestionParties object
    vector<Partie> matches = tennisChampionship->gestionParties.getParties();

    // Retrieve the list of enrolled players from the championnat object
    vector<Joueur> joueursInscrits = tennisChampionship->championnat.getJoueursInscrits();

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
    std::vector<Joueur> joueurs = tennisChampionship->championnat.getJoueursInscrits();
    std::sort(joueurs.begin(), joueurs.end(), [](const Joueur& a, const Joueur& b) {
      return a.getClassement() > b.getClassement(); // Sort by descending ranking
    });

    // Pair players based on rankings
    for (int i = 0; i < joueurs.size() / 2; ++i) {
      TypePartie type = getMatchTypeFromUser();
      Partie partie(type, joueurs[i].getNom(), joueurs[joueurs.size() - 1 - i].getNom());
      tennisChampionship->gestionParties.ajouterPartie(partie);
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
      TypePartie type = getMatchTypeFromUser();
      Partie partie(type, vainqueurs[i].getNom(), vainqueurs[i + 1].getNom());
      tennisChampionship->gestionParties.ajouterPartie(partie);
    }
  }

  void creerPartiesQuartsDeFinale() {
    std::vector<Joueur> vainqueurs = getWinnersFromPreviousRound();

    std::sort(vainqueurs.begin(), vainqueurs.end(), [](const Joueur& j1, const Joueur& j2) {
      return j1.getClassement() > j2.getClassement();
    });

    // Pair and create matches
    for (int i = 0; i < vainqueurs.size(); i += 2) { // Assuming even number of players (adjust logic for odd numbers if needed)
      TypePartie type = getMatchTypeFromUser();
      Partie partie(type, vainqueurs[i].getNom(), vainqueurs[i + 1].getNom());
      tennisChampionship->gestionParties.ajouterPartie(partie);
    }
  }

  void creerPartiesDemiFinales() {
    // Retrieve the list of winners from the previous round (e.g., round of 8)
    vector<Joueur> vainqueurs = getWinnersFromPreviousRound();

    // Create a new match for each pair of winners
    for (int i = 0; i < vainqueurs.size(); i++) {
      for (int j = i + 1; j < vainqueurs.size(); j++) {
        TypePartie type = getMatchTypeFromUser();
        Partie partie(type, vainqueurs[i].getNom(), vainqueurs[j].getNom());
        tennisChampionship->gestionParties.ajouterPartie(partie);
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
    TypePartie type = getMatchTypeFromUser();
    Partie partie(type, vainqueurs[0].getNom(), vainqueurs[1].getNom());
    tennisChampionship->gestionParties.ajouterPartie(partie);
  }
};