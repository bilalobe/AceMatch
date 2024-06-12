#ifndef TENNIS_CHAMPIONSHIP_H
#define TENNIS_CHAMPIONSHIP_H

#include <string>
#include <vector>
#include <map>

#include "parties.h"
#include "joueurs.h" 
#include "scores.h"
#include "terrains.h"
#include "reservations.h"


class TennisChampionship {
public:
  TennisChampionship(); 

  // ... Other methods for managing the championship ...
  GestionJoueurs gestionJoueurs;
  GestionTerrains gestionTerrains;
  GestionReservations gestionReservations;
  GestionScores gestionScores;
  GestionParties gestionParties;
  ChampionnatSimple championnat;
  PlanificationParties planificateur;
  GestionClients gestionClients;
  GestionTickets gestionTickets;};

#endif // TENNIS_CHAMPIONSHIP_H