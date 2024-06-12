#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <map>
#include <fstream>
#include <iostream>

class Scoreboard {
public:
    void afficherScores() const;
    void ajouterScore(const std::string& joueur1, const std::string& joueur2, int score1, int score2);
    void sauvegarderScores(const std::string& filename) const;
    void chargerScores(const std::string& filename);

private:
    std::map<std::string, std::map<std::string, int>> scores;
};

#endif // SCOREBOARD_H
