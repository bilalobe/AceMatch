#ifndef TOURNAMENTRANKING_H
#define TOURNAMENTRANKING_H

#include <vector>
#include <string>
#include <map>

class TournamentRanking {
public:
    void ajouterMatch(const std::string &joueur1, const std::string &joueur2, int score1, int score2);
    void afficherClassement() const;

private:
    std::map<std::string, int> classement;
    void mettreAJourClassement(const std::string &joueur, int points);
};

#endif // TOURNAMENTRANKING_H
