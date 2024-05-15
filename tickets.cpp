#include "tickets.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Ticket::Ticket(string type, double prix, string nomMatch, int numeroTicket)
    : type(type), prix(prix), nomMatch(nomMatch), numeroTicket(numeroTicket) {}

void Ticket::afficher() const {
  cout << "Type: " << type << endl;
  cout << "Prix: " << prix << endl;
  cout << "Nom du Match: " << nomMatch << endl;
  cout << "Numéro de ticket: " << numeroTicket << endl;
}

class GestionTickets {
public:
  vector<Ticket> tickets;

  void ajouterTicket(Ticket ticket) {
    tickets.push_back(ticket);
  }

  void afficherTickets() {
    for (Ticket ticket : tickets) {
      ticket.afficher();
      cout << endl;
    }
  }

  void supprimerTicket(int numeroTicket) {
    for (int i = 0; i < tickets.size(); i++) {
      if (tickets[i].numeroTicket == numeroTicket) {
        tickets.erase(tickets.begin() + i);
        break;
      }
    }
  }
};