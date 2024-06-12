#ifndef JOUEURS_H
#define JOUEURS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Joueur {
    
public:
    std::string nom;
    int classement;
    int nbVictoires;
    int nbDefaites;

public:
    // Constructor 1: Initialize with name and ranking
    Joueur(const std::string& nom, int classement);

    // Constructor 2: Initialize with just a name (ranking is optional)
    Joueur(const std::string& nom);

    // Getters and Setters
    std::string getNom() const;
    int getClassement() const;
    void setNom(std::string nom);
    void setClassement(int classement);
    int getNbVictoires() const;
    int getNbDefaites() const;
    void setNbVictoires(int nbVictoires);
    void setNbDefaites(int nbDefaites);

    // Methods to increment wins and losses
    void incrementerVictoire();
    void incrementerDefaite();

    // Operator overloading for comparison
    bool operator==(const Joueur& other) const;


};
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

#endif // JOUEURS_H
