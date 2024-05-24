#ifndef PLANIFICATION_PARTIES.H
#define PLANIFICATION_PARTIES.H

#include <vector>

#include "Joueur.h"
#include "Partie.h"

enum TypeTerrain
{
  DUR,
  TERRE_BATTUE,
  GAZON
};

class SeatingPlan{


  // Methods for managing seating
  void initializeSeatingPlan(int rows, int cols);
  bool isSeatAvailable(int row, int col);
  void reserveSeat(int row, int col);
  void releaseSeat(int row, int col);
  void displaySeatingPlan() const; // Display the seating plan

  
};

#endif