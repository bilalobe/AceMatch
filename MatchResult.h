#ifndef MATCHRESULT_H
#define MATCHRESULT_H

#include "Match.h"


class MatchResult {
public:
  // Constructor
  MatchResult(const Match& match, int scorePlayer1, int scorePlayer2);

  // Methods:
  void displayResult();
  Joueur* getWinner();
  Joueur* getLoser();
  int getScorePlayer1();
  int getScorePlayer2();

private:
  Match match;
  int scorePlayer1;
  int scorePlayer2;
};

#endif // MATCHRESULT_H