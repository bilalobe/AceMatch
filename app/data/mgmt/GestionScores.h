#ifndef GESTIONSCORE_H
#define GESTIONSCORE_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Score.h" 

class GestionScore
{
public:
    GestionScore(const QSqlDatabase& db);
    ~GestionScore();

    bool ajouterScore(const QSqlDatabase& db, int matchId, int score1, int score2);
    bool supprimerScore(const QSqlDatabase& db, int scoreId); 
    bool modifierScore(const QSqlDatabase& db, int scoreId, int newScore1, int newScore2);
    QList<Score> getScores(const QSqlDatabase& db) const; 
    Score getScoreById(const QSqlDatabase& db, int scoreId) const; 
};

#endif // GESTIONSCORE_H