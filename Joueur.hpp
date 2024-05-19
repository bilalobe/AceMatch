#include "Joueur.h"


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
