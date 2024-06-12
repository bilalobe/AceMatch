#include "Scoreboard.h"

Scoreboard::Scoreboard(QObject *parent)
    : QObject(parent) {}

QVector<MatchResult*> Scoreboard::getAllResults() const {
    return m_results;
}

void Scoreboard::addResult(MatchResult *result) {
    m_results.append(result);
    emit resultsChanged();
}

void Scoreboard::removeResult(int matchId) {
    for (int i = 0; i < m_results.size(); ++i) {
        if (m_results[i]->getMatchId() == matchId) {
            m_results.remove(i);
            emit resultsChanged();
            return;
        }
    }
}

MatchResult* Scoreboard::getResult(int matchId) const {
    for (const auto &result : m_results) {
        if (result->getMatchId() == matchId) {
            return result;
        }
    }
    return nullptr;
}
