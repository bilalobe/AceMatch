// GestionMatch.h
#ifndef GESTIONMATCH_H
#define GESTIONMATCH_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Match.h"

class GestionMatch
{
public:
    GestionMatch(const QSqlDatabase& db);
    ~GestionMatch();

    bool creerMatch(const QSqlDatabase& db, const QString& player1Name, const QString& player2Name, int score1, int score2);
    bool supprimerMatch(const QSqlDatabase& db, int matchId);
    bool modifierMatch(const QSqlDatabase& db, int matchId, int newScore1, int newScore2);
    QList<Match> getMatches(const QSqlDatabase& db) const;
    Match getMatchById(const QSqlDatabase& db, int matchId) const;

    // Add method to get the score for a match
    Score getMatchScore(const QSqlDatabase& db, int matchId) const;
};

#endif // GESTIONMATCH_H