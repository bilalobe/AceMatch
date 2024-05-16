#ifndef CLIENTS_H
#define CLIENTS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "tickets.h"

using namespace std;

class Client {
public:
  string nom;
  int age;
  string adresse;
  string telephone;
  vector<Ticket> tickets; 

public:
  Client(string nom, int age);            // Constructor for a client with basic details
  Client(string nom, int age, string adresse, string telephone); // Constructor for a client with full details
  void afficher() const;
};

class GestionClients {
public:
  void ajouterClient(const Client& client);
  void supprimerClient(const string& nom);
  Client* rechercherClient(const string& nom) const;
  const vector<Client>& getClients() const;
  void trierClientsParNom();

private:
  vector<Client> clients;
};

#endif // CLIENTS_H