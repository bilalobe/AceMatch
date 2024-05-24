#ifndef GESTION_PARTIES.H
#define GESTION_PARTIES.H

#include "Partie.h"
#include <vector>
#include <map>

class GestionParties {
public:
    GestionParties();
    std::vector<Partie> getParties();
    std::vector<Partie> getPreviousRoundMatches();
    bool isPartieFromPreviousRound(Partie partie);
    int getPreviousRoundMaxMatchNumber() const;
    void setPreviousRoundMaxMatchNumber(int newMax);
    void setParties(std::vector<Partie> parties);
    void ajouterPartie(Partie partie);
    void afficherParties();
    void supprimerPartie(TypePartie type, std::string nomJoueur1, std::string nomJoueur2);
    Partie* rechercherPartie(const std::string& nomJoueur1, const std::string& nomJoueur2);
    void setMatchResult(int numero, const std::string& winnerName);

private:
    std::vector<Partie> parties;
    std::map<std::pair<std::string, std::string>, Partie*> partiesMap;
    int previousRoundMaxMatchNumber;
};

#endif