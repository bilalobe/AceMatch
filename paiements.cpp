#include "paiements.h"


using namespace std;

// Base Payment Class (Template)
template <typename T>
Paiement<T>::Paiement(MethodePaiement methode, double montant) : 
  methode(methode), montant(montant) {}

template <typename T>
void Paiement<T>::afficher() const {
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

// Specialized Payment Classes

// PaiementCarteBancaire
PaiementCarteBancaire::PaiementCarteBancaire(double montant, const string& numeroCarte) 
    : Paiement<string>(CARTE_BANCAIRE, montant), numeroCarte(numeroCarte) {}

void PaiementCarteBancaire::traiterPaiement(const string& numeroCarte) const {
  cout << "\nProcessing credit card payment...\n" << endl; 
  cout << "Numéro de carte: " << numeroCarte << endl; 

  //  Simulate sending the payment information to the payment gateway
  cout << "Sending payment information to the bank..." << endl; 
  // (This is where you would actually make an API request to a payment gateway) 
  // ... 

  // Simulate a popup 
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  system("cls"); 
  cout << "\t\t\t\t   *** Transaction effectuée! *** \t\t\t\t" << endl;
  cout << "\t\t\t\t      Montant: " << montant << " \t\t\t\t" << endl;
  cout << "\t\t\t\t  Appuyez sur une touche pour continuer...\t\t\t\t" << endl;

  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  _getch();
  system("cls");
} 

PaiementEspeces::PaiementEspeces(double montant) 
    : Paiement<NoDetails>(ESPECES, montant) {}

void PaiementEspeces::traiterPaiement(const NoDetails&) const {
  cout << "Traitement de paiement en espèces..." << endl; 
  // Simulate a popup
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  system("cls"); 
  cout << "\t\t\t\t   *** Transaction effectuée! *** \t\t\t\t" << endl;
  cout << "\t\t\t\t      Montant: " << montant << " \t\t\t\t" << endl;
  cout << "\t\t\t\t  Appuyez sur une touche pour continuer...\t\t\t\t" << endl;

  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  _getch();
  system("cls");
}

// PaiementCheque
PaiementCheque::PaiementCheque(double montant, const string& numeroCheque) 
    : Paiement<string>(CHEQUE, montant), numeroCheque(numeroCheque) {}

void PaiementCheque::traiterPaiement(const string& numeroCheque) const {
  cout << "Traitement de paiement par chèque..." << endl;
  cout << "Numéro de chèque: " << numeroCheque << endl; 

  // Simulate a popup 
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
  system("cls"); 
  cout << "\t\t\t\t   *** Transaction effectuée! *** \t\t\t\t" << endl;
  cout << "\t\t\t\t      Montant: " << montant << " \t\t\t\t" << endl;
  cout << "\t\t\t\t  Appuyez sur une touche pour continuer...\t\t\t\t" << endl;

  SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
  _getch();
  system("cls");
}