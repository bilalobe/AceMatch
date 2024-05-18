#ifndef CLIENTS_H
#define CLIENTS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "tickets.h"


class Client {
private:
    string nom;
    int age;
    string adresse;
    string telephone;
    vector<Ticket*> tickets; 

public:
    Client(string nom, int age, string adresse, string telephone);
    string getNom() const;
    int getAge() const;
    string getAdresse() const;
    string getTelephone() const;
    void addTicket(Ticket* ticket);
    int setNom(string nom);
    int setAge(int age);
    int setAdresse(string adresse);
    int setTelephone(string telephone);
    void afficher() const;
};

class GestionClients {
public:
  void ajouterClient(const Client& client);
  bool supprimerClient(const string& nom);
  Client* rechercherClient(const string& nom) const;
  const vector<Client>& getClients() const;
  void trierClientsParNom();

private:
  vector<Client> clients;
};

#endif // CLIENTS_H