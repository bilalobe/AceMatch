#ifndef PAIEMENTS_H
#define PAIEMENTS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class Paiement {
public:
    Paiement(const std::string &clientName, double amount, const std::string &date);
    
    std::string getClientName() const;
    double getAmount() const;
    std::string getDate() const;

    std::string toString() const;
    static Paiement fromString(const std::string &data);

private:
    std::string clientName;
    double amount;
    std::string date;
};

class Paiements {
public:
    void ajouterPaiement(const Paiement &paiement);
    void afficherPaiements() const;
    void sauvegarderPaiements(const std::string &filename) const;
    void chargerPaiements(const std::string &filename);

private:
    std::vector<Paiement> paiements;
};

#endif // PAIEMENTS_H
