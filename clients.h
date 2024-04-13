#ifndef CLIENTS_H
#define CLIENTS_H

#include <string>
#include <vector>

using namespace std;

class Client {
public:
  Client(string nom, int numero);
  string getNom() const;
  int getNumero() const;
  void setNom(string nom);
  void setNumero(int numero);
private:
  string nom;
  int numero;
};

class GestionClients {
public:
  void ajouterClient(Client client);
  void supprimerClient(string nom);
  Client* rechercherClient(string nom);
  const vector<Client>& getClients() const;
  void trierClientsParNom();

private:
  vector<Client> clients;
};

#endif // CLIENTS_H