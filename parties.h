#ifndef PARTIES_H
#define PARTIES_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <map>

#include "joueurs.h"
#include "championnats.h"

using namespace std;

// No longer an enum, now an int
int TypePartie; 

enum ResultatPartie {
  VICTOIRE,
  DEFAITE,
  MATCH_NUL,
};

class Partie {
public:
  static int nextMatchNumber;
  int numero;
  int type; // Use int for the type 
  string nomJoueur1;
  string nomJoueur2;
  ResultatPartie resultat1;
  ResultatPartie resultat2;

  Partie(int type, string nomJoueur1, string nomJoueur2);

  void afficher() const;
  void setResultat(const std::string& nomJoueur, int resultatAsInt);

  ResultatPartie getResultat1() const;
  ResultatPartie getResultat2() const;
  string getNomJoueur1() const;
  string getNomJoueur2() const;
  void setNomJoueur1(string nomJoueur1);
  void setNomJoueur2(string nomJoueur2);
};

class GestionParties {
private:
  int previousRoundMaxMatchNumber;
  // Use a map to store matches for efficient retrieval
  std::map<std::pair<std::string, std::string>, Partie*> partiesMap;

public:
  vector<Partie> parties;
  vector<Partie> getParties();
  vector<Partie> getPreviousRoundMatches();
  bool isPartieFromPreviousRound(Partie partie);
  int getPreviousRoundMaxMatchNumber() const;
  void setPreviousRoundMaxMatchNumber(int newMax);
  void setParties(vector<Partie> parties);
  void ajouterPartie(Partie partie);
  void afficherParties();
  void supprimerPartie(int type, string nomJoueur1, string nomJoueur2); // Adjust parameter type

  // Function to retrieve a Partie by match name
  Partie* rechercherPartie(const string& matchName);
};

class PlanificationParties {
public:
  vector<Joueur> getWinnersFromPreviousRound();
  void creerPartiesEliminatoires();
  void attribuerJoueursParties();
  void creerParties16emes();
  void creerPartiesHuitiemesDeFinale();
  void creerPartiesQuartsDeFinale();
  void creerPartiesDemiFinales();
  void creerPartieFinale();
};

#endif