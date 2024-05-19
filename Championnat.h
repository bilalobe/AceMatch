#ifndef CHAMPIONNAT_H
#define CHAMPIONNAT_H

#include "Joueur.h"
#include "Ticket.h"

#include<string>
#include<vector>

class Championnat {

private:
  string nom;      // Declare the members 
  int annee;
  int nbTours;
  TennisChampionship* tennisChampionship; // Declare tennisChampionship as a member 
  vector<Joueur> joueursInscrits; // Add a vector to store the players

public:
    std::vector<Joueur> joueursInscrits; // Enrolled players
    std::vector<Partie> parties; // Played matches
    std::vector<Ticket> tickets; // Tickets sold

    // Constructor
    Championnat::Championnat(const string& nom, int annee, int nbTours);

    // Method to add players to the tournament
    void inscrireJoueur(const Joueur& joueur);

    // Method to get the list of enrolled players
    const std::vector<Joueur>& getJoueursInscrits() const;

    // Getters and Setters
    string getNom() const { return nom; }
    int getAnnee() const { return annee; }
    int getNbTours() const { return nbTours; }
    TennisChampionship* getTennisChampionship() const { return tennisChampionship; } // Getter for tennisChampionship
    void setNom(const string& nom) { this->nom = nom; }
    void setAnnee(int annee) { this->annee = annee; }
    void setNbTours(int nbTours) { this->nbTours = nbTours; }
};

#endif