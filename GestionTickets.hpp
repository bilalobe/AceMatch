#include "Ticket.h"


// Generate a ticket
Ticket GestionTickets::genererTicket(const std::string& type, double prix, const std::string& matchName, Reservation* reservation) {
    // Get row and col from reservation
    int row = reservation->getRow();
    int col = reservation->getCol();

    Ticket ticket(type, prix, matchName, reservation, row, col); 
    tickets.push_back(ticket);
    ticketsMap[ticket.getNumeroTicket()] = &tickets.back();
    return ticket;
}

// Add a ticket
void GestionTickets::ajouterTicket(const Ticket& ticket) {
    tickets.push_back(ticket);
    ticketsMap[ticket.getNumeroTicket()] = &tickets.back();
}

// Sell a ticket
bool GestionTickets::vendreTicket(GestionClients& gestionClients, int ticketNumber) {
    Ticket* ticket = rechercherTicket(ticketNumber);

    if (ticket != nullptr && !ticket->isSold()) {
        cout << "Enter client name to sell the ticket to: ";
        string clientName;
        cin >> clientName;

        Client* client = gestionClients.rechercherClient(clientName);

        if (client != nullptr) {
            // Assign the ticket to the client
            client->addTicket(ticket);
            // Mark the ticket as sold
            ticket->setSold(true);
            return true;
        } else {
            cout << "Client not found." << endl;
            return false;
        }
    } else {
        cout << "Ticket not found or already sold." << endl;
        return false;
    }
}

// Display all tickets
void GestionTickets::afficherTickets() const {
    for (const Ticket& ticket : tickets) {
        ticket.afficher();
        cout << endl;
    }
}

// Search for a ticket
Ticket* GestionTickets::rechercherTicket(int ticketNumber) {
    auto it = ticketsMap.find(ticketNumber);
    if (it != ticketsMap.end()) {
        return it->second;
    }
    return nullptr;
}

// Remove a ticket
void GestionTickets::supprimerTicket(int ticketNumber) {
    auto it = ticketsMap.find(ticketNumber);
    if (it != ticketsMap.end()) {
        tickets.erase(std::remove(tickets.begin(), tickets.end(), *(it->second)), tickets.end());
        delete it->second; // Assuming you need to delete the dynamically allocated Ticket object
        ticketsMap.erase(it);
    }
}

