#ifndef CLIENTS_H
#define CLIENTS_H

#include <string>
#include <vector>
#include <algorithm>

class Client {
public:
    Client(std::string nom, int numero) : nom(nom), numero(numero) {} // Member initialization list

    std::string getNom() const { return nom; }
    int getNumero() const { return numero; }

    void setNom(const std::string& nom) { this->nom = nom; }
    void setNumero(int numero) { this->numero = numero; }

private:
    std::string nom;
    int numero;
};

class GestionClients {
public:
    void ajouterClient(const Client& client) {
        clients.push_back(client);
    }

    void supprimerClient(const std::string& nom) {
        auto it = std::find_if(clients.begin(), clients.end(),
                               [&nom](const Client& client) {
                                   return client.getNom() == nom;
                               });
        if (it != clients.end()) {
            clients.erase(it);
        }
    }

    Client* rechercherClient(const std::string& nom) const {
    for (const Client& client : clients) {
        if (client.getNom().find(nom) != std::string::npos) {
            return const_cast<Client*>(&client); // Remove const to return a Client*
        }
    }
    return nullptr;
    }

    const std::vector<Client>& getClients() const { return clients; }

    void trierClientsParNom() {
        std::sort(clients.begin(), clients.end(),
                  [](const Client& a, const Client& b) {
                      return a.getNom() < b.getNom();
                  });
    }

private:
    std::vector<Client> clients;
};

#endif // CLIENTS_H