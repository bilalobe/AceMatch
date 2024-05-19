#ifndef PARTIE_H
#define PARTIE_H

#include <string>
#include "Terrain.h"
#include "MatchResult.h"

using namespace std;

enum TypePartie {
    SIMPLE,
    DOUBLE
}

class Partie {
public:
    Partie(TypePartie type, std::string nomJoueur1, std::string nomJoueur2, Terrain* terrain = nullptr);
    void afficher() const;
    int getNumero() const { return numero; }
    string getNomJoueur1() const { return nomJoueur1; }
    string getNomJoueur2() const { return nomJoueur2; }
    TypePartie getType() const { return type; }
    void setNumero(int numero) { this->numero = numero; }
    void setResultat(const std::string& nomJoueur, int resultatAsInt);
    ResultatPartie getResultat1() const;
    ResultatPartie getResultat2() const;
    std::string getNomJoueur1() const;
    std::string getNomJoueur2() const;
    void setNomJoueur1(std::string nomJoueur1);
    void setNomJoueur2(std::string nomJoueur2);
    Terrain* getTerrain() const { return terrain; }

    // Declare the operator>> as a friend function of the Partie class
    friend std::istream& operator>>(std::istream& is, TypePartie& tp);

private:
    TypePartie type;
    std::string nomJoueur1;
    std::string nomJoueur2;
    ResultatPartie resultat1;
    ResultatPartie resultat2;
    int numero;
    static int nextMatchNumber;
    Terrain* terrain;
};

#endif