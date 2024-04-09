#ifndef JOUEURS_H
#define JOUEURS_H

#include <iostream>
#include <vector>
#include <algorithm> 

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

    void afficher() {
      cout << "Nom: " << nom << endl;
      cout << "Classement: " << classement << endl;
      cout << "Victoires: " << nbVictoires << endl;
      cout << "Défaites: " << nbDefaites << endl;
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

    void afficherJoueurs() {
      for (Joueur joueur : joueurs) {
        joueur.afficher();
        cout << endl;
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
    
};

#endif