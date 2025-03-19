// GestionJoueurs.h
#ifndef GESTIONJOUEURS_H
#define GESTIONJOUEURS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Joueur.h"

class GestionJoueurs : public QObject
{
    Q_OBJECT

public:
    GestionJoueurs(const QSqlDatabase& db);
    ~GestionJoueurs();

    bool ajouterJoueur(const QString& nom, int rang);
    bool supprimerJoueur(const QString& nom);
    bool modifierJoueur(const QString& nom, int nouveauRang);
    QList<Joueur> getJoueurs() const;
    Joueur getJoueurByName(const QString& name) const;
    QList<Joueur> searchJoueurs(const QString& searchTerm) const;
    Match getMatchById(int matchId) const;

signals:
    void joueurAdded(const QString& nom, int rang);
    void joueurDeleted(const QString& nom);
    void joueurUpdated(const QString& nom, int nouveauRang);
    void joueurFound(const QString& nom, int rang);

private:
    QSqlDatabase db;
};

#endif // GESTIONJOUEURS_H
