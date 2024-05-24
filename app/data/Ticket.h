#ifndef TICKET_H
#define TICKET_H

#include <string>
#include "Reservation.h"
    
class Ticket {
public:
    Ticket(const std::string& type, double prix, const std::string& matchName, Reservation* reservation, int row, int col); // Constructor

    // Getters
    std::string getType() const { return type; }
    double getPrix() const { return prix; }
    std::string getMatchName() const { return matchName; }
    int getNumeroTicket() const { return numeroTicket; } // Getter for ticket number
    bool isSold() const { return sold; } // Getter to check if the ticket is sold
    Reservation* getReservation() const { return reservation; } // Getter for the reservation
    int getRow() const { return row; }
    int getCol() const { return col; }

    // Setters
    void setSold(bool sold) { this->sold = sold; } // Setter to mark the ticket as sold

    // Display ticket information
    void afficher() const;

private:
    std::string type;
    double prix;
    std::string matchName;
    int numeroTicket; // Ticket number
    bool sold; // Flag to indicate if the ticket is sold
    Reservation* reservation; 
    int row;
    int col; 
    static int nextTicketNumber;
};

#endif