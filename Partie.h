#ifndef PARTIE_H
#define PARTIE_H

#include <iostream>
#include <string>

#include "Match.h"
#include "Terrain.h"
#include "MatchResult.h"

enum TypePartie {
    SIMPLE,
    DOUBLE
};

class Partie {
public:
    Partie(TypePartie type, const std::string& nomJoueur1, const std::string& nomJoueur2, Terrain* terrain = nullptr);

    void afficher() const;
    int getNumero() const { return numero; }
    std::string getNomJoueur1() const { return nomJoueur1; }
    std::string getNomJoueur2() const { return nomJoueur2; }
    TypePartie getType() const { return type; }
    Terrain* getTerrain() const { return terrain; }

    void setNumero(int numero) { this->numero = numero; }
    void setNomJoueur1(const std::string& nomJoueur1) { this->nomJoueur1 = nomJoueur1; }
    void setNomJoueur2(const std::string& nomJoueur2) { this->nomJoueur2 = nomJoueur2; }
    void setResultat(const std::string& nomJoueur, int resultatAsInt);

    MatchResult getResultat1() const { return resultat1; }
    MatchResult getResultat2() const { return resultat2; }

    friend std::istream& operator>>(std::istream& is, TypePartie& tp);

private:
    TypePartie type;
    std::string nomJoueur1;
    std::string nomJoueur2;
    MatchResult resultat1;
    MatchResult resultat2;
    int numero;
    static int nextMatchNumber;
    Terrain* terrain;
};

#endif // PARTIE_H
