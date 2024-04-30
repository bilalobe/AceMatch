#ifndef JOUEURS_H
#define JOUEURS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "personne.h"
#include "scores.h"

using namespace std;

class Joueur {
public:
  std::string nom;
  int classement;
  int nbVictoires;
  int nbDefaites;

  Joueur(string nom, int classement) {
    this->nom = nom;
    this->classement = classement;
    this->nbVictoires = 0;
    this->nbDefaites = 0;
  }
  Joueur(std::string nom) : nom(nom), classement(0), nbVictoires(0), nbDefaites(0) {}

  string Joueur::getNom() const { return nom; }

  int Joueur::getClassement() const { return classement; }

  void Joueur::setNom(string nom) { this->nom = nom; }

  void Joueur::setClassement(int classement) { this->classement = classement; }

  void afficher(const Joueur* joueur) {
    cout << "Nom: " << joueur->nom << endl;
    cout << "Classement: " << joueur->classement << endl;
    cout << "Victoires: " << joueur->nbVictoires << endl;
    cout << "Défaites: " << joueur->nbDefaites << endl;
  }

  void incrementerVictoire() { nbVictoires++; }

  void incrementerDefaite() { nbDefaites++; }

  bool operator==(const Joueur& other) const { return nom == other.nom; }
};

class GestionJoueurs {
public:
  vector<Joueur> joueurs;

  void afficherJoueurs() {
    if (joueurs.empty()) {
      cout << "No players found." << endl;
      return;
    }

    for (Joueur joueur : joueurs) {
      cout << "Name: " << joueur.getNom() << endl;
      cout << "Ranking: " << joueur.getClassement() << endl;
      cout << "Wins: " << joueur.nbVictoires << endl;
      cout << "Losses: " << joueur.nbDefaites << endl;

      cout << endl;
    }
  }


  void ajouterJoueur(const Joueur& joueur) {
      if (joueur.nom.empty()) {
          throw std::invalid_argument("Player name cannot be empty.");
      }

      for (Joueur& j : joueurs) {
          if (j.nom == joueur.nom) {
              throw std::invalid_argument("Player already exists.");
          }
      }
    joueurs.push_back(joueur); 
  }

  void supprimerJoueur(const std::string& nom) {
    for (int i = 0; i < joueurs.size(); i++) {
      if (joueurs[i].nom == nom) {
        joueurs.erase(joueurs.begin() + i);
        break;
      }
    }
  }
  void rechercherJoueur() {
    cout << "Enter player name (or part of name) to search: ";
    string searchTerm;
    cin >> searchTerm;

    bool found = false;
    for (Joueur& joueur : joueurs) {
      if (joueur.getNom().find(searchTerm) != string::npos) {  // Case-insensitive partial match
        joueur.afficher(const_cast<Joueur*>(&joueur));  // Customize how you display the player
        found = true;
      }
    }
    if (!found) {
      cout << "Player not found." << endl;
    }
  }

  void trierJoueursParClassement() {
    std::sort(joueurs.begin(), joueurs.end(), [](Joueur joueur1, Joueur joueur2) {
      return joueur1.classement > joueur2.classement;
    });
  }
  void modifierJoueur(Joueur& joueur) {
    for (int i = 0; i < joueurs.size(); i++) {
      if (joueurs[i].nom == joueur.nom) {
        joueurs[i].nom = joueur.nom;
        joueurs[i].classement = joueur.classement;
        break;
      }
    }
  }
};

#endif
