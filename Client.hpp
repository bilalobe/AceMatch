
#include "Client.h"


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

