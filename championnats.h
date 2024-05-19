#ifndef CHAMPIONNATS_H
#define CHAMPIONNATS_H

#include <vector>
#include <string>


using namespace std;



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