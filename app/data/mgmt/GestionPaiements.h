#ifndef GESTIONPAIEMENTS_H
#define GESTIONPAIEMENTS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include "..\Paiement.h"

class GestionPaiements
{
public:
    GestionPaiements(const QSqlDatabase& db);
    ~GestionPaiements();

    bool ajouterPaiement(const QSqlDatabase& db, int ticketId, double montant, const QString& modePaiement);
    bool supprimerPaiement(const QSqlDatabase& db, int paiementId); 
    bool modifierPaiement(const QSqlDatabase& db, int paiementId, double newMontant, const QString& newModePaiement);
    QList<Paiement> getPaiements(const QSqlDatabase& db) const; 
    Paiement getPaiementById(const QSqlDatabase& db, int paiementId) const; 
};

#endif // GESTIONPAIEMENTS_H
