// PlayerManager.h
#ifndef GESTIONJOUEURS_H
#define GESTIONJOUEURS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Player.h"

class PlayerManager : public QObject
{
    Q_OBJECT

public:
    PlayerManager(const QSqlDatabase& db);
    ~PlayerManager();

    bool addJoueur(const QString& name, int rang);
    bool removeJoueur(const QString& name);
    bool updateJoueur(const QString& name, int nouveauRang);
    QList<Player> getPlayers() const;
    Player getJoueurByName(const QString& name) const;
    QList<Player> searchJoueurs(const QString& searchTerm) const;
    Match getMatchById(int matchId) const;

signals:
    void joueurAdded(const QString& name, int rang);
    void joueurDeleted(const QString& name);
    void joueurUpdated(const QString& name, int nouveauRang);
    void joueurFound(const QString& name, int rang);

private:
    QSqlDatabase db;
};

#endif // GESTIONJOUEURS_H
