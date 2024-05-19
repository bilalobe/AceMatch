#include "partie.h"

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

