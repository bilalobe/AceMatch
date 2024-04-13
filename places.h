#ifndef PLACES_H
#define PLACES_H

#include <iostream>
#include <string>

using namespace std;

// Définition de la classe Place
class Place {
public:
  string type;
  double prix;

public:
  Place(string type, double prix) : type(type), prix(prix) {}

  void afficher() const {
    cout << "Type: " << type << endl;
    cout << "Prix: " << prix << endl;
  }

  string getType() const { return type; }
  double getPrix() const { return prix; }
};

// Définition de la classe StandardPlace
class StandardPlace : public Place {
public:
  StandardPlace(int numero) : Place("Standard", 10.0), numero(numero) {}

  void afficher() const {
    Place::afficher();
    cout << "Numéro: " << numero << endl;
  }

  int getNumero() const { return numero; }

private:
  int numero;
};

// Définition de la classe VipPlace
class VipPlace : public Place {
public:
  VipPlace(int numero) : Place("VIP", 20.0), numero(numero) {}

  void afficher() const {
    Place::afficher();
    cout << "Numéro: " << numero << endl;
  }

  int getNumero() const { return numero; }

private:
  int numero;
};

#endif
