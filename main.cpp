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
#include "clients.h"

using namespace std;

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
  GestionClients gestionClients;
  GestionTickets gestionTickets;

  // Constructor
  TennisChampionship() {
    // Initialize the championship (load data from a file if needed)
    championnat = ChampionnatSimple("Grand Slam", 2023, 4);

    // Add some sample players for testing
    gestionJoueurs.ajouterJoueur(Joueur("Roger Federer", 1));
    gestionJoueurs.ajouterJoueur(Joueur("Rafael Nadal", 2));
    gestionJoueurs.ajouterJoueur(Joueur("Novak Djokovic", 3));
    gestionJoueurs.ajouterJoueur(Joueur("Carlos Alcaraz", 4));
  }

  // Menu functions (members of the TennisChampionship class)
  void displayMainMenu();
  void displayJoueursMenu();
  void displayTerrainsMenu();
  void displayPartiesMenu();
  void displayChampionnatsMenu();
  void displayReservationsMenu();
  void displayScoreManagementMenu();
  void displayClientsMenu();
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
  cout << "Player Management Menu" << endl;
  cout << "---------------------" << endl;
  cout << "1. Add a player" << endl;
  cout << "2. Remove a player" << endl;
  cout << "3. Update a player's information" << endl;
  cout << "4. Search for a player" << endl;
  cout << "5. Display all players" << endl;
  cout << "6. Sort players by ranking" << endl;
  cout << "7. Exit" << endl;
  cout << "Enter your choice: ";

  int choice = getUserChoice();

  switch (choice) {
    case 1: { // Add a player
      string nom;
      int classement;
      cout << "Enter player name: ";
      cin >> nom;
      cout << "Enter player ranking: ";
      cin >> classement;

      // Input Validation
      if (classement < 1 || classement > 100) {
        cout << "Invalid ranking. Ranking must be between 1 and 100." << endl;
        break;
      }

      Joueur joueur(nom, classement);
      this->gestionJoueurs.ajouterJoueur(joueur);
      cout << "Player added successfully." << endl;
      break;
    }
    case 2: { // Remove a player
      string nom;
      cout << "Enter player name: ";
      cin >> nom;
      if (!this->gestionJoueurs.supprimerJoueur(nom)) {
        cout << "Player not found." << endl;
      } else {
        cout << "Player removed successfully." << endl;
      }
      break;
    }
    case 3: { // Update player's information
      string nom;
      cout << "Enter player name: ";
      cin >> nom;
      Joueur* joueurToModify = this->gestionJoueurs.rechercherJoueur(nom);
      if (joueurToModify != nullptr) {
        cout << "Enter new player name: ";
        cin >> joueurToModify->nom;

        cout << "Enter new player ranking: ";
        int newRanking;
        cin >> newRanking;

        // Input Validation
        if (newRanking < 1 || newRanking > 100) {
          cout << "Invalid ranking. Ranking must be between 1 and 100." << endl;
          break;
        }

        joueurToModify->setClassement(newRanking);
        cout << "Player updated successfully." << endl;
      } else {
        cout << "Player not found." << endl;
      }
      break;
    }
    case 4: { // Search for a player
      string nom;
      cout << "Enter player name: ";
      cin >> nom;
      this->gestionJoueurs.rechercherJoueur(nom);
      break;
    }
    case 5: { // Display all players
      this->gestionJoueurs.afficherJoueurs();
      break;
    }
    case 6: { // Sort players by ranking
      this->gestionJoueurs.trierJoueursParClassement();
      break;
    }
    case 7:
      break; // Exit the Joueurs menu
    default:
      cout << "Invalid choice. Please try again." << endl;
  }
}

void TennisChampionship::displayTerrainsMenu() {
  cout << "Terrain Management Menu" << endl;
  cout << "---------------------" << endl;
  cout << "1. Add a terrain" << endl;
  cout << "2. Remove a terrain" << endl;
  cout << "3. Update a terrain's information" << endl;
  cout << "4. Search for a terrain" << endl;
  cout << "5. Display all terrains" << endl;
  cout << "6. Exit" << endl;
  cout << "Enter your choice: ";
  int choice = getUserChoice();

  switch (choice) {
    case 1: { // Add terrain
      int typeAsInt;
      int longueur;
      int largeur;

      cout << "Enter terrain type (0 - Dur, 1 - Terre battue, 2 - Gazon): ";
      cin >> typeAsInt;

      // Input Validation
      if (typeAsInt < 0 || typeAsInt > 2) {
        cout << "Invalid terrain type. Please enter a number between 0 and 2." << endl;
        break; // Or handle the error in another way
      }

      TypeTerrain type = static_cast<TypeTerrain>(typeAsInt);

      cout << "Enter terrain length: ";
      cin >> longueur;
      cout << "Enter terrain width: ";
      cin >> largeur;

      Terrain terrain(type, longueur, largeur);
      gestionTerrains.ajouterTerrain(terrain);
      cout << "Terrain added successfully." << endl;
      break;
    }
    case 2: { // Remove terrain
      int typeAsInt;
      int longueur;
      int largeur;

      cout << "Enter terrain type (0 - Dur, 1 - Terre battue, 2 - Gazon): ";
      cin >> typeAsInt;

      // Input Validation
      if (typeAsInt < 0 || typeAsInt > 2) {
        cout << "Invalid terrain type. Please enter a number between 0 and 2." << endl;
        break;
      }

      TypeTerrain type = static_cast<TypeTerrain>(typeAsInt);

      cout << "Enter terrain length: ";
      cin >> longueur;
      cout << "Enter terrain width: ";
      cin >> largeur;

      gestionTerrains.supprimerTerrain(type, longueur, largeur);
      cout << "Terrain removed successfully." << endl;
      break;
    }
    case 3: { // Update terrain's information
      int typeAsInt;
      int longueur;
      int largeur;

      cout << "Enter terrain type (0 - Dur, 1 - Terre battue, 2 - Gazon): ";
      cin >> typeAsInt;

      // Input Validation
      if (typeAsInt < 0 || typeAsInt > 2) {
        cout << "Invalid terrain type. Please enter a number between 0 and 2." << endl;
        break;
      }

      TypeTerrain type = static_cast<TypeTerrain>(typeAsInt);

      cout << "Enter terrain length: ";
      cin >> longueur;
      cout << "Enter terrain width: ";
      cin >> largeur;

      gestionTerrains.supprimerTerrain(type, longueur, largeur);
      cout << "Terrain updated successfully." << endl;
      break;
    }
    case 4: { // Search for terrain
      // Implement search functionality
      break;
    }
    case 5: { // Display all terrains
      gestionTerrains.afficherTerrains();
      break;
    }
    case 6:
      break; // Exit the terrains menu
    default:
      cout << "Invalid choice. Please try again." << endl;
  }
}

// Function to display the parties menu
void TennisChampionship::displayPartiesMenu() {
  cout << "Match Management Menu" << endl;
  cout << "---------------------" << endl;
  cout << "1. Add a match" << endl;
  cout << "2. Remove a match" << endl;
  cout << "3. Update a match's information" << endl;
  cout << "4. Search for a match" << endl;
  cout << "5. Display all matches" << endl;
  cout << "6. Gestion des championnats" << endl;
  cout << "7. Exit" << endl;
  cout << "Enter your choice: ";
  int choice = getUserChoice();

  switch (choice) {
    case 1: { // Add match
      TypePartie type;
      string nomJoueur1, nomJoueur2;

      cout << "Enter match type (0 - Simple, 1 - Double): ";
      cin >> type;

      cout << "Enter player 1 name: ";
      cin >> nomJoueur1;

      cout << "Enter player 2 name: ";
      cin >> nomJoueur2;

      Partie partie(type, nomJoueur1, nomJoueur2);
      gestionParties.ajouterPartie(partie);
      cout << "Match added successfully." << endl;
      break;
    }
    case 2: { // Remove match
      // Implement remove functionality
      // Example:
      cout << "Enter Player 1 Name: ";
      string nomJoueur1;
      cin >> nomJoueur1;

      cout << "Enter Player 2 Name: ";
      string nomJoueur2;
      cin >> nomJoueur2;

      gestionParties.supprimerPartie(SIMPLE, nomJoueur1, nomJoueur2);
      cout << "Match removed successfully." << endl;

      break;
    }
    case 3: { // Update match's information
      // Implement update functionality
      // Example:
      cout << "Enter Player 1 Name: ";
      string nomJoueur1;
      cin >> nomJoueur1;

      cout << "Enter Player 2 Name: ";
      string nomJoueur2;
      cin >> nomJoueur2;

    //  Partie partie = rechercherPartie(nomJoueur1, nomJoueur2);

      // Update match details (you'll need to decide what to update)
      // ...
      cout << "Match updated successfully." << endl;

      break;
    }
    case 4: { // Search for match
      // Implement search functionality
      // Example:
      cout << "Enter Player 1 Name: ";
      string nomJoueur1;
      cin >> nomJoueur1;

      cout << "Enter Player 2 Name: ";
      string nomJoueur2;
      cin >> nomJoueur2;

      Partie* partie = gestionParties.rechercherPartie(nomJoueur1, nomJoueur2);
      if (partie != nullptr) {
        partie->afficher();
      } else {
        cout << "Match not found." << endl;
      }
      break;
    }
    case 5: { // Display all matches
      gestionParties.afficherParties();
      break;
    }
    case 6:
      displayChampionnatsMenu();
      break; // Go to the Championships menu
    case 7:
      break; // Exit the matches menu
    default:
      cout << "Invalid choice. Please try again." << endl;
  }
}

// Function to display the reservations menu
void TennisChampionship::displayReservationsMenu() {
  cout << "Reservation Management Menu" << endl;
  cout << "---------------------" << endl;
  cout << "1. Add a reservation" << endl;
  cout << "2. Remove a reservation" << endl;
  cout << "3. Update a reservation's information" << endl;
  cout << "4. Search for a reservation" << endl;
  cout << "5. Display all reservations" << endl;
  cout << "6. Exit" << endl;
  cout << "Enter your choice: ";
  int choice = getUserChoice();

  switch (choice) {
    case 1: { // Add reservation
      // Implement add reservation functionality
      cout << "Enter Client Name: ";
      string nomClient;
      cin >> nomClient;

      Client* client = gestionClients.rechercherClient(nomClient);
      if (client != nullptr) {
        cout << "Enter Match Name (Player 1 vs. Player 2): ";
        string matchName;
        cin >> matchName;

        Partie* partie = gestionParties.rechercherPartie(matchName);
        if (partie != nullptr) {
          // Place Selection Logic (You'll need to replace this placeholder with your new logic)
          // ...

          Reservation reservation(client, partie);
          gestionReservations.ajouterReservation(reservation);
          cout << "Reservation added successfully." << endl;
        } else {
          cout << "Match not found." << endl;
        }
      } else {
        cout << "Client not found." << endl;
      }
      break;
    }
    case 2: { // Remove reservation
      // Implement remove reservation functionality
      cout << "Enter Client Name: ";
      string nomClient;
      cin >> nomClient;

      Client* client = gestionClients.rechercherClient(nomClient);
      if (client != nullptr) {
        cout << "Enter Match Name (Player 1 vs. Player 2): ";
        string matchName;
        cin >> matchName;

        Partie* partie = gestionParties.rechercherPartie(matchName);
        if (partie != nullptr) {
          // Place Selection Logic
          // ...

          gestionReservations.supprimerReservation(client, partie);
          cout << "Reservation removed successfully." << endl;
        } else {
          cout << "Match not found." << endl;
        }
      } else {
        cout << "Client not found." << endl;
      }
      break;
    }
    case 3: { // Update reservation's information
      // Implement update reservation functionality
      cout << "Enter Client Name: ";
      string nomClient;
      cin >> nomClient;

      Client* client = gestionClients.rechercherClient(nomClient);
      if (client != nullptr) {
        cout << "Enter Match Name (Player 1 vs. Player 2): ";
        string matchName;
        cin >> matchName;

        Partie* partie = gestionParties.rechercherPartie(matchName);
        if (partie != nullptr) {
          // Place Selection Logic
          // ...

          Reservation* reservation = gestionReservations.rechercherReservation(client, partie);
          if (reservation != nullptr) {
            // Update reservation details (e.g., change the place)
            // ...
            cout << "Reservation updated successfully." << endl;
          } else {
            cout << "Reservation not found." << endl;
          }
        } else {
          cout << "Match not found." << endl;
        }
      } else {
        cout << "Client not found." << endl;
      }
      break;
    }
    case 4: { // Search for reservation
      // Implement search functionality
      cout << "Enter Client Name: ";
      string nomClient;
      cin >> nomClient;

      Client* client = gestionClients.rechercherClient(nomClient);
      if (client != nullptr) {
        cout << "Enter Match Name (Player 1 vs. Player 2): ";
        string matchName;
        cin >> matchName;

        Partie* partie = gestionParties.rechercherPartie(matchName);
        if (partie != nullptr) {
          // Place Selection Logic
          // ...

          Reservation* reservation = gestionReservations.rechercherReservation(client, partie);
          if (reservation != nullptr) {
           // reservation->afficher();
          } else {
            cout << "Reservation not found." << endl;
          }
        } else {
          cout << "Match not found." << endl;
        }
      } else {
        cout << "Client not found." << endl;
      }
      break;
    }
    case 5: { // Display all reservations
      for (const Reservation& reservation : gestionReservations.getReservations()) {
        cout << "Client: " << reservation.getClient()->nom << endl;
        cout << "Match: " << reservation.getPartie()->getNomJoueur1() << " vs. " << reservation.getPartie()->getNomJoueur2() << endl;
        cout << endl;
      }
      break;
    }
    case 6:
      break; // Exit the reservations menu
    default:
      cout << "Invalid choice. Please try again." << endl;
  }
}

void TennisChampionship::displayChampionnatsMenu() {
  cout << "Championship Management Menu" << endl;
  cout << "---------------------" << endl;
  cout << "1. Add a championship" << endl;
  cout << "2. Remove a championship" << endl;
  cout << "3. Update a championship's information" << endl;
  cout << "4. Search for a championship" << endl;
  cout << "5. Display all championships" << endl;
  cout << "6. Schedule Matches" << endl;
  cout << "7. Exit" << endl;
  cout << "Enter your choice: ";
  int choice = getUserChoice();

  switch (choice) {
    case 1: { // Add championship
      string nom;
      int annee;
      int nbTours;
      cout << "Enter championship name: ";
      cin >> nom;
      cout << "Enter championship year: ";
      cin >> annee;
      cout << "Enter number of rounds: ";
      cin >> nbTours;
      championnat = ChampionnatSimple(nom, annee, nbTours); // Create the championship
      cout << "Championship added successfully." << endl;
      break;
    }
    case 2: { // Remove championship
      // Implement remove championship functionality
      break;
    }
    case 3: { // Update championship's information
      // Implement update championship functionality
      break;
    }
    case 4: { // Search for championship
      // Implement search functionality
      break;
    }
    case 5: { // Display all championships
      // Implement display all championships functionality
      break;
    }
    case 6: { // Schedule Matches
      // Implement scheduling functionality
      cout << "Scheduling matches..." << endl;
      planificateur.creerParties16emes();
      // ... other scheduling logic 
      cout << "Matches scheduled!" << endl;
      break;
    }
    case 7:
      break; // Exit the championships menu
    default:
      cout << "Invalid choice. Please try again." << endl;
  }
}

// Function to display the score management menu
void TennisChampionship::displayScoreManagementMenu() {
  cout << "Score Management Menu" << endl;
  cout << "---------------------" << endl;
  cout << "1. Add a score" << endl;
  cout << "2. Remove a score" << endl;
  cout << "3. Update a score" << endl;
  cout << "4. Search for a score" << endl;
  cout << "5. Display all scores" << endl;
  cout << "6. Display Top Scorers" << endl;
  cout << "7. Exit" << endl;
  cout << "Enter your choice: ";
  int choice = getUserChoice();

  switch (choice) {
    case 1: { // Add score
      // Implement add score functionality
      break;
    }
    case 2: { // Remove score
      // Implement remove score functionality
      break;
    }
    case 3: { // Update score
      // Implement update score functionality
      break;
    }
    case 4: { // Search for score
      // Implement search functionality
      break;
    }
    case 5: { // Display all scores
      // Implement display all scores functionality
      gestionScores.afficherScores();
      break;
    }
    case 6: { // Display Top Scorers
      int numScoresToDisplay;
      cout << "Enter the number of top scores to display: ";
      cin >> numScoresToDisplay;

      vector<Score> topScores = gestionScores.getTopScores(numScoresToDisplay);
      if (!topScores.empty()) {
        for (const Score& score : topScores) {
          score.afficher();
        }
      } else {
        cout << "No scores available." << endl;
      }
      break;
    }
    case 7:
      break; // Exit the score management menu
    default:
      cout << "Invalid choice. Please try again." << endl;
  }
}

// Function to display the clients menu
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

TypePartie getMatchTypeFromUser() {
  int input;
  cout << "Enter match type (0 - Simple, 1 - Double): ";
  cin >> input;

  if (input == 0) {
    return SIMPLE;
  } else if (input == 1) {
    return DOUBLE;
  } else {
    cout << "Invalid input. Please enter 0 for Simple or 1 for Double: ";
    return getMatchTypeFromUser();
  }
}

int main() {
  // ... (Initialize your data, perhaps by loading from a file)
  TennisChampionship tennisChampionship; // Create an instance
  PlanificationParties planificateur(&tennisChampionship); // Pass the instance

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