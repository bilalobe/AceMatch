#ifndef GESTIONPAIEMENTS_H
#define GESTIONPAIEMENTS_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QObject>
#include "..\Payment.h"

class PaymentManager : public QObject
{
    Q_OBJECT

public:
    PaymentManager(const QSqlDatabase& db);
    ~PaymentManager();

    bool addPaiement(int ticketId, double amount, const QString& paymentMode);
    bool removePaiement(int paiementId); 
    bool updatePaiement(int paiementId, double newMontant, const QString& newModePaiement);
    QList<Payment> getPayments() const;
    Payment getPaiementById(int paiementId) const;
    QList<Payment> searchPaiements(const QString& searchTerm) const;

signals:
    void paiementAdded(int id, int ticketId, double amount, const QString& paymentMode);
    void paiementDeleted(int id);
    void paiementUpdated(int id, double newMontant, const QString& newModePaiement);
    void paiementFound(int id, int ticketId, double amount, const QString& paymentMode);

private:
    QSqlDatabase db;
};

#endif // GESTIONPAIEMENTS_H
