#ifndef TICKETS_H
#define TICKETS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ticket {
public:
  string type;
  double prix;
  string nomMatch; 
  int numeroTicket;

public:
  Ticket(string type, double prix, string nomMatch, int numeroTicket);

  void afficher() const;
};

class GestionTickets {
public:
  vector<Ticket> tickets;

  void ajouterTicket(Ticket ticket);
  void afficherTickets();
  void supprimerTicket(int numeroTicket);
};

#endif // TICKETS_H