#ifndef SCORE_H
#define SCORE_H

#include <map>
#include <string>
#include "Scoreboard.h"

class Score {
public:
    void updateScore(const std::string& player, int score);
    int getScore(const std::string& player) const;
    void displayScores() const;

private:
    std::map<std::string, int> scores;
};

#endif // SCOREBOARD_H
