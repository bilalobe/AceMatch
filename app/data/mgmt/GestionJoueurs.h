// GestionJoueurs.h
#ifndef GESTIONJOUEURS_H
#define GESTIONJOUEURS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "Joueur.h" 

class GestionJoueurs
{
public:
    GestionJoueurs(const QSqlDatabase& db);
    ~GestionJoueurs();

    bool ajouterJoueur(const QSqlDatabase& db, const QString& nom, int rang);
    bool supprimerJoueur(const QSqlDatabase& db, const QString& nom);
    bool modifierJoueur(const QSqlDatabase& db, const QString& nom, int nouveauRang);
    QList<Joueur> getJoueurs(const QSqlDatabase& db) const; 
    Joueur getJoueurByName(const QSqlDatabase& db, const QString& name) const; 
};

#endif // GESTIONJOUEURS_H