#include "scores.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "joueurs.h"
#include "championnats.h"

// Constructor
Score::Score(const Partie& partie, int scoreJoueur1, int scoreJoueur2)
    : partie(partie), scoreJoueur1(scoreJoueur1), scoreJoueur2(scoreJoueur2) {}

// Display the score
void Score::afficher() const {
    std::cout << "Match: " << partie.getNomJoueur1() << " vs. " << partie.getNomJoueur2() << std::endl;
    std::cout << "Score: " << scoreJoueur1 << " - " << scoreJoueur2 << std::endl;
}

// GestionScores implementation
GestionScores::GestionScores() {}

// Add a score
void GestionScores::ajouterScore(const Score& score) {
    scores.push_back(score);
    scoresMap[score.getPartie().getNumero()] = &scores.back();
}

// Remove a score
void GestionScores::supprimerScore(int numero) {
    auto it = scoresMap.find(numero);
    if (it != scoresMap.end()) {
        scores.erase(std::remove(scores.begin(), scores.end(), *(it->second)), scores.end());
        scoresMap.erase(it);
    }
}

// Update a score
void GestionScores::mettreAJourScore(int numero, int scoreJoueur1, int scoreJoueur2, GestionJoueurs& gestionJoueurs) {
    auto it = scoresMap.find(numero);
    if (it != scoresMap.end()) {
        it->second->setScoreJoueur1(scoreJoueur1);
        it->second->setScoreJoueur2(scoreJoueur2);

        const Partie& partie = it->second->getPartie();

        // Update win/loss records
        if (scoreJoueur1 > scoreJoueur2) {
            gestionJoueurs.updateWin(partie.getNomJoueur1());
            gestionJoueurs.updateLoss(partie.getNomJoueur2());
        } else if (scoreJoueur2 > scoreJoueur1) {
            gestionJoueurs.updateWin(partie.getNomJoueur2());
            gestionJoueurs.updateLoss(partie.getNomJoueur1());
        } else {
            gestionJoueurs.updateLoss(partie.getNomJoueur1());
            gestionJoueurs.updateLoss(partie.getNomJoueur2());
        }
    }
}

// Display all scores
void GestionScores::afficherScores() const {
    for (const Score& score : scores) {
        score.afficher();
        std::cout << std::endl;
    }
}

// Display Top Scorers
std::vector<Score> GestionScores::getTopScores(int numScoresToDisplay) {
    std::vector<Score> topScores = scores; // Make a copy
    std::sort(topScores.begin(), topScores.end(),
                [](const Score& a, const Score& b) {
                    return (a.getScoreJoueur1() + a.getScoreJoueur2()) > (b.getScoreJoueur1() + b.getScoreJoueur2());
                });
    if (numScoresToDisplay > topScores.size()) {
        numScoresToDisplay = topScores.size();
    }
    topScores.resize(numScoresToDisplay);
    return topScores;
}
