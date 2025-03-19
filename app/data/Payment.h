#ifndef PAYMENT_H
#define PAYMENT_H

#include <QString>

class Payment
{
public:
    Payment(int id = -1, int ticketId = 0, double amount = 0.0, const QString& paymentMode = "")
        : id(id), ticketId(ticketId), amount(amount), paymentMode(paymentMode) {} // Inline constructor
    int getId() const { return id; }
    int getTicketId() const { return ticketId; }
    double getMontant() const { return amount; }
    QString getModePaiement() const { return paymentMode; }

private:
    int id;
    int ticketId;
    double amount;
    QString paymentMode;
};

#endif // PAYMENT_H