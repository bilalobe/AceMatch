#include "MatchSchedule.h"
#include <iostream>

void MatchSchedule::addMatch(const Match& match) {
    matches.push_back(match);
}

std::vector<Match> MatchSchedule::getMatches() const {
    return matches;
}

void MatchSchedule::displaySchedule() const {
    for (const auto& match : matches) {
        match.display();
        std::cout << "------------------" << std::endl;
    }
}
