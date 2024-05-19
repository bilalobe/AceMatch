#ifndef GESTIONTICKETS_H
#define GESTIONTICKETS_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "ticket.h"
#include "GestionClients.h"


class GestionTickets {
public:

    // Generate a ticket
    Ticket genererTicket(const std::string& type, double prix, const std::string& matchName, Reservation* reservation);

    // Add a ticket
    void ajouterTicket(const Ticket& ticket);

    // Sell a ticket
    bool vendreTicket(GestionClients& gestionClients, int ticketNumber);

    // Display all tickets
    void afficherTickets() const;

    // Search for a ticket
    Ticket* rechercherTicket(int ticketNumber);

    // Remove a ticket
    void supprimerTicket(int ticketNumber);

private:
    std::vector<Ticket> tickets;
    std::map<int, Ticket*> ticketsMap;
};

#endif