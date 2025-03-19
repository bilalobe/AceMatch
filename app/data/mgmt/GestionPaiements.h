#ifndef GESTIONPAIEMENTS_H
#define GESTIONPAIEMENTS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Paiement.h"

class GestionPaiements : public QObject
{
    Q_OBJECT

public:
    GestionPaiements(const QSqlDatabase& db);
    ~GestionPaiements();

    bool ajouterPaiement(int ticketId, double montant, const QString& modePaiement);
    bool supprimerPaiement(int paiementId); 
    bool modifierPaiement(int paiementId, double newMontant, const QString& newModePaiement);
    QList<Paiement> getPaiements() const;
    Paiement getPaiementById(int paiementId) const;
    QList<Paiement> searchPaiements(const QString& searchTerm) const;

signals:
    void paiementAdded(int id, int ticketId, double montant, const QString& modePaiement);
    void paiementDeleted(int id);
    void paiementUpdated(int id, double newMontant, const QString& newModePaiement);
    void paiementFound(int id, int ticketId, double montant, const QString& modePaiement);

private:
    QSqlDatabase db;
};

#endif // GESTIONPAIEMENTS_H
