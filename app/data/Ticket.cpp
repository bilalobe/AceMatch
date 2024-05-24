#include "Ticket.h"

// Static member initialization for next ticket number
int Ticket::nextTicketNumber = 1;

// Constructor for Ticket
Ticket::Ticket(const std::string& type, double prix, const std::string& matchName, Reservation* reservation, int row, int col)
    : type(type), prix(prix), matchName(matchName), numeroTicket(nextTicketNumber++), sold(false), reservation(reservation), row(row), col(col) {} 

// Display ticket information
void Ticket::afficher() const {
    cout << "Ticket Number: " << numeroTicket << endl;
    cout << "Type: " << type << endl;
    cout << "Price: " << prix << endl;
    cout << "Match: " << matchName << endl;
    cout << "Sold: " << (sold ? "Yes" : "No") << endl;
    cout << "Reservation: " << (reservation ? "Yes" : "No") << endl; 
    cout << "Row: " << row << endl;
    cout << "Column: " << col << endl;
}

