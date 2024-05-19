#ifndef TENNIS_CHAMPIONSHIP_H
#define TENNIS_CHAMPIONSHIP_H

#include <string>
#include <vector>
#include <map>


#include "TennisEvent.h"



class TennisChampionship {
public:
  TennisChampionship(); 
  void TennisChampionship::scheduleMatches(int championshipIndex, int round) ;
 MatchSchedule createMatchSchedule(const ChampionnatSimple& championnat);
  void scheduleMatch(const Match& match);
  MatchSchedule& getMatchSchedule(); // Return a reference to the schedule

  // Methods for managing tournament rankings
  TournamentRanking createTournamentRankings(const ChampionnatSimple& championnat);
  void updateTournamentRankings(const MatchResult& matchResult);
  TournamentRanking& getTournamentRankings(); // Return a reference to the rankings

  // Methods for saving/loading championship data
  void saveChampionshipData(const string& filename);
  void loadChampionshipData(const string& filename);

  // Methods for ticket management (examples)
  Ticket generateTicket(const string& ticketType, double price, const string& matchName, Reservation* reservation);
  bool sellTicket(int ticketNumber);


}

#endif 