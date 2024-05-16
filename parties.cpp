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

// PlanificationParties implementation
PlanificationParties::PlanificationParties() {}

// Get the winners from the previous round
vector<Joueur> PlanificationParties::getWinnersFromPreviousRound() {
  vector<Joueur> winners;
  vector<Partie> previousRoundMatches = gestionParties.getPreviousRoundMatches();
  for (Partie partie : previousRoundMatches) {
    if (partie.getResultat1() == VICTOIRE) {
      winners.push_back(Joueur(partie.getNomJoueur1()));
    } else if (partie.getResultat2() == VICTOIRE) {
      winners.push_back(Joueur(partie.getNomJoueur2()));
    } else {
      // Handle draws (optional, logic not provided)
    }
  }
  return winners;
}

// Create matches for the elimination rounds
void PlanificationParties::creerPartiesEliminatoires() {
  vector<Joueur> joueursInscrits = championnat.getJoueursInscrits();
  for (int i = 0; i < joueursInscrits.size(); i++) {
    for (int j = i + 1; j < joueursInscrits.size(); j++) {
      Partie partie(SIMPLE, joueursInscrits[i].getNom(), joueursInscrits[j].getNom());
      gestionParties.ajouterPartie(partie);
    }
  }
}

// Assign players to matches randomly
void PlanificationParties::attribuerJoueursParties() {
  vector<Partie> matches = gestionParties.getParties();
  vector<Joueur> joueursInscrits = championnat.getJoueursInscrits();
  for (Partie& partie : matches) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(joueursInscrits.begin(), joueursInscrits.end(), g);
    partie.setNomJoueur1(joueursInscrits[0].getNom());
    partie.setNomJoueur2(joueursInscrits[1].getNom());
  }
}

// Create matches for the round of 16
void PlanificationParties::creerParties16emes() {
  vector<Joueur> joueurs = championnat.getJoueursInscrits();
  std::sort(joueurs.begin(), joueurs.end(), [](const Joueur& a, const Joueur& b) {
    return a.getClassement() > b.getClassement();
  });
  for (int i = 0; i < joueurs.size() / 2; ++i) {
    Partie partie(SIMPLE, joueurs[i].getNom(), joueurs[joueurs.size() - 1 - i].getNom());
    gestionParties.ajouterPartie(partie);
  }
}

// Create matches for the round of 8
void PlanificationParties::creerPartiesHuitiemesDeFinale() {
  vector<Joueur> vainqueurs = getWinnersFromPreviousRound();
  std::sort(vainqueurs.begin(), vainqueurs.end(), [](const Joueur& j1, const Joueur& j2) {
    return j1.getClassement() > j2.getClassement();
  });
  for (int i = 0; i < vainqueurs.size(); i += 2) {
    Partie partie(SIMPLE, vainqueurs[i].getNom(), vainqueurs[i + 1].getNom());
    gestionParties.ajouterPartie(partie);
  }
}

// Create matches for the quarter-finals
void PlanificationParties::creerPartiesQuartsDeFinale() {
  vector<Joueur> vainqueurs = getWinnersFromPreviousRound();
  std::sort(vainqueurs.begin(), vainqueurs.end(), [](const Joueur& j1, const Joueur& j2) {
    return j1.getClassement() > j2.getClassement();
  });
  for (int i = 0; i < vainqueurs.size(); i += 2) {
    Partie partie(SIMPLE, vainqueurs[i].getNom(), vainqueurs[i + 1].getNom());
    gestionParties.ajouterPartie(partie);
  }
}

// Create matches for the semi-finals
void PlanificationParties::creerPartiesDemiFinales() {
  vector<Joueur> vainqueurs = getWinnersFromPreviousRound();
  for (int i = 0; i < vainqueurs.size(); i++) {
    for (int j = i + 1; j < vainqueurs.size(); j++) {
      Partie partie(SIMPLE, vainqueurs[i].getNom(), vainqueurs[j].getNom());
      gestionParties.ajouterPartie(partie);
    }
  }
}

// Create the final match
void PlanificationParties::creerPartieFinale() {
  vector<Joueur> vainqueurs = getWinnersFromPreviousRound();
  if (vainqueurs.size() != 2) {
    throw runtime_error("Unexpected number of winners in semifinals.");
  }
  Partie partie(SIMPLE, vainqueurs[0].getNom(), vainqueurs[1].getNom());
  gestionParties.ajouterPartie(partie);
}