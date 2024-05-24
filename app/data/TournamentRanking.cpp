#include "TournamentRanking.h"
#include <iostream>

void TournamentRanking::ajouterMatch(const std::string &joueur1, const std::string &joueur2, int score1, int score2) {
    int points1 = (score1 > score2) ? 3 : (score1 == score2) ? 1 : 0;
    int points2 = (score2 > score1) ? 3 : (score1 == score2) ? 1 : 0;

    mettreAJourClassement(joueur1, points1);
    mettreAJourClassement(joueur2, points2);
}

void TournamentRanking::mettreAJourClassement(const std::string &joueur, int points) {
    if (classement.find(joueur) == classement.end()) {
        classement[joueur] = 0;
    }
    classement[joueur] += points;
}

void TournamentRanking::afficherClassement() const {
    std::cout << "Classement du tournoi:\n";
    for (const auto &entry : classement) {
        std::cout << entry.first << " : " << entry.second << " points\n";
    }
}
