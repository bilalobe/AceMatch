#include "Match.h"
#include <iostream>

Match::Match(TypePartie type, const std::string& player1, const std::string& player2, Terrain* terrain)
    : MatchBase(type, player1, player2, terrain), matchResult(MatchResult::DRAW) {}

void Match::display() const {
    MatchBase::display();
    std::cout << "Match Result: " << matchResult.toString() << std::endl;
}

void Match::setMatchResult(const MatchResult& result) {
    matchResult = result;
}

MatchResult Match::getMatchResult() const {
    return matchResult;
}
