#include "Scoreboard.h"

void Scoreboard::ajouterScore(const std::string& joueur1, const std::string& joueur2, int score1, int score2) {
    scores[joueur1][joueur2] = score1;
    scores[joueur2][joueur1] = score2;
}

void Scoreboard::afficherScores() const {
    for (const auto& match : scores) {
        for (const auto& result : match.second) {
            std::cout << match.first << " vs " << result.first << " : " << result.second << std::endl;
        }
    }
}

void Scoreboard::sauvegarderScores(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& match : scores) {
            for (const auto& result : match.second) {
                outFile << match.first << "," << result.first << "," << result.second << std::endl;
            }
        }
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

void Scoreboard::chargerScores(const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string joueur1, joueur2;
        int score;
        while (inFile >> joueur1 >> joueur2 >> score) {
            scores[joueur1][joueur2] = score;
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
}
