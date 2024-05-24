#ifndef GESTIONCLIENTS_H
#define GESTIONCLIENTS_H


#include "client.h"
#include <string>
#include <algorithm>
#include <vector>

class GestionClients
{
public:
    // Constructor
    GestionClients() {}

    // Add a client
    void ajouterClient(const Client &client);

    // Remove a client
    bool supprimerClient(const std::string &nom);

    // Search for a client
    Client *rechercherClient(const std::string &nom) const;

    // Display all clients
    void afficherClients() const;

    // Sort clients by name
    void trierClientsParNom();

    // Get the list of clients
    const std::vector<Client> &getClients() const;

private:
    std::vector<Client> clients;
};

#endif