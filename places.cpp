#include "places.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor for Place
Place::Place(string type, double prix) : type(type), prix(prix) {}

// Display a place's details
void Place::afficher() const {
  cout << "Type: " << type << endl;
  cout << "Prix: " << prix << endl;
}

// Get the type of a place
string Place::getType() const {
  return type;
}

// Get the price of a place
double Place::getPrix() const {
  return prix;
}

// Constructor for StandardPlace
StandardPlace::StandardPlace(int numero) : Place("Standard", 10.0), numero(numero) {}

// Display a StandardPlace's details
void StandardPlace::afficher() const {
  Place::afficher();
  cout << "Numéro: " << numero << endl;
}

// Get the number of a StandardPlace
int StandardPlace::getNumero() const {
  return numero;
}

// Constructor for VipPlace
VipPlace::VipPlace(int numero) : Place("VIP", 20.0), numero(numero) {}

// Display a VipPlace's details
void VipPlace::afficher() const {
  Place::afficher();
  cout << "Numéro: " << numero << endl;
}

// Get the number of a VipPlace
int VipPlace::getNumero() const {
  return numero;
}