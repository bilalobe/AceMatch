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
  Place(string type, double prix);
  void afficher() const;
  string getType() const;
  double getPrix() const;
};

// Définition de la classe StandardPlace
class StandardPlace : public Place {
public:
  StandardPlace(int numero);

  void afficher() const;
  int getNumero() const;

private:
  int numero;
};

// Définition de la classe VipPlace
class VipPlace : public Place {
public:
  VipPlace(int numero);

  void afficher() const;
  int getNumero() const;

private:
  int numero;
};

#endif 