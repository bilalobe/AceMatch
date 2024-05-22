#include "MatchSchedule.h"

MatchSchedule::MatchSchedule(QObject *parent)
    : QObject(parent) {}

QVector<Match*> MatchSchedule::getAllMatches() const {
    return m_matches;
}

void MatchSchedule::addMatch(Match *match) {
    m_matches.append(match);
    emit matchesChanged();
}

void MatchSchedule::removeMatch(int matchId) {
    for (int i = 0; i < m_matches.size(); ++i) {
        if (m_matches[i]->getMatchId() == matchId) {
            m_matches.remove(i);
            emit matchesChanged();
            return;
        }
    }
}

Match* MatchSchedule::getMatch(int matchId) const {
    for (const auto &match : m_matches) {
        if (match->getMatchId() == matchId) {
            return match;
        }
    }
    return nullptr;
}
