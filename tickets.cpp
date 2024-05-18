#include "tickets.h"
#include "clients.h"
#include <iostream>
#include <string>
#include <vector>
#include <random> // Include for random number generation

using namespace std;

Ticket::Ticket(string type, double prix, string nomMatch, int numeroTicket)
    : type(type), prix(prix), nomMatch(nomMatch), numeroTicket(numeroTicket) {}

bool Ticket::isSold() const
{
  return sold;
}
void Ticket::setSold(bool sold)
{
  this->sold = sold;
}

void Ticket::afficher() const
{
  cout << "Type: " << type << endl;
  cout << "Prix: " << prix << endl;
  cout << "Nom du Match: " << nomMatch << endl;
  cout << "Numéro de ticket: " << numeroTicket << endl;
  cout << "Vendu: " << (sold ? "Oui" : "Non") << endl;
}

class GestionTickets
{
public:
  vector<Ticket> tickets;
  int nextTicketNumber = 1; // Track ticket numbers

  // Add a ticket
  void ajouterTicket(Ticket ticket)
  {
    tickets.push_back(ticket);
  }

  // Display all tickets
  void afficherTickets()
  {
    for (Ticket ticket : tickets)
    {
      ticket.afficher();
      cout << endl;
    }
  }

  // Remove a ticket
  void supprimerTicket(int numeroTicket)
  {
    for (int i = 0; i < tickets.size(); i++)
    {
      if (tickets[i].getNumeroTicket() == numeroTicket)
      {
        tickets.erase(tickets.begin() + i);
        break;
      }
    }
  }

  // Search for a ticket
  Ticket *rechercherTicket(int numeroTicket) const
  {
    for (int i = 0; i < tickets.size(); i++)
    {
      if (tickets[i].getNumeroTicket() == numeroTicket)
      {
        return const_cast<Ticket *>(&tickets[i]);
      }
    }
    return nullptr;
  }

  // Generate a new ticket
  Ticket genererTicket(string type, double prix, string nomMatch)
  {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100000, 999999);
    int uniqueTicketNumber = dis(gen);

    return Ticket(type, prix, nomMatch, uniqueTicketNumber);
  }

  // Sell a ticket to a client (using GestionClients)

  bool vendreTicket(GestionClients &gestionClients, int numeroTicket)
  {
    Ticket *ticket = rechercherTicket(numeroTicket);

    if (ticket != nullptr && !ticket->isSold())
    {
      cout << "Enter client name to sell the ticket to: ";
      string clientName;
      cin >> clientName;

      Client *client = gestionClients.rechercherClient(clientName);

      if (client != nullptr)
      {
        // Assign the ticket to the client
        client->addTicket(ticket);
        // Mark the ticket as sold
        ticket->setSold(true);
        return true;
      }
      else
      {
        cout << "Client not found." << endl;
        return false;
      }
    }
    else
    {
      cout << "Ticket not found or already sold." << endl;
      return false;
    }
  }
};
