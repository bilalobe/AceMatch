#include "clients.h"
#include <iostream>
#include <algorithm> 
#include <string>

using namespace std;

// Client Constructors
Client::Client(string nom, int age) : nom(nom), age(age) {}

Client::Client(string nom, int age, string adresse, string telephone) 
    : nom(nom), age(age), adresse(adresse), telephone(telephone) {}

// Display a client's details
void Client::afficher() const {
  cout << "Nom: " << nom << endl;
  cout << "Age: " << age << endl;
  cout << "Adresse: " << adresse << endl;
  cout << "Telephone: " << telephone << endl;
  cout << "Tickets:" << endl; 
  for (const Ticket& ticket : tickets) {
    ticket.afficher(); 
  }
  cout << endl;
}

// GestionClients implementation
void GestionClients::ajouterClient(const Client& client) {
    clients.push_back(client);
}

void GestionClients::supprimerClient(const std::string& nom) {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&nom](const Client& client) {
                               return client.nom == nom;
                           });
    if (it != clients.end()) {
        clients.erase(it);
    }
}

Client* GestionClients::rechercherClient(const std::string& nom) const {
    for (const Client& client : clients) {
        if (client.nom.find(nom) != std::string::npos) {
            return const_cast<Client*>(&client); 
        }
    }
    return nullptr;
}

const std::vector<Client>& GestionClients::getClients() const {
    return clients;
}

void GestionClients::trierClientsParNom() {
    std::sort(clients.begin(), clients.end(),
              [](const Client& a, const Client& b) {
                  return a.nom < b.nom;
              });
}