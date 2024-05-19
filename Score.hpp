#include "Score.h"

Score::Score(const Partie& partie, int scoreJoueur1, int scoreJoueur2)
    : partie(partie), scoreJoueur1(scoreJoueur1), scoreJoueur2(scoreJoueur2) {}

// Display the score
void Score::afficher() const {
    std::cout << "Match: " << partie.getNomJoueur1() << " vs. " << partie.getNomJoueur2() << std::endl;
    std::cout << "Score: " << scoreJoueur1 << " - " << scoreJoueur2 << std::endl;
}
