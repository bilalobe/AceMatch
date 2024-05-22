#include "MatchResult.h"

MatchResult::MatchResult(QObject *parent)
    : QObject(parent), m_matchId(0), m_winner(nullptr), m_loser(nullptr), m_score("") {}

MatchResult::MatchResult(int matchId, Player *winner, Player *loser, QString score, QObject *parent)
    : QObject(parent), m_matchId(matchId), m_winner(winner), m_loser(loser), m_score(score) {}

int MatchResult::getMatchId() const {
    return m_matchId;
}

Player* MatchResult::getWinner() const {
    return m_winner;
}

Player* MatchResult::getLoser() const {
    return m_loser;
}

QString MatchResult::getScore() const {
    return m_score;
}

void MatchResult::setMatchId(int matchId) {
    if (m_matchId != matchId) {
        m_matchId = matchId;
        emit matchIdChanged(m_matchId);
    }
}

void MatchResult::setWinner(Player *winner) {
    if (m_winner != winner) {
        m_winner = winner;
        emit winnerChanged(m_winner);
    }
}

void MatchResult::setLoser(Player *loser) {
    if (m_loser != loser) {
        m_loser = loser;
        emit loserChanged(m_loser);
    }
}

void MatchResult::setScore(QString score) {
    if (m_score != score) {
        m_score = score;
        emit scoreChanged(m_score);
    }
}
