#ifndef PLANIFICATION_PARTIES_H
#define PLANIFICATION_PARTIES_H

#include "parties.h"
#include "championnats.h"
#include "tennis_championnat.cpp"
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