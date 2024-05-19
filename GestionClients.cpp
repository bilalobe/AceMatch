#include "Client.h"
#include "GestionClients.h"

// Add a client
void GestionClients::ajouterClient(const Client &client) {
    clients.push_back(client);
}

// Remove a client
bool GestionClients::supprimerClient(const std::string &nom) {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&nom](const Client &client) {
                               return client.getNom() == nom;
                           });
    if (it != clients.end()) {
        clients.erase(it);
        return true; // Success
    }
    return false; // Client not found
}

// Search for a client
Client *GestionClients::rechercherClient(const std::string &nom) const {
    for (const Client &client : clients) {
        if (client.getNom().find(nom) != std::string::npos) {
            return const_cast<Client *>(&client);
        }
    }
    return nullptr;
}

// Display all clients
void GestionClients::afficherClients() const {
    for (const Client &client : clients) {
        client.afficher();
    }
}

// Sort clients by name
void GestionClients::trierClientsParNom() {
    std::sort(clients.begin(), clients.end(),
              [](const Client &a, const Client &b) {
                  return a.getNom() < b.getNom();
              });
}

// Get the list of clients
const std::vector<Client> &GestionClients::getClients() const {
    return clients;
}
