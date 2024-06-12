#ifndef PLACES_H
#define PLACES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Définition de la classe Place
class Place {
public:
  string type;
  double prix;

public:
  Place(string type, double prix);
  void afficher() const;
  string getType() const;
  double getPrix() const;
};

// Définition de la classe StandardPlace
class StandardPlace : public Place {
public:
  StandardPlace(int numero);

  void afficher() const;
  int getNumero() const;

private:
  int numero;
};

// Définition de la classe VipPlace
class VipPlace : public Place {
public:
  VipPlace(int numero);

  void afficher() const;
  int getNumero() const;

private:
  int numero;
};

// GestionPlaces class (Now in places.h)
class GestionPlaces {
public:
    // Add a place
    void ajouterPlace(Place* place);
    
    // Get the list of places
    const vector<Place*>& getPlaces() const;

    // Search for a place (example: search by type)
    Place* rechercherPlace(const string& type) const;

    // Display all places
    void afficherPlaces() const;

private:
    vector<Place*> places; 
};

#endif 