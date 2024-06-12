#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Reservation.h"
#include "Joueur.h"
#include "Partie.h"
#include "Score.h"
#include "Paiements.h"

class DataManager
{
public:
        // Constructor
    DataManager();

    // Destructor
    ~DataManager();

    // Methods for saving and loading data
    void sauvegarderReservations(const std::string &filename, const std::vector<Reservation> &reservations) const;
    void chargerReservations(const std::string &filename, std::vector<Reservation> &reservations);

    void sauvegarderJoueurs(const std::string &filename, const std::vector<Joueur> &joueurs) const;
    void chargerJoueurs(const std::string &filename, std::vector<Joueur> &joueurs);

    void sauvegarderParties(const std::string &filename, const std::vector<Partie> &parties) const;
    void chargerParties(const std::string &filename, std::vector<Partie> &parties);

    void sauvegarderScores(const std::string &filename, const std::vector<Score> &scores) const;
    void chargerScores(const std::string &filename, std::vector<Score> &scores);

    

private:
    // Helper function to save data to a file
    template <typename T>
    void sauvegarderDonnees(const std::string &filename, const std::vector<T> &data) const;

    // Helper function to load data from a file
    template <typename T>
    void chargerDonnees(const std::string &filename, std::vector<T> &data);
};

#endif // DATAMANAGER_H
