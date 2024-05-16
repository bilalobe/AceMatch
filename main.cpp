#include <iostream>
#include <vector>
#include <limits>
#include "joueurs.h"
#include "terrains.h"
#include "parties.h"
#include "reservations.h"
#include "championnats.h"
#include "tickets.h"
#include "scores.h"
#include "clients.h" // You'll need to add this for GestionClients

using namespace std;

// ... (Other global objects)

// --- Tennis Championship Application ---

class TennisChampionship {
public:
    GestionJoueurs gestionJoueurs;
    GestionTerrains gestionTerrains;
    GestionReservations gestionReservations;
    GestionScores gestionScores;
    GestionParties gestionParties;
    ChampionnatSimple championnat;
    PlanificationParties planificateur;
    GestionClients gestionClients; // Add GestionClients to TennisChampionship

    // Constructor
    TennisChampionship() {
        // Initialize the championship (load data from a file if needed)
        championnat = ChampionnatSimple("Grand Slam", 2023, 4); 
    }
    
    // Menu functions (members of the TennisChampionship class)
    void displayMainMenu();
    void displayJoueursMenu();
    void displayTerrainsMenu();
    void displayPartiesMenu();
    void displayChampionnatsMenu();
    void displayReservationsMenu();
    void displayScoreManagementMenu();
    void displayClientsMenu(); // Add displayClientsMenu
    void displayTicketsMenu(); 

private:
    int getUserChoice(); // Helper function for menu selection

    // ... (Other helper functions you may need)
};


// --- Menu Display Functions ---
void TennisChampionship::displayMainMenu() {
  cout << "Tennis Championship Application" << endl;
  cout << "------------------------------" << endl;
  cout << "1. Gestion des Joueurs" << endl;
  cout << "2. Gestion des Terrains" << endl;
  cout << "3. Gestion des Parties" << endl;
  cout << "4. Gestion des Championnats" << endl;
  cout << "5. Gestion des Réservations" << endl;
  cout << "6. Gestion des Scores" << endl;
  cout << "7. Gestion des Clients" << endl;
  cout << "8. Gestion des Tickets" << endl;
  cout << "9. Quitter" << endl;
  cout << "------------------------------" << endl;
  cout << "Enter your choice: ";
}

// --- Menu Selection Validation ---
int TennisChampionship::getUserChoice() {
    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 9) {
        cout << "Invalid input. Please enter a number between 1 and 9: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining input
    }
    return choice;
}

// --- Menu Functions for Each Section ---

void TennisChampionship::displayJoueursMenu() {
  // ... (Implementation of displayJoueursMenu) ...
}

void TennisChampionship::displayTerrainsMenu() {
  // ... (Implementation of displayTerrainsMenu) ...
}

void TennisChampionship::displayPartiesMenu() {
  // ... (Implementation of displayPartiesMenu) ...
}

void TennisChampionship::displayChampionnatsMenu() {
  // ... (Implementation of displayChampionnatsMenu) ...
}

void TennisChampionship::displayReservationsMenu() {
  // ... (Implementation of displayReservationsMenu) ...
}

void TennisChampionship::displayScoreManagementMenu() {
  // ... (Implementation of displayScoreManagementMenu) ...
}

void TennisChampionship::displayClientsMenu() {
  cout << "Client Management Menu" << endl;
  cout << "---------------------" << endl;
  cout << "1. Add a client" << endl;
  cout << "2. Remove a client" << endl;
  cout << "3. Update a client's information" << endl;
  cout << "4. Search for a client" << endl;
  cout << "5. Display all clients" << endl;
  cout << "6. Exit" << endl;
  cout << "Enter your choice: ";
  int choice = getUserChoice();

  switch (choice) {
    case 1: { // Add a client
      string nom;
      int age;
      string adresse;
      string telephone;

      cout << "Enter client name: ";
      cin >> nom;

      cout << "Enter client age: ";
      cin >> age;

      cout << "Enter client address: ";
      cin >> adresse;

      cout << "Enter client phone number: ";
      cin >> telephone;

      Client client(nom, age, adresse, telephone);
      this->gestionClients.ajouterClient(client);
      cout << "Client added successfully." << endl;
      break;
    }
    case 2: { // Remove a client
      string nom;
      cout << "Enter client name: ";
      cin >> nom;
      if (!this->gestionClients.supprimerClient(nom)) {
        cout << "Client not found." << endl;
      } else {
        cout << "Client removed successfully." << endl;
      }
      break;
    }
    case 3: { // Update a client's information
      string nom;
      cout << "Enter client name: ";
      cin >> nom;
      Client* clientToUpdate = this->gestionClients.rechercherClient(nom);
      if (clientToUpdate != nullptr) {
        cout << "Enter new client name: ";
        cin >> clientToUpdate->nom;

        cout << "Enter new client age: ";
        cin >> clientToUpdate->age;

        cout << "Enter new client address: ";
        cin >> clientToUpdate->adresse;

        cout << "Enter new client phone number: ";
        cin >> clientToUpdate->telephone;

        cout << "Client updated successfully." << endl;
      } else {
        cout << "Client not found." << endl;
      }
      break;
    }
    case 4: { // Search for a client
      string nom;
      cout << "Enter client name: ";
      cin >> nom;
      Client* client = this->gestionClients.rechercherClient(nom);
      if (client != nullptr) {
        client->afficher();
      } else {
        cout << "Client not found." << endl;
      }
      break;
    }
    case 5: { // Display all clients
      this->gestionClients.trierClientsParNom(); 
      for (const Client& client : this->gestionClients.getClients()) {
        client.afficher();
      }
      break;
    }
    case 6:
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
  }
}

void TennisChampionship::displayTicketsMenu() {
    cout << "Ticket Management Menu" << endl;
    cout << "---------------------" << endl;
    cout << "1. Generate a ticket" << endl;
    cout << "2. Sell a ticket" << endl;
    cout << "3. Display all tickets" << endl;
    cout << "4. Search for a ticket" << endl;
    cout << "5. Remove a ticket" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    int choice = getUserChoice();
    
    switch (choice) {
      case 1: { // Generate a ticket
        cout << "Enter ticket type (Standard or VIP): ";
        string type;
        cin >> type;

        cout << "Enter ticket price: ";
        double prix;
        cin >> prix;

        cout << "Enter match name (Player 1 vs. Player 2): ";
        string matchName;
        cin >> matchName;

        Ticket ticket = this->gestionTickets.genererTicket(type, prix, matchName); 
        this->gestionTickets.ajouterTicket(ticket);
        cout << "Ticket generated successfully!" << endl;
        break;
      }
      case 2: { // Sell a ticket
        cout << "Enter ticket number: ";
        int ticketNumber;
        cin >> ticketNumber;

        bool success = this->gestionTickets.vendreTicket(this->gestionClients, ticketNumber); 
        if (success) {
          cout << "Ticket sold successfully." << endl;
        }
        break;
      }
      case 3: { // Display all tickets
        this->gestionTickets.afficherTickets();
        break;
      }
      case 4: { // Search for a ticket
        cout << "Enter ticket number: ";
        int ticketNumber;
        cin >> ticketNumber;

        Ticket* ticket = this->gestionTickets.rechercherTicket(ticketNumber);
        if (ticket != nullptr) {
          ticket->afficher();
        } else {
          cout << "Ticket not found." << endl;
        }
        break;
      }
      case 5: { // Remove a ticket
        cout << "Enter ticket number: ";
        int ticketNumber;
        cin >> ticketNumber;

        this->gestionTickets.supprimerTicket(ticketNumber);
        cout << "Ticket removed successfully." << endl;
        break;
      }
      case 6:
        break; // Exit the Tickets menu
      default:
        cout << "Invalid choice. Please try again." << endl;
    }
}

// ... (Implementations of other functions) ...

// Helper function to choose a place


int main() {
  // ... (You'll likely want to initialize your data here, perhaps by loading it from a file)
  TennisChampionship tennisChampionship; // Create an instance

  int selection;
  do {
    tennisChampionship.displayMainMenu();
    selection = tennisChampionship.getUserChoice();

    switch (selection) {
      case 1:
        tennisChampionship.displayJoueursMenu();
        break;
      case 2:
        tennisChampionship.displayTerrainsMenu();
        break;
      case 3:
        tennisChampionship.displayPartiesMenu();
        break;
      case 4:
        tennisChampionship.displayChampionnatsMenu();
        break;
      case 5:
        tennisChampionship.displayReservationsMenu();
        break;
      case 6:
        tennisChampionship.displayScoreManagementMenu();
        break;
      case 7:
        tennisChampionship.displayClientsMenu();
        break;
      case 8:
        tennisChampionship.displayTicketsMenu();
        break;
      case 9:
        cout << "Au revoir!" << endl;
        break;
      default:
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 9);

  return 0;
}