#include "joueurs.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Constructor for Joueur
Joueur::Joueur(string nom, int classement) {
  this->nom = nom;
  this->classement = classement;
  this->nbVictoires = 0;
  this->nbDefaites = 0;
}

// Constructor for Joueur (with only name)
Joueur::Joueur(std::string nom) : nom(nom), classement(0), nbVictoires(0), nbDefaites(0) {}

// Getters for Joueur
string Joueur::getNom() const {
  return nom;
}
int Joueur::getClassement() const {
  return classement;
}

// Setters for Joueur
void Joueur::setNom(string nom) {
  this->nom = nom;
}
void Joueur::setClassement(int classement) {
  this->classement = classement;
}

// Increment win count for Joueur
void Joueur::incrementerVictoire() {
  nbVictoires++;
}

// Increment loss count for Joueur
void Joueur::incrementerDefaite() {
  nbDefaites++;
}

// Operator overloading for Joueur comparison
bool Joueur::operator==(const Joueur& other) const {
  return nom == other.nom;
}

// GestionJoueurs implementation
GestionJoueurs::GestionJoueurs() {}

// Display players in GestionJoueurs
void GestionJoueurs::afficherJoueurs() {
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

// Add a player to GestionJoueurs
void GestionJoueurs::ajouterJoueur(const Joueur& joueur) {
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

// Remove a player from GestionJoueurs
bool GestionJoueurs::supprimerJoueur(const std::string& nom) {
  for (int i = 0; i < joueurs.size(); i++) {
    if (joueurs[i].nom == nom) {
      joueurs.erase(joueurs.begin() + i);
      return true; // Player found and deleted
    }
  }
  return false; // Player not found
}

// Search for a player in GestionJoueurs
void GestionJoueurs::rechercherJoueur(const std::string& searchTerm) const {
  auto it = std::find_if(joueurs.begin(), joueurs.end(),
                         [&searchTerm](const Joueur& joueur) {
                           return joueur.getNom().find(searchTerm) != std::string::npos;
                         });
  if (it != joueurs.end()) {
    std::cout << "Player found:" << std::endl;
    std::cout << "Nom: " << it->nom << std::endl; 
    std::cout << "Classement: " << it->classement << std::endl;
  } else {
    std::cout << "Player not found." << std::endl;
  }
}

// Sort players in GestionJoueurs by ranking
void GestionJoueurs::trierJoueursParClassement() {
  std::sort(joueurs.begin(), joueurs.end(), [](Joueur joueur1, Joueur joueur2) {
    return joueur1.classement > joueur2.classement;
  });
}

// Modify a player's information in GestionJoueurs
void GestionJoueurs::modifierJoueur(Joueur& joueur) {
  for (int i = 0; i < joueurs.size(); i++) {
    if (joueurs[i].nom == joueur.nom) {
      joueurs[i].nom = joueur.nom;
      joueurs[i].classement = joueur.classement;
      return; // Player found and modified
    }
  }
}