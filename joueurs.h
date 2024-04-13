#ifndef JOUEURS_H
#define JOUEURS_H

#include <iostream>
#include <vector>
#include <algorithm> 
#include "personne.h"

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

    // Getters
    string getNom() const; 
    int getClassement() const;

    // Setters
    void setNom(string nom);
    void setClassement(int classement);

    void afficher(Joueur* joueur) {
      cout << "Nom: " << joueur->nom << endl;
      cout << "Classement: " << joueur->classement << endl;
      cout << "Victoires: " << joueur->nbVictoires << endl;
      cout << "Défaites: " << joueur->nbDefaites << endl;
    }

    void incrementerVictoire() {
      nbVictoires++;
    }

    void incrementerDefaite() {
      nbDefaites++;
    }

    bool operator==(const Joueur& other) const {
      return nom == other.nom;
    }
};

class GestionJoueurs {
  public:
    vector<Joueur> joueurs;
    
    void afficherJoueurs() const {
      for (Joueur joueur : joueurs) {
        joueur.afficher(&joueur);
      }
    }

    void ajouterJoueur(Joueur joueur) {
      joueurs.push_back(joueur);
    }

    void supprimerJoueur(string nom) {
      for (int i = 0; i < joueurs.size(); i++) {
        if (joueurs[i].nom == nom) {
          joueurs.erase(joueurs.begin() + i);
          break;
        }
      }
    }
    Joueur* rechercherJoueur(string nom) {
      for (Joueur joueur : joueurs) {
        if (joueur.nom == nom) {
          return &joueur;
        }
      }
      return nullptr;
    }

    void trierJoueursParClassement() {
    std::sort(joueurs.begin(), joueurs.end(), [](Joueur joueur1, Joueur joueur2) {
      return joueur1.classement > joueur2.classement;
    });
  }
    void modifierJoueur(Joueur& joueur){
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
