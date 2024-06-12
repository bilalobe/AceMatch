#ifndef TERRAIN.H
#define TERRAIN.H

enum TypeTerrain {
    GAZON,
    TERRE_BATTUE,
    ASPHALTE
};

class Terrain
{
public:
    // Constructors
    Terrain(TypeTerrain type, int longueur, int largeur);
    Terrain(TypeTerrain type, int longueur, int largeur, int nbPlacesReservees);

    // Getters
    TypeTerrain getType() const;
    int getLongueur() const;
    int getLargeur() const;
    std::string getNom() const;
    std::vector<std::vector<bool>> getSeatingPlan() const;
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

private:
    TypeTerrain type;
    int longueur;
    int largeur;
    int nbPlacesReservees;
    std::string nom;
    std::vector<std::vector<bool>> seatingPlan; // 2D vector for seating plan
};

#endif