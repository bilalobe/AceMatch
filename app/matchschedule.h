#ifndef MATCHSCHEDULE_H
#define MATCHSCHEDULE_H

#include <QObject>
#include <QVector>
#include "Match.h"

class MatchSchedule : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector<Match*> matches READ getAllMatches NOTIFY matchesChanged)

public:
    explicit MatchSchedule(QObject *parent = nullptr);

    QVector<Match*> getAllMatches() const;

public slots:
    void addMatch(Match *match);
    void removeMatch(int matchId);
    Match*
}
