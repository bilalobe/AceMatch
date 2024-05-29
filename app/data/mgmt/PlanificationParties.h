#ifndef PLANIFICATIONPARTIES_H
#define PLANIFICATIONPARTIES_H

#include <vector>
#include "data/Joueur.h"
#include "data/Partie.h"
#include "data/TennisChampionship.h"

class PlanificationParties
{
private:
    TennisChampionship *tennisChampionship;
    TypePartie matchType;

public:
    PlanificationParties(TennisChampionship *tennisChampionship);
    ~PlanificationParties() {} // Destructor

    void creerTournoi(int nbRounds);
    void creerParties16emes();
    void creerRound(int round);
    void creerPartieFinale();

    std::vector<Joueur> getWinnersFromPreviousRound();

    // Match Type Management
    TypePartie getMatchType() const { return matchType; }
    void setMatchType(TypePartie type) { matchType = type; }
};

#endif // PLANIFICATIONPARTIES_H
