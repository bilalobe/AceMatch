#include "GestionPlaces.h"

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