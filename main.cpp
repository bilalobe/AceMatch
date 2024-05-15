#include <iostream>
#include <string>
#include <vector>
#include <limits> // For handling invalid input

#include "paiements.h"
#include "scores.h"
#include "reservations.h"
#include "places.h"
#include "personne.h" 
#include "joueurs.h"
#include "championnats.h"
#include "parties.h"
#include "tickets.h"
#include "clients.h" 
#include <iostream>
using namespace std;

<<<<<<< Updated upstream
void clearScreen() {
    system("cls"); // For Windows
=======
// Global Management Objects 
GestionJoueurs gestionJoueurs;
GestionTerrains gestionTerrains;
GestionReservations gestionReservations;
GestionScores gestionScores; 
GestionParties gestionParties;
ChampionnatSimple championnat; 
PlanificationParties planificateur;
Championnat championnat;  
// Helper Functions 
Partie retrievePartie(const string& nomJoueur1, const string& nomJoueur2) {
    // Implement logic to find the Partie based on player names
    // (You may need to iterate through your parties vector or use a more efficient search method)
    // ... 
    for (Partie& partie : gestionParties.getParties()) {
      if ((partie.nomJoueur1 == nomJoueur1 && partie.nomJoueur2 == nomJoueur2) || 
          (partie.nomJoueur1 == nomJoueur2 && partie.nomJoueur2 == nomJoueur1)) {
        return partie; 
      }
    }
    return Partie(SIMPLE, "unknown", "unknown"); // Return a default if not found
>>>>>>> Stashed changes
}


// Function to display the main menu options
void displayMainMenu() {
    clearScreen(); // Clear the screen for a clean menu display
    cout << "Tennis Championship Application" << endl;
    cout << "------------------------------" << endl;
    cout << "1. Manage Players" << endl;
    cout << "2. Manage Championships" << endl; 
    cout << "3. Manage Matches" << endl;
    cout << "4. Manage Tickets" << endl;
    cout << "5. Manage Clients" << endl;
    cout << "------------------------------" << endl;
    cout << "6. Manage Payments" << endl;
    cout << "7. Manage Scores" << endl;
    cout << "8. Manage Reservations" << endl;
    cout << "9. Manage Places" << endl;
    cout << "------------------------------" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to get the user's menu choice with input validation
int getUserChoice() {
    int choice;
    while (!(cin >> choice) || choice < 0 || choice > 9) {
        cout << "Invalid input. Please enter a number between 0 and 5: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining input
    }
    return choice;
}


// Function to display the player management menu
void displayJoueursMenu(GestionJoueurs& gestionJoueurs) {
    clearScreen();
    cout << "Player Management Menu" << endl;
    cout << "---------------------" << endl;
    cout << "1. Add a player" << endl;
    cout << "2. Remove a player" << endl;
    cout << "3. Update a player's information" << endl;
    cout << "4. Search for a player" << endl;
    cout << "5. Display all players" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    int choice = getUserChoice();

    switch (choice) {
        case 1: { // Add player
            std::string nom;
            int classement;
            std::cout << "Enter player name: ";
            std::cin >> nom;
            std::cout << "Enter player ranking: ";
            std::cin >> classement;
            // Input validation (example)
            if (classement < 1 || classement > 100) {
                std::cout << "Invalid ranking. Ranking must be between 1 and 100." << std::endl;
                break;
            }
            Joueur joueur(nom, classement); // Create Joueur object
            gestionJoueurs.ajouterJoueur(joueur); // Add player
            std::cout << "Player added successfully." << std::endl;
            break;
        }
        case 2: { // Remove player
            std::string nom;
            std::cout << "Enter player name: ";
            std::cin >> nom;
            gestionJoueurs.supprimerJoueur(nom); // Remove player
            std::cout << "Player removed successfully." << std::endl;
            break;
        }
        case 3: { // Update player's information
            std::string nom;
            std::cout << "Enter player name: ";
            std::cin >> nom;
            Joueur joueur = gestionJoueurs.rechercherJoueur(nom); // Find player
            if (joueur.getNom() == "") {
                std::cout << "Player not found." << std::endl;
                break;
            }
            std::cout << "Enter new player name: ";
            std::cin >>nom; joueur.setNom(nom);
            std::cout << "Enter new player ranking: ";
            std::cin >> joueur.setClassement();
            gestionJoueurs.modifierJoueur(joueur); // Update player
            std::cout << "Player updated successfully." << std::endl;
            break;
        }
        case 4: { // Search for a player
            std::string nom;
            std::cout << "Enter player name: ";
            std::cin >> nom;
            Joueur joueur = gestionJoueurs.rechercherJoueur(nom); // Find player
            if (joueur.getNom() == "") {
                std::cout << "Player not found." << std::endl;
                break;
            }
            std::cout << "Player found:" << std::endl;
            std::cout << "Name: " << joueur.getNom() << std::endl;
            std::cout << "Ranking: " << joueur.getClassement() << std::endl;
            break;
        }
        case 5: { // Display all players
            std::vector<Joueur> joueurs = gestionJoueurs.obtenirJoueurs(); // Get all players
            if (joueurs.empty()) {
                std::cout << "No players found." << std::endl;
                break;
            }
            std::cout << "Players:" << std::endl;
            for (Joueur joueur : joueurs) {
                std::cout << "Name: " << joueur.getNom() << std::endl;
                std::cout << "Ranking: " << joueur.getClassement() << std::endl;
            }
            break;
        }

        case 6: // exit

            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

void displayChampionnatsMenu() {
    clearScreen();
    cout << "Championship Management Menu" << endl;
    cout << "---------------------" << endl;
    cout << "1. Add a championship" << endl;
    cout << "2. Remove a championship" << endl;
    cout << "3. Update a championship's information" << endl;
    cout << "4. Search for a championship" << endl;
    cout << "5. Display all championships" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    int choice = getUserChoice();
    switch (choice) {
        case 1: { // Add a championship
            std::string nom;
            std::cout << "Enter championship name: ";
            std::cin >> nom;
            gestionChampionnats.ajouterChampionnat(nom); // Add championship
            std::cout << "Championship added successfully." << std::endl;
            break;
        }
        case 2: { // Remove a championship
            std::string nom;
            std::cout << "Enter championship name: ";
            std::cin >> nom;
            gestionChampionnats.supprimerChampionnat(nom); // Remove championship
            std::cout << "Championship removed successfully." << std::endl;
            break;
        }
        case 3: { // Update a championship's information
            std::string nom;
            std::cout << "Enter championship name: ";
            std::cin >> nom;
            Championnat championnat = gestionChampionnats.rechercherChampionnat(nom); // Find championship
            if (championnat.getNom() == "") {
                std::cout << "Championship not found." << std::endl;
                break;
            }
            std::cout << "Enter new championship name: ";
            std::cin >> championnat.setNom();
            gestionChampionnats.modifierChampionnat(championnat); // Update championship
            std::cout << "Championship updated successfully." << std::endl;
            break;
        }
        case 4: { // Search for a championship
            std::string nom;
            std::cout << "Enter championship name: ";
            std::cin >> nom;
            Championnat championnat = gestionChampionnats.rechercherChampionnat(nom); // Find championship
            if (championnat.getNom() == "") {
                std::cout << "Championship not found." << std::endl;
                break;
            }
            std::cout << "Championship found:" << std::endl;
            std::cout << "Name: " << championnat.getNom() << std::endl;
            break;
        }
        case 5: { // Display all championships
            std::vector<Championnat> championnats = gestionChampionnats.obtenirChampionnats(); // Get all championships
            if (championnats.empty()) {
                std::cout << "No championships found." << std::endl;
                break;
            }
            std::cout << "Championships:" << std::endl;
            for (Championnat championnat : championnats) {
                std::cout << "Name: " << championnat.getNom() << std::endl;
            }
            break;
        }
        case 6: // exit
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

void displayPartiesMenu() {
    clearScreen();
    cout << "Match Management Menu" << endl;
    cout << "---------------------" << endl;
    cout << "1. Add a match" << endl;
    cout << "2. Remove a match" << endl;
    cout << "3. Update a match's information" << endl;
    cout << "4. Search for a match" << endl;
    cout << "5. Display all matches" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    int choice = getUserChoice();
    switch (choice) {
        case 1: { // Add a match
            std::string nom;
            std::cout << "Enter match name: ";
            std::cin >> nom;
            gestionParties.ajouterMatch(nom); // Add match
            std::cout << "Match added successfully." << std::endl;
            break;
        }
        case 2: { // Remove a match
            std::string nom;
            std::cout << "Enter match name: ";
            std::cin >> nom;
            gestionParties.supprimerMatch(nom); // Remove match
            std::cout << "Match removed successfully." << std::endl;
            break;
        }
        case 3: { // Update a match's information
            std::string nom;
            std::cout << "Enter match name: ";
            std::cin >> nom;
            Match match = gestionParties.rechercherMatch(nom); // Find match
            if (match.getNom() == "") {
                std::cout << "Match not found." << std::endl;
                break;
            }
            std::cout << "Enter new match name: ";
            std::cin >> match.setNom();
            gestionParties.modifierMatch(match); // Update match
            std::cout << "Match updated successfully." << std::endl;
            break;
        }
        case 4: { // Search for a match
            std::string nom;
            std::cout << "Enter match name: ";
            std::cin >> nom;
            Match match = gestionParties.rechercherMatch(nom); // Find match
            if (match.getNom() == "") {
                std::cout << "Match not found." << std::endl;
                break;
            }
            std::cout << "Match found:" << std::endl;
            std::cout << "Name: " << match.getNom() << std::endl;
            break;
        }
        case 5: { // Display all matches
            std::vector<Match> matches = gestionParties.obtenirMatches(); // Get all matches
            if (matches.empty()) {
                std::cout << "No matches found." << std::endl;
                break;
            }
            std::cout << "Matches:" << std::endl;
            for (Match match : matches) {
                std::cout << "Name: " << match.getNom() << std::endl;
        case 6: // exit
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

void displayTicketsMenu() {
    clearScreen();
    cout << "Ticket Management Menu" << endl;
    cout << "---------------------" << endl;
    cout << "1. Add a ticket" << endl;
    cout << "2. Remove a ticket" << endl;
    cout << "3. Update a ticket's information" << endl;
    cout << "4. Search for a ticket" << endl;
    cout << "5. Display all tickets" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    int choice = getUserChoice();
    switch (choice) {
        case 1: { // Add a ticket
            std::string nom;
            std::cout << "Enter ticket name: ";
            std::cin >> nom;
            gestionTickets.ajouterTicket(nom); // Add ticket
            std::cout << "Ticket added successfully." << std::endl;
            break;
        }
        case 2: { // Remove a ticket
            std::string nom;
            std::cout << "Enter ticket name: ";
            std::cin >> nom;
            gestionTickets.supprimerTicket(nom); // Remove ticket
            std::cout << "Ticket removed successfully." << std::endl;
            break;
        }
        case 3: { // Update a ticket's information
            std::string nom;
            std::cout << "Enter ticket name: ";
            std::cin >> nom;
            Ticket ticket = gestionTickets.rechercherTicket(nom); // Find ticket
            if (ticket.getNom() == "") {
                std::cout << "Ticket not found." << std::endl;
                break;
            }
            std::cout << "Enter new ticket name: ";
            std::cin >> ticket.setNom();
            gestionTickets.modifierTicket(ticket); // Update ticket
            std::cout << "Ticket updated successfully." << std::endl;
            break;
        }
        case 4: { // Search for a ticket
            std::string nom;
            std::cout << "Enter ticket name: ";
            std::cin >> nom;
            Ticket ticket = gestionTickets.rechercherTicket(nom); // Find ticket
            if (ticket.getNom() == "") {
                std::cout << "Ticket not found." << std::endl;
                break;
            }
            std::cout << "Ticket found:" << std::endl;
            std::cout << "Name: " << ticket.getNom() << std::endl;
            break;
        }
        case 5: { // Display all tickets
            std::vector<Ticket> tickets = gestionTickets.obtenirTickets(); // Get all tickets
            if (tickets.empty()) {
                std::cout << "No tickets found." << std::endl;
                break;
            }
            std::cout << "Tickets:" << std::endl;
            for (Ticket ticket : tickets) {
                std::cout << "Name: " << ticket.getNom() << std::endl;
                std::cout << std::endl;
                }
            break;
        case 6: // exit
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

void displayClientsMenu() {
    clearScreen();
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
            std::string nom;
            std::cout << "Enter client name: ";
            std::cin >> nom;
            gestionClients.ajouterClient(nom); // Add client
            std::cout << "Client added successfully." << std::endl;
            break;
        }
        case 2: { // Remove a client
            std::string nom;
            std::cout << "Enter client name: ";
            std::cin >> nom;
            gestionClients.supprimerClient(nom); // Remove client
            std::cout << "Client removed successfully." << std::endl;
            break;
        }
        case 3: { // Update a client's information
            std::string nom;
            std::cout << "Enter client name: ";
            std::cin >> nom;
            Client client = gestionClients.rechercherClient(nom); // Find client
            if (client.getNom() == "") {
                std::cout << "Client not found." << std::endl;
                break;
            }
            std::cout << "Enter new client name: ";
            std::cin >> client.setNom();
            gestionClients.modifierClient(client); // Update client
            std::cout << "Client updated successfully." << std::endl;
            break;
        }
        case 4: { // Search for a client
            std::string nom;
            std::cout << "Enter client name: ";
            std::cin >> nom;
            Client client = gestionClients.rechercherClient(nom); // Find client
            if (client.getNom() == "") {
                std::cout << "Client not found." << std::endl;
                break;
            }
            std::cout << "Client found:" << std::endl;
            std::cout << "Name: " << client.getNom() << std::endl;
            break;
        }
        case 5: { // Display all clients
            std::vector<Client> clients = gestionClients.obtenirClients(); // Get all clients
            if (clients.empty()) {
                std::cout << "No clients found." << std::endl; 
                break;
            }
            std::cout << "Clients:" << std::endl;
            for (Client client : clients) {
                std::cout << "Name: " << client.getNom() << std::endl;
                std::cout << std::endl;
            }
            break;
        case 6: // exit
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}





int main() {


    GestionTickets gestionTickets;
    GestionClients gestionClients;
    GestionScores gestionScores;
    GestionReservations gestionReservations;
    GestionParties gestionParties;
    GestionJoueurs gestionJoueurs;

    // Main menu loop

    int choice;
    do {
        displayMainMenu();
        choice = getUserChoice();

        switch (choice) {
            case 1: 
                displayJoueursMenu();

<<<<<<< Updated upstream
                break; 
            case 2:
                displayChampionnatsMenu();
                break;
            case 3:
                displayPartiesMenu();

                break;
            case 4:
                displayTicketsMenu();
                break;
            case 5:
                displayClientsMenu();
                break;
            case 0:
                cout << "Exiting the application. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0; 
}
=======
  return 0;
}
>>>>>>> Stashed changes
