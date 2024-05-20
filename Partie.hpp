#include "Partie.h"

// Static member initialization for next match number
int Partie::nextMatchNumber = 1;

// Constructor for Partie
Partie::Partie(TypePartie type, const std::string& nomJoueur1, const std::string& nomJoueur2, Terrain* terrain)
    : type(type), nomJoueur1(nomJoueur1), nomJoueur2(nomJoueur2), resultat1(DRAW), resultat2(DRAW), terrain(terrain) {
    numero = nextMatchNumber++;
}

// Display a match's details
void Partie::afficher() const {
    std::cout << "Type: " << (type == SIMPLE ? "Simple" : "Double") << std::endl;
    std::cout << "Joueur 1: " << nomJoueur1 << std::endl;
    std::cout << "Joueur 2: " << nomJoueur2 << std::endl;
    std::cout << "Résultat 1: " << (resultat1 == PLAYER2_WON ? "Victoire" : (resultat1 == PLAYER2_WON ? "Défaite" : "Match Nul")) << std::endl;
    std::cout << "Résultat 2: " << (resultat2 == PLAYER1_WON ? "Victoire" : (resultat2 == PLAYER2_WON ? "Défaite" : "Match Nul")) << std::endl;
    if (terrain) {
        std::cout << "Terrain: " << terrain->getNom() << std::endl;
    } else {
        std::cout << "Terrain: Non spécifié" << std::endl;
    }
}

// Set the result of a match
void Partie::setResultat(const std::string& nomJoueur, int resultatAsInt) {
    if (resultatAsInt < 0 || resultatAsInt > 2) {
        throw std::invalid_argument("Invalid result value. Must be between 0 and 2.");
    }
    MatchResult actualResultat = static_cast<MatchResult>(resultatAsInt);

    if (nomJoueur == nomJoueur1) {
        resultat1 = actualResultat;
    } else if (nomJoueur == nomJoueur2) {
        resultat2 = actualResultat;
    } else {
        throw std::invalid_argument("Player name does not match any participants in the match.");
    }
}

// Overload the operator>> to read TypePartie
std::istream& operator>>(std::istream& is, TypePartie& tp) {
    int typeInt;
    is >> typeInt;
    tp = static_cast<TypePartie>(typeInt);
    return is;
}
