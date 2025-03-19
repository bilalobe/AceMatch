#include "CourtManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

CourtManager::CourtManager(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

CourtManager::~CourtManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool CourtManager::addCourt(const QSqlDatabase& db, const QString& name, const QString& type) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Courts (name, type) VALUES (:name, :type)");
    query.bindValue(":name", name);
    query.bindValue(":type", type);

    if (!query.exec()) {
        qDebug() << "Error adding court:" << query.lastError();
        return false;
    }
    return true;
}

bool CourtManager::removeCourt(const QSqlDatabase& db, int CourtId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Courts WHERE id = :courtId");
    query.bindValue(":courtId", CourtId);

    if (!query.exec()) {
        qDebug() << "Error deleting court:" << query.lastError();
        return false;
    }
    return true;
}

bool CourtManager::updateCourt(const QSqlDatabase& db, int CourtId, const QString& newName, const QString& newType) {
    QSqlQuery query(db);
    query.prepare("UPDATE Courts SET name = :newName, type = :newType WHERE id = :courtId");
    query.bindValue(":newName", newName);
    query.bindValue(":newType", newType);
    query.bindValue(":courtId", CourtId);

    if (!query.exec()) {
        qDebug() << "Error updating court:" << query.lastError();
        return false;
    }
    return true;
}

QList<Court> CourtManager::getCourts(const QSqlDatabase& db) const {
    QList<Court> Courts;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Courts"); 

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString type = query.value("type").toString(); 

        Courts.append(Court(id, name, type)); 
    }
    return Courts;
}