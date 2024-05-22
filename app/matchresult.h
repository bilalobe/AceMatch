#ifndef MATCHRESULT_H
#define MATCHRESULT_H

#include <QObject>
#include <QString>
#include "Player.h"

class MatchResult : public QObject {
    Q_OBJECT
    Q_PROPERTY(int matchId READ getMatchId WRITE setMatchId NOTIFY matchIdChanged)
    Q_PROPERTY(Player* winner READ getWinner WRITE setWinner NOTIFY winnerChanged)
    Q_PROPERTY(Player* loser READ getLoser WRITE setLoser NOTIFY loserChanged)
    Q_PROPERTY(QString score READ getScore WRITE setScore NOTIFY scoreChanged)

public:
    explicit MatchResult(QObject *parent = nullptr);
    MatchResult(int matchId, Player *winner, Player *loser, QString score, QObject *parent = nullptr);

    int getMatchId() const;
    Player* getWinner() const;
    Player* getLoser() const;
    QString getScore() const;

public slots:
    void setMatchId(int matchId);
    void setWinner(Player *winner);
    void setLoser(Player *loser);
    void setScore(QString score);

signals:
    void matchIdChanged(int matchId);
    void winnerChanged(Player *winner);
    void loserChanged(Player *loser);
    void scoreChanged(QString score);

private:
    int m_matchId;
    Player *m_winner;
    Player *m_loser;
    QString m_score;
};

#endif // MATCHRESULT_H
