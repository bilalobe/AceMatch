#include "GestionJoueurs.h"
#include <algorithm>
#include <iostream>


// Default constructor
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
