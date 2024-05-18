#ifndef JOUEURS_H
#define JOUEURS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "scores.h"

using namespace std;

class Joueur {
public:
  Joueur(const std::string& nom, int classement);

  Joueur(const std::string& nom); 

  std::string nom;
  int classement;
  int nbVictoires;
  int nbDefaites;


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
  
  const std::vector<Joueur>& getJoueurs() const; 
  void afficherJoueurs();
  void ajouterJoueur(const Joueur& joueur);
  bool supprimerJoueur(const std::string& nom);
  Joueur* GestionJoueurs::rechercherJoueur(const std::string& nom);
  void trierJoueursParClassement();
  void modifierJoueur(Joueur& joueur);
};

#endif 