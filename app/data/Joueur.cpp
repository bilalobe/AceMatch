#include "Joueur.h"

namespace Tournament {

Joueur::Joueur(const QString& nom, int rang) :
    nom(nom),
    rang(rang),
    victoires(0),
    defaites(0) 
{}

QString Joueur::getNom() const { return nom; }
int Joueur::getRang() const { return rang; }
int Joueur::getVictoires() const { return victoires; }
int Joueur::getDefaites() const { return defaites; }

void Joueur::setNom(const QString& nom) { this->nom = nom; }
void Joueur::setRang(int rang) { this->rang = rang; }
void Joueur::setVictoires(int victoires) { this->victoires = victoires; }
void Joueur::setDefaites(int defaites) { this->defaites = defaites; }

} // namespace Tournament 