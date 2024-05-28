#ifndef SCORE_H
#define SCORE_H

#include <QString>

class Score
{
public:
    Score(int id = -1, int matchId = 0, int score1 = 0, int score2 = 0)
        : id(id), matchId(matchId), score1(score1), score2(score2) {} // Inline constructor
    int getId() const { return id; }
    int getMatchId() const { return matchId; }
    int getScore1() const { return score1; }
    int getScore2() const { return score2; }

private:
    int id;
    int matchId;
    int score1;
    int score2;
};

#endif // SCORE_H