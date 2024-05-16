#ifndef PARTIES_H
#define PARTIES_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <map> // Include for the map

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
  static int nextMatchNumber;
  int numero;
  TypePartie type;
  string nomJoueur1;
  string nomJoueur2;
  ResultatPartie resultat1;
  ResultatPartie resultat2;

  Partie(TypePartie type, string nomJoueur1, string nomJoueur2);

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
  void supprimerPartie(TypePartie type, string nomJoueur1, string nomJoueur2);

  // Function to retrieve a Partie by player names
  Partie* rechercherPartie(const string& nomJoueur1, const string& nomJoueur2);
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