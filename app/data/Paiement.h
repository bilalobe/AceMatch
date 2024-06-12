#ifndef PAIEMENT_H
#define PAIEMENT_H

#include <QString>

class Paiement
{
public:
    Paiement(int id = -1, int ticketId = 0, double montant = 0.0, const QString& modePaiement = "")
        : id(id), ticketId(ticketId), montant(montant), modePaiement(modePaiement) {} // Inline constructor
    int getId() const { return id; }
    int getTicketId() const { return ticketId; }
    double getMontant() const { return montant; }
    QString getModePaiement() const { return modePaiement; }

private:
    int id;
    int ticketId;
    double montant;
    QString modePaiement;
};

#endif // PAIEMENT_H