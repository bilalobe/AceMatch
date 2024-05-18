#ifndef TICKETS_H
#define TICKETS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ticket {
  string type;
  double prix;
  string nomMatch; 
  int numeroTicket;

public:
  Ticket(string type, double prix, string nomMatch, int numeroTicket);
  string getType() const { return type; }
  double getPrix() const { return prix; }
  string getNomMatch() const { return nomMatch; }
  int getNumeroTicket() const { return numeroTicket; }
  bool isSold() const { return sold; }
  void setSold(bool sold) { this->sold = sold; }
  void afficher() const;
private:
  bool sold;
};

class GestionTickets {
public:
  vector<Ticket> tickets;

  void ajouterTicket(Ticket ticket);
  void afficherTickets();
  void supprimerTicket(int numeroTicket);
  Ticket* rechercherTicket(int numeroTicket) const;
  Ticket genererTicket(string type, double prix, string nomMatch);
  bool vendreTicket(GestionClients& gestionClients, int numeroTicket);
};

#endif // TICKETS_H