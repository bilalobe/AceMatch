#ifndef JOUEUR.H
#define JOUEUR.H

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

#endif