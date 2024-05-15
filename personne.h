#ifndef PERSONNE_H
#define PERSONNE_H
#include<iostream>
#include <string>
#include <vector>

using namespace std;

class Personne {
public:
  string nom;
  int age;

public:
  Personne(string nom, int age);

  void afficher() const;
};

class Client : public Personne {
public:
  string adresse;
  string telephone;

public:
  Client(string nom, int age, string adresse, string telephone);

  void afficher() const;
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
  Joueur(string nom, int age, int classement);

  void afficher() const;
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