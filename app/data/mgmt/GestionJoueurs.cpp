// GestionJoueurs.cpp
#include "GestionJoueurs.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionJoueurs::GestionJoueurs(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

GestionJoueurs::~GestionJoueurs()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionJoueurs::ajouterJoueur(const QSqlDatabase& db, const QString& nom, int rang)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO joueurs (nom, rang) VALUES (:nom, :rang)");
    query.bindValue(":nom", nom);
    query.bindValue(":rang", rang);

    if (!query.exec()) {
        qDebug() << "Error adding player: " << query.lastError();
        return false;
    }
    return true;
}

bool GestionJoueurs::supprimerJoueur(const QSqlDatabase& db, const QString& nom)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM joueurs WHERE nom = :nom");
    query.bindValue(":nom", nom);

    if (!query.exec()) {
        qDebug() << "Error removing player: " << query.lastError();
        return false;
    }
    return true;
}

bool GestionJoueurs::modifierJoueur(const QSqlDatabase& db, const QString& nom, int nouveauRang)
{
    QSqlQuery query(db);
    query.prepare("UPDATE joueurs SET rang = :rang WHERE nom = :nom");
    query.bindValue(":nom", nom);
    query.bindValue(":rang", nouveauRang);

    if (!query.exec()) {
        qDebug() << "Error updating player: " << query.lastError();
        return false;
    }
    return true;
}

QList<Joueur> GestionJoueurs::getJoueurs(const QSqlDatabase& db) const
{
    QList<Joueur> joueurs;
    QSqlQuery query(db);
    query.exec("SELECT * FROM joueurs");

    while (query.next()) {
        QString nom = query.value(0).toString();
        int rang = query.value(1).toInt();
        joueurs.append(Joueur(nom, rang));
    }

    return joueurs;
}

Joueur GestionJoueurs::getJoueurByName(const QSqlDatabase& db, const QString& name) const
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM joueurs WHERE nom = :name");
    query.bindValue(":name", name);

    if (query.exec() && query.next()) {
        return Joueur(query.value("nom").toString(), query.value("rang").toInt());
    } else {
        qDebug() << "Error getting player by name:" << query.lastError();
        return Joueur();
    }
}