#ifndef TERRAINS_H
#define TERRAINS_H

#include <vector>
#include <string>

enum TypeTerrain {
  DUR,
  TERRE_BATTUE,
  GAZON
};

class Terrain {
public:
  Terrain(TypeTerrain type, int longueur, int largeur);
  Terrain(TypeTerrain type, int longueur, int largeur, int nbPlacesReservees);
  TypeTerrain getType() const;
  void getLongueur(int& longueur) const;
  void getLargeur(int& largeur) const;
  void getNbPlacesReservees(int& nbPlacesReservees) const;
  void setLongueur(int longueur);
  void setLargeur(int largeur);
  void setNbPlacesReservees(int nbPlacesReservees);
  void setTerrain(TypeTerrain type, int longueur, int largeur);
  void setTerrain(TypeTerrain type, int longueur, int largeur, int nbPlacesReservees);
  void afficher(int longueur, int largeur, int nbPlacesReservees) const;
  void afficher() const;

  // Methods for seating plan management
  void initializeSeatingPlan(int rows, int cols); 
  bool isSeatAvailable(int row, int col) const;
  void reserveSeat(int row, int col); 
  void releaseSeat(int row, int col);

private:
  TypeTerrain type;
  int longueur;
  int largeur;
  int nbPlacesReservees; // Number of reserved places
  std::vector<std::vector<bool>> seatingPlan; // 2D vector to represent seating 
};

class GestionTerrains {
public:
  void ajouterTerrain(Terrain terrain);
  void afficherTerrains();
  bool supprimerTerrain(TypeTerrain type, int longueur, int largeur);
  Terrain* rechercherTerrain(TypeTerrain type, int longueur, int largeur) const;

private:
  std::vector<Terrain> terrains; 
};

#endif
