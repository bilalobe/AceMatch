#ifndef CLIENTS_H
#define CLIENTS_H

#include <string>
#include <vector>
#include <algorithm>

class Client {
public:
    Client(std::string nom, int numero); // Member initialization list

    std::string getNom() const;
    int getNumero() const;

    void setNom(const std::string& nom);
    void setNumero(int numero);

private:
    std::string nom;
    int numero;
};

class GestionClients {
public:
    void ajouterClient(const Client& client);
    void supprimerClient(const std::string& nom);
    Client* rechercherClient(const std::string& nom) const;
    const std::vector<Client>& getClients() const;
    void trierClientsParNom();

private:
    std::vector<Client> clients;
};

#endif // CLIENTS_H