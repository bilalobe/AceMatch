#include "PaymentManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

PaymentManager::PaymentManager(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

PaymentManager::~PaymentManager()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool PaymentManager::addPaiement(const QSqlDatabase& db, int ticketId, double amount, const QString& paymentMode) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Paiements (ticketId, amount, paymentMode) VALUES (:ticketId, :amount, :paymentMode)");
    query.bindValue(":ticketId", ticketId);
    query.bindValue(":amount", amount);
    query.bindValue(":paymentMode", paymentMode);

    if (!query.exec()) {
        qDebug() << "Error adding payment:" << query.lastError();
        return false;
    }
    return true;
}

bool PaymentManager::removePaiement(const QSqlDatabase& db, int paymentId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Paiements WHERE id = :paiementId");
    query.bindValue(":paymentId", paiementId);

    if (!query.exec()) {
        qDebug() << "Error deleting payment:" << query.lastError();
        return false;
    }
    return true;
}

bool PaymentManager::updatePaiement(const QSqlDatabase& db, int paymentId, double newMontant, const QString& newModePaiement) {
    QSqlQuery query(db);
    query.prepare("UPDATE Paiements SET amount = :newMontant, paymentMode = :newModePaiement WHERE id = :paiementId");
    query.bindValue(":newMontant", newMontant);
    query.bindValue(":newModePaiement", newModePaiement);
    query.bindValue(":paymentId", paiementId);

    if (!query.exec()) {
        qDebug() << "Error updating payment:" << query.lastError();
        return false;
    }
    return true;
}

QList<Payment> PaymentManager::getPayments(const QSqlDatabase& db) const {
    QList<Payment> payments;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Paiements");

    while (query.next()) {
        int id = query.value("id").toInt();
        int ticketId = query.value("ticketId").toInt();
        double amount = query.value("amount").toDouble();
        QString paymentMode = query.value("paymentMode").toString();

        payments.append(Payment(id, ticketId, amount, paymentMode));
    }
    return paiements;
}

Payment PaymentManager::getPaiementById(const QSqlDatabase& db, int paiementId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Paiements WHERE id = :paiementId");
    query.bindValue(":paymentId", paiementId);

    if (query.exec() && query.next()) {
        return Payment(query.value("id").toInt(), query.value("ticketId").toInt(), query.value("amount").toDouble(), query.value("paymentMode").toString());
    } else {
        qDebug() << "Error getting payment by ID:" << query.lastError();
        return Payment();
    }
}