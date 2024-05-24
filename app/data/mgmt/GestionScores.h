#ifndef GESTION_SCORES_H
#define GESTION_SCORES_H

#include <vector>
#include "Score.h"
#include "Partie.h"


class GestionScores {
public:
    GestionScores(); // Constructor

    void ajouterScore(const Score& score); // Add a score
    void supprimerScore(int numero); // Remove a score
    void mettreAJourScore(int numero, int scoreJoueur1, int scoreJoueur2, GestionJoueurs& gestionJoueurs); // Update a score
    void afficherScores() const; // Display all scores
    std::vector<Score> getTopScores(int numScoresToDisplay); // Display Top Scorers

private:
    std::vector<Score> scores;
    std::map<int, Score*> scoresMap;
};


#endif // GESTION_SCORES_H
