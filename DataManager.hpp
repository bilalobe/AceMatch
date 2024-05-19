#include "DataManager.h"

static void saveReservations(const std::vector<Reservation> &reservations, const std::string &filename)
{
    std::ofstream outFile(filename, std::ios::out | std::ios::binary);
    if (outFile.is_open())
    {
        for (const auto &res : reservations)
        {
            outFile.write((char *)&res, sizeof(res));
        }
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

static std::vector<Reservation> loadReservations(const std::string &filename)
{
    std::vector<Reservation> reservations;
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (inFile.is_open())
    {
        Reservation res;
        while (inFile.read((char *)&res, sizeof(res)))
        {
            reservations.push_back(res);
        }
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
    return reservations;
}
static void saveJoueurs(const std::vector<Joueur> &joueurs, const std::string &filename)
{
    std::ofstream outFile(filename, std::ios::out | std::ios::binary);
    if (outFile.is_open())
    {
        for (const auto &joueur : joueurs)
        {
            outFile.write((char *)&joueur, sizeof(joueur));
        }
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

static std::vector<Joueur> loadJoueurs(const std::string &filename)
{
    std::vector<Joueur> joueurs;
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (inFile.is_open())
    {
        Joueur joueur;
        while (inFile.read((char *)&joueur, sizeof(joueur)))
        {
            joueurs.push_back(joueur);
        }
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
    return joueurs;
}

static void saveParties(const std::vector<Partie> &parties, const std::string &filename)
{
    std::ofstream outFile(filename, std::ios::out | std::ios::binary);
    if (outFile.is_open())
    {
        for (const auto &partie : parties)
        {
            outFile.write((char *)&partie, sizeof(partie));
        }
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

static std::vector<Partie> loadParties(const std::string &filename)
{
    std::vector<Partie> parties;
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (inFile.is_open())
    {
        Partie partie;
        while (inFile.read((char *)&partie, sizeof(partie)))
        {
            parties.push_back(partie);
        }
        inFile.close();
    }
    std::cerr << "Unable to open file for writing: " << filename << std::endl;
}
