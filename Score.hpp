#include "Score.h"

void Score::updateScore(const std::string& player, int score) {
    scores[player] = score;
}

int Score::getScore(const std::string& player) const {
    auto it = scores.find(player);
    if (it != scores.end()) {
        return it->second;
    }
    return 0;
}

void Score::displayScores() const {
    for (const auto& entry : scores) {
        std::cout << "Player: " << entry.first << ", Score: " << entry.second << std::endl;
    }
}