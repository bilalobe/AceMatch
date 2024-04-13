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
  Paiement(MethodePaiement methode, double montant) {
    this->methode = methode;
    this->montant = montant;
  }

  void afficher() const {
    cout << "Méthode de paiement: ";
    switch (methode) {
      case CARTE_BANCAIRE:
        cout << "Carte bancaire";
        break;
      case ESPECES:
        cout << "Espèces";
        break;
      case CHEQUE:
        cout << "Chèque";
        break;
    }
    cout << endl;
    cout << "Montant: " << montant << endl;
  }
};

#endif