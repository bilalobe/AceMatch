#ifndef MATCH_H
#define MATCH_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Player.h" 

class Match
{
public:
    Match(const Player& player1 = Player(), const Player& player2 = Player(), int score1 = 0, int score2 = 0, int id = -1)
        : id(id), player1(player1), player2(player2), score1(score1), score2(score2) {} // Inline constructor
    int getId() const { return id; }
    const Player& getPlayer1() const { return player1; }
    const Player& getPlayer2() const { return player2; }
    int getScore1() const { return score1; }
    int getScore2() const { return score2; }

private:
    int id;
    Player player1;
    Player player2;
    int score1;
    int score2;
};

#endif // MATCH_H