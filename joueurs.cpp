#include "joueurs.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Constructor 1: Initialize with name and ranking
Joueur::Joueur(const std::string& nom, int classement)
  : nom(nom), classement(classement), nbVictoires(0), nbDefaites(0) {}

// Constructor 2: Initialize with just a name (ranking is optional)
Joueur::Joueur(const std::string& nom)
  : nom(nom), classement(0), nbVictoires(0), nbDefaites(0) {}

// Getters for Joueur
std::string Joueur::getNom() const {
  return nom;
}

int Joueur::getClassement() const {
  return classement;
}

int Joueur::getNbVictoires() const {
  return nbVictoires;
}

int Joueur::getNbDefaites() const {
  return nbDefaites;
}

// Setters for Joueur
void Joueur::setNom(std::string nom) {
  this->nom = nom;
}

void Joueur::setClassement(int classement) {
  this->classement = classement;
}

void Joueur::setNbVictoires(int nbVictoires) {
  this->nbVictoires = nbVictoires;
}

void Joueur::setNbDefaites(int nbDefaites) {
  this->nbDefaites = nbDefaites;
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

// Accessor for players list
const std::vector<Joueur>& GestionJoueurs::getJoueurs() const {
  return joueurs;
}

// Display players in GestionJoueurs
void GestionJoueurs::afficherJoueurs() {
  if (joueurs.empty()) {
    cout << "No players found." << endl;
    return;
  }
  for (const Joueur& joueur : joueurs) {
    cout << "Name: " << joueur.getNom() << endl;
    cout << "Ranking: " << joueur.getClassement() << endl;
    cout << "Wins: " << joueur.getNbVictoires() << endl;
    cout << "Losses: " << joueur.getNbDefaites() << endl;
    cout << endl;
  }
}

// Add a player to GestionJoueurs
void GestionJoueurs::ajouterJoueur(const Joueur& joueur) {
  if (joueur.getNom().empty()) {
    throw std::invalid_argument("Player name cannot be empty.");
  }
  for (const Joueur& j : joueurs) {
    if (j.getNom() == joueur.getNom()) {
      throw std::invalid_argument("Player already exists.");
    }
  }
  joueurs.push_back(joueur);
}

// Remove a player from GestionJoueurs
bool GestionJoueurs::supprimerJoueur(const std::string& nom) {
  auto it = std::remove_if(joueurs.begin(), joueurs.end(),
                           [&nom](const Joueur& joueur) { return joueur.getNom() == nom; });
  if (it != joueurs.end()) {
    joueurs.erase(it, joueurs.end());
    return true;
  }
  return false;
}

// Search for a player in GestionJoueurs
Joueur* GestionJoueurs::rechercherJoueur(const std::string& nom) {
  for (Joueur& joueur : joueurs) {
    if (joueur.getNom() == nom) {
      return &joueur;
    }
  }
  return nullptr;
}

// Sort players in GestionJoueurs by ranking
void GestionJoueurs::trierJoueursParClassement() {
  std::sort(joueurs.begin(), joueurs.end(), [](const Joueur& joueur1, const Joueur& joueur2) {
    return joueur1.getClassement() > joueur2.getClassement();
  });
}

// Modify a player's information in GestionJoueurs
void GestionJoueurs::modifierJoueur(Joueur& joueur) {
  for (Joueur& j : joueurs) {
    if (j.getNom() == joueur.getNom()) {
      j.setNom(joueur.getNom());
      j.setClassement(joueur.getClassement());
      j.setNbVictoires(joueur.getNbVictoires());
      j.setNbDefaites(joueur.getNbDefaites());
      return;
    }
  }
}

// Update win count for a player in GestionJoueurs
void GestionJoueurs::updateWin(const std::string& playerName) {
  for (Joueur& joueur : joueurs) {
    if (joueur.getNom() == playerName) {
      joueur.incrementerVictoire();
      return;
    }
  }
}

// Update loss count for a player in GestionJoueurs
void GestionJoueurs::updateLoss(const std::string& playerName) {
  for (Joueur& joueur : joueurs) {
    if (joueur.getNom() == playerName) {
      joueur.incrementerDefaite();
      return;
    }
  }
}
