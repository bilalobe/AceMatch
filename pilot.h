#ifndef TENNIS_CHAMPIONSHIP_H
#define TENNIS_CHAMPIONSHIP_H

#include <string>
#include <vector>
#include <map>

#include "parties.h"
#include "joueurs.h" 
#include "scores.h"
#include "planner.h"
#include "TennisEvent.h"
#include "terrains.h"
#include "reservations.h"
#include "TournamentRanking.h"
#include "MatchSchedule.h"


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


  GestionJoueurs gestionJoueurs;
  GestionTerrains gestionTerrains;
  GestionReservations gestionReservations;
  GestionScores gestionScores;
  GestionParties gestionParties;
  ChampionnatSimple championnat;
  PlanificationParties planificateur;
  GestionClients gestionClients;
  TennisEvent* tennisEvent;
    MatchSchedule schedule; // Store the match schedule
  TournamentRanking rankings; // Store the tournament rankings
  GestionTickets gestionTickets;};

#endif // TENNIS_CHAMPIONSHIP_H