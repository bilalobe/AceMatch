#ifndef TOURNAMENTSCHEDULER_H
#define TOURNAMENTSCHEDULER_H

#include "data/Player.h"
#include "data/Game.h"
#include "data/TennisChampionship.h"

class TournamentScheduler
{
private:
    TennisChampionship *tennisChampionship;
    TypePartie matchType;

public:
    TournamentScheduler(TennisChampionship *tennisChampionship);
    ~TournamentScheduler() {} // Destructor

    void createTournament(int nbRounds); // renamed from createTournament(...)
    void createRoundOf16();              // renamed from createRoundOf16()
    void createRound(int round);
    void createFinalMatch();             // renamed from createFinalMatch()

    std::vector<Player> getWinnersFromPreviousRound();

    // Match Type Management
    TypePartie getMatchType() const { return matchType; }
    void setMatchType(TypePartie type) { matchType = type; }
};

#endif // TOURNAMENTSCHEDULER_H