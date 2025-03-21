#include "MatchManager.h"
#include "PlayerManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


MatchManager::MatchManager(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

MatchManager::~MatchManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool MatchManager::createMatch(const QSqlDatabase& db, const QString& player1Name, const QString& player2Name, int score1, int score2) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Matches (player1, player2, score1, score2) "
                  "VALUES (:player1, :player2, :score1, :score2)");
    query.bindValue(":player1", player1Name);
    query.bindValue(":player2", player2Name);
    query.bindValue(":score1", score1);
    query.bindValue(":score2", score2);

    if (!query.exec()) {
        qDebug() << "Error creating match:" << query.lastError();
        return false;
    }
    return true;
}

bool MatchManager::removeMatch(const QSqlDatabase& db, int matchId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Matches WHERE id = :matchId");
    query.bindValue(":matchId", matchId);

    if (!query.exec()) {
        qDebug() << "Error deleting match:" << query.lastError();
        return false; 
    }
    return true; 
}

QList<Match> MatchManager::getMatches(const QSqlDatabase& db) const {
    QList<Match> matches;
    QSqlQuery query(db);
    query.exec("SELECT * FROM matches");

    while (query.next()) {
        matches.append(Match(
            getJoueurByName(db, query.value("player1").toString()), 
            getJoueurByName(db, query.value("player2").toString()),
            query.value("score1").toInt(),
            query.value("score2").toInt()
        ));
    }
    return matches;
}

Match MatchManager::getMatchById(const QSqlDatabase& db, int matchId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Matches WHERE id = :matchId"); 
    query.bindValue(":matchId", matchId);

    if (query.exec() && query.next()) {
        // Assuming you have a way to construct a Match object from query results
        return Match(
            getJoueurByName(db, query.value("player1").toString()),
            getJoueurByName(db, query.value("player2").toString()),
            query.value("score1").toInt(),
            query.value("score2").toInt()
        );
    } else {
        qDebug() << "Error getting match by ID:" << query.lastError();
        return Match(); // Return a default-constructed Match (you might want to define a specific "not found" Match)
    }
}
 

Score MatchManager::getMatchScore(const QSqlDatabase& db, int matchId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Scores WHERE matchId = :matchId");
    query.bindValue(":matchId", matchId);

    if (query.exec() && query.next()) {
        return Score(query.value("id").toInt(), matchId, query.value("score1").toInt(), query.value("score2").toInt());
    } else {
        qDebug() << "Error getting score for match:" << query.lastError();
        return Score(); // Return a default-constructed Score (you might want to define a specific "not found" Score)
    }
}

// MatchManager.cpp
bool MatchManager::updateMatch(const QSqlDatabase& db, int matchId, int newScore1, int newScore2) {
    QSqlQuery query(db);
    query.prepare("UPDATE Matches SET score1 = :score1, score2 = :score2 WHERE id = :matchId");
    query.bindValue(":score1", newScore1);
    query.bindValue(":score2", newScore2);
    query.bindValue(":matchId", matchId);

    if (!query.exec()) {
        qDebug() << "Error updating match:" << query.lastError();
        return false;
    }

    // Also update the Scores table (assuming you have a Scores table)
    QSqlQuery updateScoreQuery(db);
    updateScoreQuery.prepare("UPDATE Scores SET score1 = :newScore1, score2 = :newScore2 WHERE matchId = :matchId");
    updateScoreQuery.bindValue(":newScore1", newScore1);
    updateScoreQuery.bindValue(":newScore2", newScore2);
    updateScoreQuery.bindValue(":matchId", matchId);

    if (!updateScoreQuery.exec()) {
        qDebug() << "Error updating score:" << updateScoreQuery.lastError();
        return false;
    }

    return true;
}
