#ifndef PAIEMENTS_H
#define PAIEMENTS_H

#include <iostream>
#include <string>
#include <conio.h> 

using namespace std;

// Base Payment Class (Template)
template <typename T>
class Paiement {
public:
  enum MethodePaiement {
    CARTE_BANCAIRE,
    ESPECES,
    CHEQUE
  };

  MethodePaiement methode;
  double montant;

  // Constructor (Template)
  Paiement(MethodePaiement methode, double montant);

  // Virtual Function for Processing (Template)
  virtual void traiterPaiement(const T& paymentDetails) const = 0; 

  void afficher() const; 
};

// Placeholder struct for PaiementEspeces
struct NoDetails {}; 

// Specialized Payment Classes (Inherited from Paiement)
class PaiementCarteBancaire : public Paiement<string> {
public:
  PaiementCarteBancaire(double montant, const string& numeroCarte);
  void traiterPaiement(const string& numeroCarte) const override; 
  // ... (Other methods)
private:
    string numeroCarte; // Member variable
};

class PaiementEspeces : public Paiement<NoDetails> { // Use NoDetails
public:
  PaiementEspeces(double montant);
  void traiterPaiement(const NoDetails&) const override; 
};

class PaiementCheque : public Paiement<string> {
public:
  PaiementCheque(double montant, const string& numeroCheque);
  void traiterPaiement(const string& numeroCheque) const override; 
private:
    string numeroCheque; // Member variable
};


#endif