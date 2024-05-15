#ifndef PAIEMENTS_H
#define PAIEMENTS_H

#include <iostream>
#include <string>

using namespace std;

class Paiement {
public:
  enum MethodePaiement {
    CARTE_BANCAIRE,
    ESPECES,
    CHEQUE
  };

  MethodePaiement methode;
  double montant;

public:
  Paiement();
  Paiement(MethodePaiement methode, double montant);

  void afficher() const; 
};

#endif