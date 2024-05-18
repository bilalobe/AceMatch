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
Partie::Partie(TypePartie type, string nomJoueur1, string nomJoueur2, Terrain* terrain) {
  this->type = type;
  this->nomJoueur1 = nomJoueur1;
  this->nomJoueur2 = nomJoueur2;
  resultat1 = MATCH_NUL;
  resultat2 = MATCH_NUL;
  numero = nextMatchNumber++;
  this->terrain = terrain;
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
    if (partie.getNumero() <= previousRoundMaxMatchNumber) {
      previousRoundMatches.push_back(partie);
    }
  }
  return previousRoundMatches;
}

// Check if a match is from the previous round
bool GestionParties::isPartieFromPreviousRound(Partie partie) {
  return partie.getNumero() <= previousRoundMaxMatchNumber;
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
  partiesMap[make_pair(partie.getNomJoueur1(), partie.getNomJoueur2())] = &partie;
  partiesMap[make_pair(partie.getNomJoueur2(), partie.getNomJoueur1())] = &partie;
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
    if (parties[i].getType == type && parties[i].getNomJoueur1() == nomJoueur1 &&
        parties[i].getNomJoueur2() == nomJoueur2) {
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
Partie* GestionParties::rechercherPartie(const std::string& matchName) {
  // Add logic to search for a match by its name
  // Example: Assuming matchName is in the format "Player1 vs. Player2"
  for (auto& partie : parties) {
    if ((partie.getNomJoueur1() + " vs. " + partie.getNomJoueur1() == matchName) ||
        (partie.getNomJoueur2() + " vs. " + partie.getNomJoueur1() == matchName)) {
      return &partie;
    }
  }
  return nullptr; // Match not found
}
void GestionParties::setMatchResult(int numero, const std::string& winnerName) {
    for (int i = 0; i < parties.size(); i++) {
        if (parties[i].getNumero() == numero) {
            if (parties[i].getNomJoueur1() == winnerName) {
                parties[i].setResultat(parties[i].getNomJoueur1(), 1);
                parties[i].setResultat(parties[i].getNomJoueur2(), 2);
            } else if (parties[i].getNomJoueur2() == winnerName) {
                parties[i].setResultat(parties[i].getNomJoueur2(), 1);
                parties[i].setResultat(parties[i].getNomJoueur1(), 2);
            }
            break;
        }
    }
}

std::istream& operator>>(std::istream& is, TypePartie& tp) {
  int input;
  is >> input; // Read the input as an integer
  if (input == 0) {
    tp = SIMPLE;
  } else if (input == 1) {
    tp = DOUBLE;
  } else {
    is.setstate(ios_base::failbit); // Set the error state if the input is invalid
  }
  return is;
}