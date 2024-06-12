#ifndef MATCH_H
#define MATCH_H

#include "MatchBase.h"
#include "MatchResult.h"

class Match : public MatchBase {
public:
    Match(TypePartie type, const std::string& player1, const std::string& player2, Terrain* terrain = nullptr);

    void display() const override;
    void setMatchResult(const MatchResult& result);
    MatchResult getMatchResult() const;

private:
    MatchResult matchResult;
};

#endif // MATCH_H
