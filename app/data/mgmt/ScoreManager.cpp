#include "ScoreManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ScoreManager::ScoreManager(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

ScoreManager::~ScoreManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool ScoreManager::addScore(const QSqlDatabase& db, int matchId, int score1, int score2) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Scores (matchId, score1, score2) VALUES (:matchId, :score1, :score2)");
    query.bindValue(":matchId", matchId);
    query.bindValue(":score1", score1);
    query.bindValue(":score2", score2);

    if (!query.exec()) {
        qDebug() << "Error adding score:" << query.lastError();
        return false;
    }
    return true;
}

bool ScoreManager::removeScore(const QSqlDatabase& db, int scoreId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Scores WHERE id = :scoreId");
    query.bindValue(":scoreId", scoreId);

    if (!query.exec()) {
        qDebug() << "Error deleting score:" << query.lastError();
        return false;
    }
    return true;
}

bool ScoreManager::updateScore(const QSqlDatabase& db, int scoreId, int newScore1, int newScore2) {
    QSqlQuery query(db);
    query.prepare("UPDATE Scores SET score1 = :newScore1, score2 = :newScore2 WHERE id = :scoreId");
    query.bindValue(":newScore1", newScore1);
    query.bindValue(":newScore2", newScore2);
    query.bindValue(":scoreId", scoreId);

    if (!query.exec()) {
        qDebug() << "Error updating score:" << query.lastError();
        return false;
    }
    return true;
}

QList<Score> ScoreManager::getScores(const QSqlDatabase& db) const {
    QList<Score> scores;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Scores"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        int matchId = query.value("matchId").toInt();
        int score1 = query.value("score1").toInt();
        int score2 = query.value("score2").toInt(); 

        scores.append(Score(id, matchId, score1, score2)); 
    }
    return scores;
}

Score ScoreManager::getScoreById(const QSqlDatabase& db, int scoreId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Scores WHERE id = :scoreId"); 
    query.bindValue(":scoreId", scoreId);

    if (query.exec() && query.next()) {
        return Score(query.value("id").toInt(), query.value("matchId").toInt(), query.value("score1").toInt(), query.value("score2").toInt());
    } else {
        qDebug() << "Error getting score by ID:" << query.lastError();
        return Score(); // Return a default-constructed Score (you might want to define a specific "not found" Score)
    }
}
