#ifndef TENNIS_CHAMPIONSHIP_H
#define TENNIS_CHAMPIONSHIP_H

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "MatchSchedule.h"
#include "TournamentRanking.h"
#include "Championnat.h"
#include "MatchResult.h"
#include "Match.h"
#include "Ticket.h"
#include "Reservation.h"
#include "MatchBase.h"



class TennisChampionship
{
public:
  TennisChampionship();
  void addMatch(std::shared_ptr<MatchBase> match);
  void displayMatches() const;
  void TennisChampionship::scheduleMatches(int championshipIndex, int round);
  MatchSchedule createMatchSchedule(const TennisChampionship &championnat);
  void scheduleMatch(const Match &match);
  MatchSchedule &getMatchSchedule(); // Return a reference to the schedule

  // Methods for managing tournament rankings
  TournamentRanking createTournamentRankings(const TennisChampionship &championnat);
  void updateTournamentRankings(const MatchResult &matchResult);
  TournamentRanking &getTournamentRankings(); // Return a reference to the rankings

  // Methods for saving/loading championship data
  void saveChampionshipData(const std::string &filename);
  void loadChampionshipData(const std::string &filename);

  // Methods for ticket management (examples)
  Ticket generateTicket(const std::string &ticketType, double price, const std::string &matchName, Reservation *reservation);
  bool sellTicket(int ticketNumber);



private:
  std::vector<std::shared_ptr<MatchBase>> matches;
  MatchSchedule matchSchedule;
  TournamentRanking tournamentRankings;
}

#endif