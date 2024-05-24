#ifndef PLANIFICATION_PARTIES_H
#define PLANIFICATION_PARTIES_H


#include <vector>
#include <random>

#include "GestionParties.h"
#include "Joueur.h"
#include "Tennis.h"

class PlanificationParties {
private:
  TennisChampionship* tennisChampionship;
  std::vector<Joueur*> joueurs;
   void creerParties16emes();

  
public:
  PlanificationParties(TennisChampionship* tennisChampionship); 
};

#endif // PLANIFICATION_PARTIES_H