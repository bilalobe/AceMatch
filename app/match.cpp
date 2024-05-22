#include "Match.h"

Match::Match(QObject *parent)
    : QObject(parent), m_matchId(0), m_player1(nullptr), m_player2(nullptr), m_result(nullptr), m_scheduledTime("") {}

Match::Match(int matchId, Player *player1, Player *player2, MatchResult *result, QString scheduledTime, QObject *parent)
    : QObject(parent), m_matchId(matchId), m_player1(player1), m_player2(player2), m_result(result), m_scheduledTime(scheduledTime) {}

int Match::getMatchId() const {
    return m_matchId;
}

Player* Match::getPlayer1() const {
    return m_player1;
}

Player* Match::getPlayer2() const {
    return m_player2;
}

MatchResult* Match::getResult() const {
    return m_result;
}

QString Match::getScheduledTime() const {
    return m_scheduledTime;
}

void Match::setMatchId(int matchId) {
    if (m_matchId != matchId) {
        m_matchId = matchId;
        emit matchIdChanged(m_matchId);
    }
}

void Match::setPlayer1(Player *player1) {
    if (m_player1 != player1) {
        m_player1 = player1;
        emit player1Changed(m_player1);
    }
}

void Match::setPlayer2(Player *player2) {
    if (m_player2 != player2) {
        m_player2 = player2;
        emit player2Changed(m_player2);
    }
}

void Match::setResult(MatchResult *result) {
    if (m_result != result) {
        m_result = result;
        emit resultChanged(m_result);
    }
}

void Match::setScheduledTime(QString scheduledTime) {
    if (m_scheduledTime != scheduledTime) {
        m_scheduledTime = scheduledTime;
        emit scheduledTimeChanged(m_scheduledTime);
    }
}
