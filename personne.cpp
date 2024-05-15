#include "personne.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // Include for sort()

using namespace std;

// Constructor for Personne
Personne::Personne(string nom, int age) : nom(nom), age(age) {}

// Display a person's details
void Personne::afficher() const {
  cout << "Nom: " << nom << endl;
  cout << "Age: " << age << endl;
}

// Constructor for Client
Client::Client(string nom, int age, string adresse, string telephone)
    : Personne(nom, age), adresse(adresse), telephone(telephone) {}

// Display a Client's details
void Client::afficher() const {
  Personne::afficher();
  cout << "Adresse: " << adresse << endl;
  cout << "Telephone: " << telephone << endl;
}

// GestionClients (Now a separate class outside Client)
class GestionClients {
public:
  void ajouterClient(const Client& client) { 
    clients.push_back(client); 
  }

  void supprimerClient(const string& nom) { 
    for (int i = 0; i < clients.size(); i++) {
      if (clients[i].nom == nom) {
        clients.erase(clients.begin() + i);
        break;
      }
    }
  }

  Client* rechercherClient(const string& nom) { 
    for (int i = 0; i < clients.size(); i++) {
      if (clients[i].nom == nom) {
        return &clients[i];
      }
    }
    return nullptr;
  }

  const vector<Client>& getClients() const {
    return clients;
  }

  void trierClientsParNom() { 
    sort(clients.begin(), clients.end(), [](const Client& a, const Client& b) {
      return a.nom < b.nom;
    });
  }

private:
  vector<Client> clients;
};

// GestionJoueurs (Now a separate class outside Joueur)
class GestionJoueurs {
public:
  void ajouterJoueur(const Joueur& joueur) {
    joueurs.push_back(joueur);
  }

  void supprimerJoueur(const string& nom) {
    for (int i = 0; i < joueurs.size(); i++) {
      if (joueurs[i].nom == nom) {
        joueurs.erase(joueurs.begin() + i);
        break;
      }
    }
  }

  Joueur* rechercherJoueur(const string& nom) {
    for (int i = 0; i < joueurs.size(); i++) {
      if (joueurs[i].nom == nom) {
        return &joueurs[i];
      }
    }
    return nullptr;
  }

  const vector<Joueur>& getJoueurs() const {
    return joueurs;
  }

  void trierJoueursParClassement() {
    sort(joueurs.begin(), joueurs.end(), [](const Joueur& a, const Joueur& b) {
      return a.classement < b.classement;
    });
  }

private:
  vector<Joueur> joueurs;
};

// Constructor for Joueur
Joueur::Joueur(string nom, int age, int classement)
    : Personne(nom, age), classement(classement) {}

// Display a Joueur's details
void Joueur::afficher() const {
  Personne::afficher();
  cout << "Classement: " << classement << endl;
}