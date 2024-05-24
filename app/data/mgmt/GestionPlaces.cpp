#include "GestionPlaces.h"
#include <iostream>
#include <vector>
#include <string>

// Add a place
void GestionPlaces::ajouterPlace(Place *place)
{
    places.push_back(place);
}

// Get the list of places
const vector<Place *> &getPlaces() const
{
    return places;
}

// Search for a place (example: search by type)
GestionPlaces *rechercherPlace(const string &type) const
{
    for (Place *place : places)
    {
        if (place->getType() == type)
        {
            return place;
        }
    }
    return nullptr;
}

// Display all places
void afficherPlaces() const
{
    for (Place *place : places)
    {
        place->afficher();
        cout << endl;
    }
}
