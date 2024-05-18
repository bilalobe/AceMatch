#include "clients.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor
Client::Client(const std::string &nom, int age, const std::string &adresse, const std::string &telephone)
    : nom(nom), age(age), adresse(adresse), telephone(telephone) {}

// Getters
string Client::getNom() const { return nom; }
int Client::getAge() const { return age; }
string Client::getAdresse() const { return adresse; }
string Client::getTelephone() const { return telephone; }

// Setters
int Client::setNom(const string &nom) {
    this->nom = nom;
    return 0; // Success
}

int Client::setAge(int age) {
    if (age > 0) {
        this->age = age;
        return 0; // Success
    } else {
        return 1; // Error: Invalid age
    }
}

int Client::setAdresse(const string &adresse) {
    this->adresse = adresse;
    return 0; // Success
}

int Client::setTelephone(const string &telephone) {
    this->telephone = telephone;
    return 0; // Success
}

// Add a ticket to the client's list
void Client::addTicket(Ticket *ticket) {
    tickets.push_back(ticket);
}

// Display client information
void Client::afficher() const {
    cout << "Nom: " << nom << endl;
    cout << "Age: " << age << endl;
    cout << "Adresse: " << adresse << endl;
    cout << "Telephone: " << telephone << endl;
    cout << "Tickets:" << endl;
    for (const Ticket *ticket : tickets) {
        ticket->afficher();
    }
    cout << endl;
}

// GestionClients methods

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
        cout << endl;
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
