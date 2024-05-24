#include "MatchBase.h"
#include <iostream>
#include <stdexcept>

// Static member initialization for next match number
int MatchBase::nextMatchNumber = 1;

// Constructor for MatchBase
MatchBase::MatchBase(TypePartie type, const std::string& player1, const std::string& player2, Terrain* terrain)
    : type(type), player1(player1), player2(player2), result1(DRAW), result2(DRAW), terrain(terrain) {
    number = nextMatchNumber++;
}

// Display a match's details
void MatchBase::display() const {
    std::cout << "Type: " << (type == SIMPLE ? "Simple" : "Double") << std::endl;
    std::cout << "Player 1: " << player1 << std::endl;
    std::cout << "Player 2: " << player2 << std::endl;
    std::cout << "Result 1: " << (result1 == PLAYER1_WON ? "Victory" : (result1 == PLAYER2_WON ? "Defeat" : "Draw")) << std::endl;
    std::cout << "Result 2: " << (result2 == PLAYER2_WON ? "Victory" : (result2 == PLAYER1_WON ? "Defeat" : "Draw")) << std::endl;
    if (terrain) {
        std::cout << "Terrain: " << terrain->getNom() << std::endl;
    } else {
        std::cout << "Terrain: Not specified" << std::endl;
    }
}

// Set the result of a match
void MatchBase::setResult(const std::string& player, int resultAsInt) {
    if (resultAsInt < 0 || resultAsInt > 2) {
        throw std::invalid_argument("Invalid result value. Must be between 0 and 2.");
    }
    MatchResult actualResult = static_cast<MatchResult>(resultAsInt);

    if (player == player1) {
        result1 = actualResult;
    } else if (player == player2) {
        result2 = actualResult;
    } else {
        throw std::invalid_argument("Player name does not match any participants in the match.");
    }
}
