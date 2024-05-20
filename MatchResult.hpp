#include "MatchResult.h"

MatchResult::MatchResult(MatchResultEnum result) : result(result) {}

void MatchResult::setResult(MatchResultEnum result) {
    this->result = result;
}

MatchResultEnum MatchResult::getResult() const {
    return result;
}

std::string MatchResult::toString() const {
    switch (result) {
        case MatchResultEnum::DRAW:
            return "Draw";
        case MatchResultEnum::PLAYER1_WON:
            return "Player 1 Won";
        case MatchResultEnum::PLAYER2_WON:
            return "Player 2 Won";
        default:
            return "Unknown";
    }
}
