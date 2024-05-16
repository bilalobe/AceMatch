#include "places.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Constructor for Place
Place::Place(string type, double prix) : type(type), prix(prix) {}

// Display a place's details
void Place::afficher() const {
  cout << "Type: " << type << endl;
  cout << "Prix: " << prix << endl;
}

// Get the type of a place
string Place::getType() const {
  return type;
}

// Get the price of a place
double Place::getPrix() const {
  return prix;
}

// Constructor for StandardPlace
StandardPlace::StandardPlace(int numero) : Place("Standard", 10.0), numero(numero) {}

// Display a StandardPlace's details
void StandardPlace::afficher() const {
  Place::afficher();
  cout << "Numéro: " << numero << endl;
}

// Get the number of a StandardPlace
int StandardPlace::getNumero() const {
  return numero;
}

// Constructor for VipPlace
VipPlace::VipPlace(int numero) : Place("VIP", 20.0), numero(numero) {}

// Display a VipPlace's details
void VipPlace::afficher() const {
  Place::afficher();
  cout << "Numéro: " << numero << endl;
}

// Get the number of a VipPlace
int VipPlace::getNumero() const {
  return numero;
}

// GestionPlaces implementation
class GestionPlaces {
public:
    // Add a place
    void ajouterPlace(Place* place) {
        places.push_back(place); 
    }
    
    // Get the list of places
    const vector<Place*>& getPlaces() const {
        return places;
    }

    // Search for a place (example: search by type)
    Place* rechercherPlace(const string& type) const {
        for (Place* place : places) {
            if (place->getType() == type) {
                return place;
            }
        }
        return nullptr; 
    }

    // Display all places
    void afficherPlaces() const {
        for (Place* place : places) {
            place->afficher();
            cout << endl;
        }
    }

private:
    vector<Place*> places; 
};