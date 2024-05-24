#ifndef GESTIONJOUEURS_H
#define GESTIONJOUEURS_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include "Joueur.h" // Make sure to include your Joueur header

class GestionJoueurs {
public:
    // Constructor (You can modify to take QSqlDatabase if needed)
    GestionJoueurs();

    // Database Interaction Methods:
    bool ajouterJoueur(QSqlDatabase& db, const Tournament::Joueur& joueur); 
    bool supprimerJoueur(QSqlDatabase& db, const QString& nom);
    bool modifierJoueur(QSqlDatabase& db, const QString& nom, int nouveauRang);
    Tournament::Joueur getJoueurByName(const QSqlDatabase& db, const QString& nom) const; 
    QList<Tournament::Joueur> getJoueurs(const QSqlDatabase& db) const;

    
};

#endif // GESTIONJOUEURS_H