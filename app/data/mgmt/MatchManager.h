// MatchManager.h
#ifndef MATCHMANAGER_H
#define MATCHMANAGER_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Match.h"
#include "..\Score.h"

class MatchManager : public QObject
{
    Q_OBJECT

public:
    MatchManager(const QSqlDatabase& db);
    ~MatchManager();

    bool createMatch(const QString& player1Name, const QString& player2Name, int score1, int score2);
    bool removeMatch(int matchId);
    bool updateMatch(int matchId, int newScore1, int newScore2);
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

#endif // MATCHMANAGER_H
