#ifndef COURTMANAGER_H
#define COURTMANAGER_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Court.h"

class CourtManager : public QObject
{
    Q_OBJECT

public:
    CourtManager(const QSqlDatabase& db);
    ~CourtManager();

    bool addCourt(const QString& name, const QString& type);
    bool removeCourt(int CourtId); 
    bool updateCourt(int CourtId, const QString& newName, const QString& newType);
    QList<Court> getCourts() const;
    Court getCourtById(int CourtId) const;
    QList<Court> searchCourts(const QString& searchTerm) const;

signals:
    void CourtAdded(int id, const QString& name, const QString& type);
    void CourtUpdated(int id, const QString& name, const QString& type);
    void CourtDeleted(int id);
    void CourtFound(int id, const QString& name, const QString& type);

private:
    QSqlDatabase db;
};

#endif // COURTMANAGER_H
