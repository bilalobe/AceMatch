#ifndef MATCH_H
#define MATCH_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Joueur.h" 

class Match
{
public:
    Match(const Joueur& joueur1 = Joueur(), const Joueur& joueur2 = Joueur(), int score1 = 0, int score2 = 0, int id = -1)
        : id(id), joueur1(joueur1), joueur2(joueur2), score1(score1), score2(score2) {} // Inline constructor
    int getId() const { return id; }
    const Joueur& getJoueur1() const { return joueur1; }
    const Joueur& getJoueur2() const { return joueur2; }
    int getScore1() const { return score1; }
    int getScore2() const { return score2; }

private:
    int id;
    Joueur joueur1;
    Joueur joueur2;
    int score1;
    int score2;
};

#endif // MATCH_H