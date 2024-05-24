#include "Paiements.h"


Paiement::Paiement(const std::string &clientName, double amount, const std::string &date)
    : clientName(clientName), amount(amount), date(date) {}

std::string Paiement::getClientName() const {
    return clientName;
}

double Paiement::getAmount() const {
    return amount;
}

std::string Paiement::getDate() const {
    return date;
}

std::string Paiement::toString() const {
    return clientName + "," + std::to_string(amount) + "," + date;
}

Paiement Paiement::fromString(const std::string &data) {
    std::istringstream iss(data);
    std::string clientName, date, amountStr;
    std::getline(iss, clientName, ',');
    std::getline(iss, amountStr, ',');
    std::getline(iss, date, ',');
    return Paiement(clientName, std::stod(amountStr), date);
}

void Paiements::ajouterPaiement(const Paiement &paiement) {
    paiements.push_back(paiement);
}

void Paiements::afficherPaiements() const {
    for (const auto &paiement : paiements) {
        std::cout << "Client: " << paiement.getClientName()
                  << ", Amount: " << paiement.getAmount()
                  << ", Date: " << paiement.getDate() << std::endl;
    }
}

void Paiements::sauvegarderPaiements(const std::string &filename) const {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto &paiement : paiements) {
            outFile << paiement.toString() << std::endl;
        }
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

void Paiements::chargerPaiements(const std::string &filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            paiements.push_back(Paiement::fromString(line));
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
}
