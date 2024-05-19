#ifndef PLANIFICATION_PARTIES_H
#define PLANIFICATION_PARTIES_H

#include "parties.h"
#include "championnats.h"
#include "pilot.h"
#include "joueurs.h"
#include <vector>
#include <random>
// ... other includes ...

class PlanificationParties {
private:
  TennisChampionship* tennisChampionship;
  std::vector<Joueur*> joueurs;
   void creerParties16emes();
public:
  PlanificationParties(TennisChampionship* tennisChampionship); 
};

#endif // PLANIFICATION_PARTIES_H