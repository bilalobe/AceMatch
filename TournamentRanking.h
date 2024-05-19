#ifndef TOURNAMENT_RANKING_H
#define TOURNAMENT_RANKING_H

#include <vector>
#include <string>
#include "championnats.h"
#include "joueurs.h"


class TournamentRanking {
public:
  // Constructor
  TournamentRanking(const ChampionnatSimple& championnat) : championnat(championnat) {}

  // Methods:
  void updateRanking(const Match& match); // Update rankings based on match results
  void displayRankings(); // Display current rankings
  void saveRankings(const string& filename); // Save rankings to a file
  void loadRankings(const string& filename); // Load rankings from a file
  Joueur* getRankedPlayer(int rank); // Get the player at a given rank

private:
  ChampionnatSimple championnat;
  vector<Joueur*> rankedPlayers; // Or a more suitable data structure for efficient ranking
};

#endif