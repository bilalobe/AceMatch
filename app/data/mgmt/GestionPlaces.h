#ifndef GESTION_PLACES.H
#define GESTION_PLACES.H

#include "Place.h"

#include <vector>
#include <string>

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