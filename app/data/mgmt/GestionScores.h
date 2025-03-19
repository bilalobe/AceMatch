#ifndef GESTIONSCORE_H
#define GESTIONSCORE_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Score.h"

class GestionScore : public QObject
{
    Q_OBJECT

public:
    GestionScore(const QSqlDatabase& db);
    ~GestionScore();

    bool ajouterScore(int matchId, int score1, int score2);
    bool supprimerScore(int scoreId); 
    bool modifierScore(int scoreId, int newScore1, int newScore2);
    QList<Score> getScores() const;
    Score getScoreById(int scoreId) const;
    QList<Score> searchScores(const QString& searchTerm) const;

signals:
    void scoreAdded(int id, int matchId, int score1, int score2);
    void scoreDeleted(int id);
    void scoreUpdated(int id, int newScore1, int newScore2);
    void scoreFound(int id, int matchId, int score1, int score2);

private:
    QSqlDatabase db;
};

#endif // GESTIONSCORE_H
