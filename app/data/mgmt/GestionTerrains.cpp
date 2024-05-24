#include "GestionTerrains.h"

void GestionTerrains::ajouterTerrain(Terrain terrain) {
    terrains.push_back(terrain);
}

// Display all terrains
void GestionTerrains::afficherTerrains() {
    for (const Terrain& terrain : terrains) {
        terrain.afficher();
        cout << endl;
    }
}

// Remove a terrain
bool GestionTerrains::supprimerTerrain(TypeTerrain type, int longueur, int largeur) {
    for (auto it = terrains.begin(); it != terrains.end(); ++it) {
        if (it->getType() == type && it->getLongueur() == longueur && it->getLargeur() == largeur) {
            terrains.erase(it);
            return true; // Terrain found and deleted
        }
    }
    return false; // Terrain not found
}

// Search for a terrain
Terrain* GestionTerrains::rechercherTerrain(TypeTerrain type, int longueur, int largeur) const {
    for (const auto& terrain : terrains) {
        if (terrain.getType() == type && terrain.getLongueur() == longueur && terrain.getLargeur() == largeur) {
            return const_cast<Terrain*>(&terrain);
        }
    }
    return nullptr;
}
