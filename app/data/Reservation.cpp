#include "Reservation.h"

Reservation::Reservation(Client* client, Partie* partie, Terrain* terrain, int row, int col)
    : client(client), partie(partie), terrain(terrain), row(row), col(col) {}

// Getter methods
Client* Reservation::getClient() const {
    return client;
}

Partie* Reservation::getPartie() const {
    return partie;
}

Terrain* Reservation::getTerrain() const {
    return terrain;
}

int Reservation::getRow() const {
    return row;
}

int Reservation::getCol() const {
    return col;
}

// Display reservation details
void Reservation::afficher() const {
    cout << "Client: " << client->getNom() << endl;
    cout << "Match: " << partie->getNomJoueur1() << " vs. " << partie->getNomJoueur2() << endl;
    cout << "Terrain: " << terrain->getType() << endl;
    cout << "Row: " << row << endl;
    cout << "Column: " << col << endl;
}

