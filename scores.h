#ifndef SCORES_H
#define SCORES_H

#include <vector>
#include <map>
#include "parties.h"
#include "joueurs.h"

class Score {
public:
    Score(const Partie& partie, int scoreJoueur1, int scoreJoueur2); // Constructor

    const Partie& getPartie() const { return partie; } // Getter for Partie
    int getScoreJoueur1() const { return scoreJoueur1; } // Getter for scoreJoueur1
    int getScoreJoueur2() const { return scoreJoueur2; } // Getter for scoreJoueur2

    void setScoreJoueur1(int score) { scoreJoueur1 = score; } // Setter for scoreJoueur1
    void setScoreJoueur2(int score) { scoreJoueur2 = score; } // Setter for scoreJoueur2

    void afficher() const; // Display the score

private:
    const Partie& partie;
    int scoreJoueur1;
    int scoreJoueur2;
};

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

#endif // SCORES_H
