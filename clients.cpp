#include "clients.h"
#include <iostream>
#include <algorithm> 
#include <string>

using namespace std;

// Add a client to the management list
void GestionClients::ajouterClient(const Client& client) {
    clients.push_back(client);
}

// Remove a client from the management list by name
void GestionClients::supprimerClient(const std::string& nom) {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&nom](const Client& client) {
                               return client.getNom() == nom;
                           });
    if (it != clients.end()) {
        clients.erase(it);
    }
}

// Search for a client by name (partial match)
Client* GestionClients::rechercherClient(const std::string& nom) const {
    for (const Client& client : clients) {
        if (client.getNom().find(nom) != std::string::npos) {
            return const_cast<Client*>(&client); // Remove const to return a Client*
        }
    }
    return nullptr;
}

// Get the list of all clients
const std::vector<Client>& GestionClients::getClients() const {
    return clients;
}

// Sort clients alphabetically by name
void GestionClients::trierClientsParNom() {
    std::sort(clients.begin(), clients.end(),
              [](const Client& a, const Client& b) {
                  return a.getNom() < b.getNom();
              });
}