#ifndef PERSONNE_H
#define PERSONNE_H
#include<iostream>
#include <string>

using namespace std;

class Personne {
public:
  string nom;
  int age;

public:
  Personne(string nom, int age) : nom(nom), age(age) {}

  void afficher() const {
    cout << "Nom: " << nom << endl;
    cout << "Age: " << age << endl;
  }
};

class Client : public Personne {
public:
  string adresse;
  string telephone;

public:
  Client(string nom, int age, string adresse, string telephone)
      : Personne(nom, age), adresse(adresse), telephone(telephone) {}

  void afficher() const {
    Personne::afficher();
    cout << "Adresse: " << adresse << endl;
    cout << "Telephone: " << telephone << endl;
  }
  class GestionClients {
  void ajouterClient(Client client);
  void supprimerClient(string nom);
  Client* rechercherClient(string nom);
  const vector<Client>& getClients() const;
  void trierClientsParNom();

private:
  vector<Client> clients;
};
};

class Joueur : public Personne {
public:
  int classement;

public:
  Joueur(string nom, int age, int classement)
      : Personne(nom, age), classement(classement) {}

  void afficher() const {
    Personne::afficher();
    cout << "Classement: " << classement << endl;
  }
  class GestionJoueurs {
  void ajouterJoueur(Joueur joueur);
  void supprimerJoueur(string nom);
  Joueur* rechercherJoueur(string nom);
  const vector<Joueur>& getJoueurs() const;
  void trierJoueursParClassement();

private:
  vector<Joueur> joueurs;
};  
};

#endif