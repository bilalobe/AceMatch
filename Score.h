#ifndef SCORE.H
#define SCORE.H

#include "Partie.h"

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
#endif // SCORE.H