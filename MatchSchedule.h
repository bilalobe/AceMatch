#ifndef MATCHSCHEDULE_H
#define MATCHSCHEDULE_H

#include <vector>
#include "scoreboard.h"
#include "Championnats.h"

using namespace std;

class MatchSchedule {
public:
  // Constructor
  MatchSchedule(const ChampionnatSimple& championnat) : championnat(championnat) {}

  // Methods:
  void addMatch(const Match& match);
  void removeMatch(const Match& match);
  void displaySchedule(); 
  void saveSchedule(const string& filename); 
  void loadSchedule(const string& filename); 
  vector<Match> getMatchesForRound(int roundNumber);
  // Helper function to find a match by its ID
  Match* findMatchById(int matchId) const;

  // Helper function to find a match by its players' names
  Match* findMatchByPlayers(const string& player1Name, const string& player2Name) const;

  // Helper function to write the schedule to a file
  Match* writeScheduleToFile(const string& filename) const;

  // Helper function to read the schedule from a file
  Match* readScheduleFromFile(const string& filename);

  // The championship for which the schedule is being created
  const ChampionnatSimple& championnat;

private:
  ChampionnatSimple championnat;
  vector<Match> matches;
};

#endif
