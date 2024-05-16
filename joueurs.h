#ifndef JOUEURS_H
#define JOUEURS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "scores.h"

using namespace std;

class Joueur {
public:
  Joueur();
  std::string nom;
  int classement;
  int nbVictoires;
  int nbDefaites;

  Joueur(string nom, int classement);
  Joueur(std::string nom);

  string getNom() const;
  int getClassement() const;

  void setNom(string nom);
  void setClassement(int classement);

  void incrementerVictoire();
  void incrementerDefaite();

  bool operator==(const Joueur& other) const;
};

class GestionJoueurs {
public:
  vector<Joueur> joueurs;
  GestionJoueurs();

  void afficherJoueurs();
  void ajouterJoueur(const Joueur& joueur);
  bool supprimerJoueur(const std::string& nom);
  void rechercherJoueur(const std::string& searchTerm) const;
  void trierJoueursParClassement();
  void modifierJoueur(Joueur& joueur); 
};

#endif