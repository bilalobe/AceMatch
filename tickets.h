#ifndef TICKETS_H
#define TICKETS_H
using namespace std;
#include <iostream>
#include <vector>

// Classe Ticket

class Ticket {
  public:
    int numero;
    string place;
    float prix;

    Ticket(int numero, string place, float prix) {
      this->numero = numero;
      this->place = place;
      this->prix = prix;
    }

    void afficher() {
      cout << "Ticket numero: " << numero << endl;
      cout << "Place: " << place << endl;
      cout << "Prix: " << prix << endl;
    }
};

class GestionTickets {
  public:
    vector<Ticket> tickets;

    void ajouterTicket(Ticket ticket) {
      tickets.push_back(ticket);
    }

    void supprimerTicket(int numero) {
      for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i].numero == numero) {
          tickets.erase(tickets.begin() + i);
          break;
        }
      }
    }

    void afficherTickets() {
      for (Ticket ticket : tickets) {
        ticket.afficher();
      }
    }
};

#endif
