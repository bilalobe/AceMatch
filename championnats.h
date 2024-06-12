#ifndef CHAMPIONNATS_H
#define CHAMPIONNATS_H

#include <vector>
#include <string>
#include "parties.h"
#include "tickets.h"
#include "joueurs.h"
#include "scores.h"
#include "tennis_championnat.h" // Include the TennisChampionship header

using namespace std;

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
    Championnat(const std::string& nom, int annee, int nbTours);

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
    // No setter for tennisChampionship - it's managed internally
};

class ChampionnatSimple : public Championnat {
public:
    std::vector<Joueur> joueurs; // Players in the tournament
    // Constructor
    ChampionnatSimple(const std::string& nom, int annee, int nbTours);

    // Method to add players to the tournament
    void ajouterJoueur(const Joueur& joueur);

    // Method to remove players from the tournament
    void supprimerJoueur(const std::string& nom);

    // Method to add matches to the tournament
    void ajouterPartie(const Partie& partie);

    // Method to remove matches from the tournament
    void supprimerPartie(int numero);

    // Method to add tickets to the tournament
    void ajouterTicket(const Ticket& ticket);

    // Method to remove tickets from the tournament
    void supprimerTicket(int numero);

    // Method to display the tournament information
    void afficherChampionnat();
};

#endif // CHAMPIONNATS_H