#include "clients.h"
#include <iostream>
#include <algorithm> 
#include <string>



Client::Client(string nom, int age, string adresse, string telephone) :
    nom(nom), age(age), adresse(adresse), telephone(telephone) {}

// Getters (should return the value)
string Client::getNom() const { return nom; }
int Client::getAge() const { return age; }
string Client::getAdresse() const { return adresse; }
string Client::getTelephone() const { return telephone; }

// Add a ticket to the client's list
void Client::addTicket(Ticket* ticket) { 
    tickets.push_back(ticket); 
}

int Client::setNom(string nom)
{
        this->nom = nom;
    return 0; // Success
}

// Setters (should return an integer indicating success or failure)
int Client::setAge(int age) {
    if (age > 0) { 
        this->age = age;
        return 0; // Success
    } else {
        return 1; // Error: Invalid age
    }
}

int Client::setAdresse(string adresse) {
    this->adresse = adresse;
    return 0; // Success
}

int Client::setTelephone(string telephone) {
    this->telephone = telephone;
    return 0; // Success
}
// Display a client's details
void Client::afficher()  const{
  cout << "Nom: " << nom << endl;
  cout << "Age: " << age << endl;
  cout << "Adresse: " << adresse << endl;
  cout << "Telephone: " << telephone << endl;
  cout << "Tickets:" << endl; 
  for (const Ticket* ticket : tickets) { // Iterate over pointers
    ticket->afficher(); // Dereference the pointer to access the Ticket object
  }
  cout << endl;
}


// GestionClients implementation
void GestionClients::ajouterClient(const Client& client) {
    clients.push_back(client);
}

bool GestionClients::supprimerClient(const std::string& nom) {
    auto it = std::find_if(clients.begin(), clients.end(),
                           [&nom](const Client& client) {
                               return client.getNom() == nom;
                           });
    if (it != clients.end()) {
        clients.erase(it);
    }
}

Client* GestionClients::rechercherClient(const std::string& nom) const {
    for (const Client& client : clients) {
        if (client.getNom().find(nom) != std::string::npos) {
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
                  return a.getNom() < b.getNom();
              });
}