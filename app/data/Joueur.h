#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString> 

namespace Tournament { // Example namespace

class Joueur {
private:
    QString nom;
    int rang;
    int victoires;
    int defaites;

public:
    // Constructor
    Joueur(const QString& nom = , int rang = 0);

    // Getters
    QString getNom() const;
    int getRang() const;
    int getVictoires() const;
    int getDefaites() const;

    // Setters
    void setNom(const QString& nom);
    void setRang(int rang);
    void setVictoires(int victoires);
    void setDefaites(int defaites);
};

} // namespace Tournament

#endif // JOUEUR_H