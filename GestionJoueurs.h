#ifndef GESTIONJOUEURS_H
#define GESTIONJOUEURS_H

#include <vector>
#include <string>
#include "Joueur.h"

class GestionJoueurs {
private:
    std::vector<Joueur> joueurs;
    
public:
    GestionJoueurs();

    // Accessors
    const std::vector<Joueur>& getJoueurs() const;

    // Methods for managing players
    void afficherJoueurs();
    void ajouterJoueur(const Joueur& joueur);
    bool supprimerJoueur(const std::string& nom);
    Joueur* rechercherJoueur(const std::string& nom);
    void trierJoueursParClassement();
    void modifierJoueur(Joueur& joueur);

    // Methods to update wins and losses
    void updateWin(const std::string& playerName);
    void updateLoss(const std::string& playerName);
};

#endif