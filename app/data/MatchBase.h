#ifndef MATCHBASE_H
#define MATCHBASE_H

#include <string>

#include "Terrain.h"
#include "MatchResult.h"
#include "Partie.h"


class MatchBase {
public:
    MatchBase(TypePartie type, const std::string& player1, const std::string& player2, Terrain* terrain = nullptr);
    
    virtual void display() const;
    int getNumber() const { return number; }
    std::string getPlayer1() const { return player1; }
    std::string getPlayer2() const { return player2; }
    TypePartie getType() const { return type; }
    Terrain* getTerrain() const { return terrain; }
    
    void setNumber(int number) { this->number = number; }
    void setPlayer1(const std::string& player1) { this->player1 = player1; }
    void setPlayer2(const std::string& player2) { this->player2 = player2; }
    void setResult(const std::string& player, int resultAsInt);

    MatchResult getResult1() const { return result1; }
    MatchResult getResult2() const { return result2; }

protected:
    TypePartie type;
    std::string player1;
    std::string player2;
    MatchResult result1;
    MatchResult result2;
    int number;
    static int nextMatchNumber;
    Terrain* terrain;
};

#endif // MATCHBASE_H
