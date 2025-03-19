// GestionMatch.h
#ifndef GESTIONMATCH_H
#define GESTIONMATCH_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Match.h"
#include "..\Score.h"

class GestionMatch : public QObject
{
    Q_OBJECT

public:
    GestionMatch(const QSqlDatabase& db);
    ~GestionMatch();

    bool creerMatch(const QString& player1Name, const QString& player2Name, int score1, int score2);
    bool supprimerMatch(int matchId);
    bool modifierMatch(int matchId, int newScore1, int newScore2);
    QList<Match> getMatches() const;
    Match getMatchById(int matchId) const;
    Score getMatchScore(int matchId) const;
    QList<Match> searchMatches(const QString& searchTerm) const;

signals:
    void matchCreated(int id, const QString& player1Name, const QString& player2Name, int score1, int score2);
    void matchDeleted(int id);
    void matchUpdated(int id, int newScore1, int newScore2);
    void matchFound(int id, const QString& player1Name, const QString& player2Name, int score1, int score2);

private:
    QSqlDatabase db;
};

#endif // GESTIONMATCH_H
