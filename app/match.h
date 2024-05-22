#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QString>
#include "Player.h"
#include "MatchResult.h"

class Match : public QObject {
    Q_OBJECT
    Q_PROPERTY(int matchId READ getMatchId WRITE setMatchId NOTIFY matchIdChanged)
    Q_PROPERTY(Player* player1 READ getPlayer1 WRITE setPlayer1 NOTIFY player1Changed)
    Q_PROPERTY(Player* player2 READ getPlayer2 WRITE setPlayer2 NOTIFY player2Changed)
    Q_PROPERTY(MatchResult* result READ getResult WRITE setResult NOTIFY resultChanged)
    Q_PROPERTY(QString scheduledTime READ getScheduledTime WRITE setScheduledTime NOTIFY scheduledTimeChanged)

public:
    explicit Match(QObject *parent = nullptr);
    Match(int matchId, Player *player1, Player *player2, MatchResult *result, QString scheduledTime, QObject *parent = nullptr);

    int getMatchId() const;
    Player* getPlayer1() const;
    Player* getPlayer2() const;
    MatchResult* getResult() const;
    QString getScheduledTime() const;

public slots:
    void setMatchId(int matchId);
    void setPlayer1(Player *player1);
    void setPlayer2(Player *player2);
    void setResult(MatchResult *result);
    void setScheduledTime(QString scheduledTime);

signals:
    void matchIdChanged(int matchId);
    void player1Changed(Player *player1);
    void player2Changed(Player *player2);
    void resultChanged(MatchResult *result);
    void scheduledTimeChanged(QString scheduledTime);

private:
    int m_matchId;
    Player *m_player1;
    Player *m_player2;
    MatchResult *m_result;
    QString m_scheduledTime;
};

#endif // MATCH_H
