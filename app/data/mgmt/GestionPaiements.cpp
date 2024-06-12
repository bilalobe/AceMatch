#include "GestionPaiements.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

GestionPaiements::GestionPaiements(const QSqlDatabase& db)
    // : db(db)  // No need for this initialization
{
    // You can add database initialization logic here if needed, but it's usually done in the MainWindow constructor
}

GestionPaiements::~GestionPaiements()
{
    // No need to close the database connection, as it's managed in MainWindow
}

bool GestionPaiements::ajouterPaiement(const QSqlDatabase& db, int ticketId, double montant, const QString& modePaiement) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Paiements (ticketId, montant, modePaiement) VALUES (:ticketId, :montant, :modePaiement)");
    query.bindValue(":ticketId", ticketId);
    query.bindValue(":montant", montant);
    query.bindValue(":modePaiement", modePaiement);

    if (!query.exec()) {
        qDebug() << "Error adding payment:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionPaiements::supprimerPaiement(const QSqlDatabase& db, int paiementId) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM Paiements WHERE id = :paiementId");
    query.bindValue(":paiementId", paiementId);

    if (!query.exec()) {
        qDebug() << "Error deleting payment:" << query.lastError();
        return false;
    }
    return true;
}

bool GestionPaiements::modifierPaiement(const QSqlDatabase& db, int paiementId, double newMontant, const QString& newModePaiement) {
    QSqlQuery query(db);
    query.prepare("UPDATE Paiements SET montant = :newMontant, modePaiement = :newModePaiement WHERE id = :paiementId");
    query.bindValue(":newMontant", newMontant);
    query.bindValue(":newModePaiement", newModePaiement);
    query.bindValue(":paiementId", paiementId);

    if (!query.exec()) {
        qDebug() << "Error updating payment:" << query.lastError();
        return false;
    }
    return true;
}

QList<Paiement> GestionPaiements::getPaiements(const QSqlDatabase& db) const {
    QList<Paiement> paiements;
    QSqlQuery query(db);
    query.exec("SELECT * FROM Paiements");

    while (query.next()) {
        int id = query.value("id").toInt();
        int ticketId = query.value("ticketId").toInt();
        double montant = query.value("montant").toDouble();
        QString modePaiement = query.value("modePaiement").toString();

        paiements.append(Paiement(id, ticketId, montant, modePaiement));
    }
    return paiements;
}

Paiement GestionPaiements::getPaiementById(const QSqlDatabase& db, int paiementId) const {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Paiements WHERE id = :paiementId");
    query.bindValue(":paiementId", paiementId);

    if (query.exec() && query.next()) {
        return Paiement(query.value("id").toInt(), query.value("ticketId").toInt(), query.value("montant").toDouble(), query.value("modePaiement").toString());
    } else {
        qDebug() << "Error getting payment by ID:" << query.lastError();
        return Paiement();
    }
}