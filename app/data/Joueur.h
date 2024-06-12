#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>

class Joueur
{
public:
    Joueur(const QString& nom = "", int rang = 0) : nom(nom), rang(rang) {} // Inline constructor
    QString getNom() const { return nom; }
    int getRang() const { return rang; }

private:
    QString nom;
    int rang;
};

#endif // JOUEUR_H