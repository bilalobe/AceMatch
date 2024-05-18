#ifndef TERRAINS_H
#define TERRAINS_H

#include <vector>
#include <string>

enum TypeTerrain
{
  DUR,
  TERRE_BATTUE,
  GAZON
};

class Terrain
{
private:
  TypeTerrain type;
  int longueur;
  int largeur;
  int nbPlacesReservees;
  std::vector<std::vector<bool>> seatingPlan; // 2D vector for seating plan

public:
  // Constructors
  Terrain(TypeTerrain type, int longueur, int largeur);
  Terrain(TypeTerrain type, int longueur, int largeur, int nbPlacesReservees);

  // Getters
  TypeTerrain getType() const;
  int getLongueur() const;
  int getLargeur() const;
  int getNbPlacesReservees() const;

  // Setters
  void setLongueur(int longueur);
  void setLargeur(int largeur);
  void setNbPlacesReservees(int nbPlacesReservees);
  void setTerrain(TypeTerrain type, int longueur, int largeur);
  void setTerrain(TypeTerrain type, int longueur, int largeur, int nbPlacesReservees);

  // Display terrain details
  void afficher() const;

  int getRow() const { return seatingPlan.size(); }    // Return the number of rows
  int getCol() const { return seatingPlan[0].size(); } // Return the number of columns

  // Methods for managing seating
  void initializeSeatingPlan(int rows, int cols);
  bool isSeatAvailable(int row, int col);
  void reserveSeat(int row, int col);
  void releaseSeat(int row, int col);
  void afficherSeatingPlan() const; // Display the seating plan
};

class GestionTerrains
{
private:
  std::vector<Terrain> terrains;

public:
  void ajouterTerrain(Terrain terrain);
  void afficherTerrains();
  bool supprimerTerrain(TypeTerrain type, int longueur, int largeur);
  Terrain *rechercherTerrain(TypeTerrain type, int longueur, int largeur) const;
};

#endif // TERRAINS_H
