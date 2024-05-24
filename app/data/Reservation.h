#ifndef RESERVATION_H
#define RESERVATION_H

#include "Client.h"
#include "Partie.h"


class Reservation {
public:
    Reservation(Client* client, Partie* partie, Terrain* terrain, int row, int col);

    // Getters
    Client* getClient() const;
    Partie* getPartie() const;
    Terrain* getTerrain() const;
    int getRow() const;
    int getCol() const;

    // Display reservation details
    void afficher() const;

private:
    Client* client;
    Partie* partie;
    Terrain* terrain;
    int row;
    int col;
};

#endif