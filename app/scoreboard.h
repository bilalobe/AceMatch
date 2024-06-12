#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QObject>
#include <QVector>
#include "MatchResult.h"

class Scoreboard : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector<MatchResult*> results READ getAllResults NOTIFY resultsChanged)

public:
    explicit Scoreboard(QObject *parent = nullptr);

    QVector<MatchResult*> getAllResults() const;

public slots:
    void addResult(MatchResult *result);
    void removeResult(int matchId);
    MatchResult* getResult(int matchId) const;

signals:
    void resultsChanged();

private:
    QVector<MatchResult*> m_results;
};

#endif // SCOREBOARD_H
