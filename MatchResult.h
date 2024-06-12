#ifndef MATCHRESULT_H
#define MATCHRESULT_H

#include <string>

enum class MatchResultEnum {
    DRAW,
    PLAYER1_WON,
    PLAYER2_WON
};

class MatchResult {
public:
    MatchResult(MatchResultEnum result = MatchResultEnum::DRAW);

    void setResult(MatchResultEnum result);
    MatchResultEnum getResult() const;
    std::string toString() const;

private:
    MatchResultEnum result;
};

#endif // MATCHRESULT_H
