#include <iostream>
#include <vector>
#include <limits>
#include "joueurs.h"
#include "terrains.h"
#include "parties.h"
#include "reservations.h"
#include "tennis_championnat.h"
#include "championnats.h"
#include "tickets.h"
#include "scores.h"
#include "clients.h"
#include "planner.h"

using namespace std;

// --- Tennis Championship Application ---
TennisChampionship tennisChampionship;
ChampionnatSimple championnat("Grand Slam", 2023, 4);
PlanificationParties planificateur(&tennisChampionship);

// --- Menu Display Functions ---
void displayMainMenu()
{
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

// --- Menu Functions for Each Section ---

void displayJoueursMenu()
{
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

  switch (choice)
  {
  case 1:
  { // Add a player
    string nom;
    int classement;
    cout << "Enter player name: ";
    cin >> nom;
    cout << "Enter player ranking: ";
    cin >> classement;

    // Input Validation
    if (classement < 1 || classement > 100)
    {
      cout << "Invalid ranking. Ranking must be between 1 and 100." << endl;
      break;
    }

    Joueur joueur(nom, classement);
    tennisChampionship.gestionJoueurs.ajouterJoueur(joueur);
    cout << "Player added successfully." << endl;
    break;
  }
  case 2:
  { // Remove a player
    string nom;
    cout << "Enter player name: ";
    cin >> nom;
    if (!tennisChampionship.gestionJoueurs.supprimerJoueur(nom))
    {
      cout << "Player not found." << endl;
    }
    else
    {
      cout << "Player removed successfully." << endl;
    }
    break;
  }
  case 3:
  { // Update player's information
    string nom;
    cout << "Enter player name: ";
    cin >> nom;
    Joueur *joueurToModify = tennisChampionship.gestionJoueurs.rechercherJoueur(nom);
    if (joueurToModify != nullptr)
    {
      cout << "Enter new player name: ";
      cin >> joueurToModify->nom;

      cout << "Enter new player ranking: ";
      int newRanking;
      cin >> newRanking;

      // Input Validation
      if (newRanking < 1 || newRanking > 100)
      {
        cout << "Invalid ranking. Ranking must be between 1 and 100." << endl;
        break;
      }

      joueurToModify->setClassement(newRanking);
      cout << "Player updated successfully." << endl;
    }
    else
    {
      cout << "Player not found." << endl;
    }
    break;
  }
  case 4:
  { // Search for a player
    string nom;
    cout << "Enter player name: ";
    cin >> nom;
    tennisChampionship.gestionJoueurs.rechercherJoueur(nom);
    break;
  }
  case 5:
  { // Display all players
    tennisChampionship.gestionJoueurs.afficherJoueurs();
    break;
  }
  case 6:
  { // Sort players by ranking
    tennisChampionship.gestionJoueurs.trierJoueursParClassement();
    break;
  }
  case 7:
    break; // Exit the Joueurs menu
  default:
    cout << "Invalid choice. Please try again." << endl;
  }
}

void displayTerrainsMenu()
{
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

  switch (choice)
  {
  case 1:
  { // Add terrain
    int typeAsInt;
    int longueur;
    int largeur;

    cout << "Enter terrain type (0 - Dur, 1 - Terre battue, 2 - Gazon): ";
    cin >> typeAsInt;

    // Input Validation
    if (typeAsInt < 0 || typeAsInt > 2)
    {
      cout << "Invalid terrain type. Please enter a number between 0 and 2." << endl;
      break; // Or handle the error in another way
    }

    TypeTerrain type = static_cast<TypeTerrain>(typeAsInt);

    cout << "Enter terrain length: ";
    cin >> longueur;
    cout << "Enter terrain width: ";
    cin >> largeur;

    Terrain terrain(type, longueur, largeur); // Declare and initialize the terrain variable
    tennisChampionship.gestionTerrains.ajouterTerrain(terrain);
    cout << "Terrain added successfully." << endl;
    break;
  }
  case 2:
  { // Remove terrain
    int typeAsInt;
    int longueur;
    int largeur;

    cout << "Enter terrain type (0 - Dur, 1 - Terre battue, 2 - Gazon): ";
    cin >> typeAsInt;

    // Input Validation
    if (typeAsInt < 0 || typeAsInt > 2)
    {
      cout << "Invalid terrain type. Please enter a number between 0 and 2." << endl;
      break;
    }

    TypeTerrain type = static_cast<TypeTerrain>(typeAsInt);

    cout << "Enter terrain length: ";
    cin >> longueur;
    cout << "Enter terrain width: ";
    cin >> largeur;

    tennisChampionship.gestionTerrains.supprimerTerrain(type, longueur, largeur);
    cout << "Terrain removed successfully." << endl;
    break;
  }
  case 3:
  { // Update terrain's information
    int typeAsInt;
    int longueur;
    int largeur;

    cout << "Enter terrain type (0 - Dur, 1 - Terre battue, 2 - Gazon): ";
    cin >> typeAsInt;

    // Input Validation
    if (typeAsInt < 0 || typeAsInt > 2)
    {
      cout << "Invalid terrain type. Please enter a number between 0 and 2." << endl;
      break;
    }

    TypeTerrain type = static_cast<TypeTerrain>(typeAsInt);

    cout << "Enter terrain length: ";
    cin >> longueur;
    cout << "Enter terrain width: ";
    cin >> largeur;

    tennisChampionship.gestionTerrains.supprimerTerrain(type, longueur, largeur);
    cout << "Terrain updated successfully." << endl;
    break;
  }
  case 4:
  { // Search for terrain
    // Implement search functionality
    break;
  }
  case 5:
  { // Display all terrains
    tennisChampionship.gestionTerrains.afficherTerrains();
    break;
  }
  case 6:
    break; // Exit the terrains menu
  default:
    cout << "Invalid choice. Please try again." << endl;
  }
}

// Function to display the parties menu
void displayPartiesMenu()
{
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

  switch (choice)
  {
  case 1:
  { // Add match
    TypePartie type;
    string nomJoueur1, nomJoueur2;

    cout << "Enter match type (0 - Simple, 1 - Double): ";
    cin >> type;

    cout << "Enter player 1 name: ";
    cin >> nomJoueur1;

    cout << "Enter player 2 name: ";
    cin >> nomJoueur2;

    Partie partie(type, nomJoueur1, nomJoueur2);
    tennisChampionship.gestionParties.ajouterPartie(partie);
    cout << "Match added successfully." << endl;
    break;
  }
  case 2:
  { // Remove match
    // Implement remove functionality
    // Example:
    cout << "Enter Player 1 Name: ";
    string nomJoueur1;
    cin >> nomJoueur1;

    cout << "Enter Player 2 Name: ";
    string nomJoueur2;
    cin >> nomJoueur2;

    tennisChampionship.gestionParties.supprimerPartie(SIMPLE, nomJoueur1, nomJoueur2);
    cout << "Match removed successfully." << endl;

    break;
  }
  case 3:
  { // Update match's information
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
  case 4:
  { // Search for match
    // Implement search functionality
    // Example:
    cout << "Enter Player 1 Name: ";
    string nomJoueur1;
    cin >> nomJoueur1;

    cout << "Enter Player 2 Name: ";
    string nomJoueur2;
    cin >> nomJoueur2;

    Partie *partie = tennisChampionship.gestionParties.rechercherPartie(nomJoueur1, nomJoueur2);
    if (partie != nullptr)
    {
      partie->afficher();
    }
    else
    {
      cout << "Match not found." << endl;
    }
    break;
  }
  case 5:
  { // Display all matches
    tennisChampionship.gestionParties.afficherParties();
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
void displayReservationsMenu()
{
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

  switch (choice)
  {
  case 1:
  { // Add reservation
    // Implement add reservation functionality
    cout << "Enter Client Name: ";
    string nomClient;
    cin >> nomClient;

    Client *client = tennisChampionship.gestionClients.rechercherClient(nomClient);
    if (client != nullptr)
    {
      cout << "Enter Match Name (Player 1 vs. Player 2): ";
      string matchName;
      cin >> matchName;

      Partie *partie = tennisChampionship.gestionParties.rechercherPartie(matchName);
      if (partie != nullptr)
      {
        // Place Selection Logic (You'll need to replace this placeholder with your new logic)
        // ...

        cout << "Enter Length: ";
        int longueur;
        cin >> longueur;

        cout << "Enter Width: ";
        int largeur;
        cin >> largeur;

        cout << "Enter terrain type (Dur, Terre battue, Gazon): "; // Change the prompt
        string terrainType;
        cin >> terrainType;

        TypeTerrain type = stringToTypeTerrain(terrainType); // Convert the string

        // ... (Rest of your code) ...

        Terrain *terrain = tennisChampionship.gestionTerrains.rechercherTerrain(type, longueur, largeur);
        if (terrain == nullptr)
        {
          cout << "No available terrains for this match. Cannot create reservation." << endl;
          break;
        }

        // Select a seat on the terrain (you'll need to prompt the user)
        // ...
        int row, col;
        cout << "Enter the row number: ";
        cin >> row;
        cout << "Enter the column number: ";
        cin >> col;

        if (terrain->isSeatAvailable(row, col))
        {
          terrain->reserveSeat(row, col);
          Reservation reservation(client, partie); // Create Reservation
          reservation.setTerrain(terrain);         // Assign the selected terrain
          tennisChampionship.gestionReservations.ajouterReservation(reservation);
          cout << "Reservation added successfully." << endl;
        }
        else
        {
          cout << "Seat is not available. Please choose another seat." << endl;
        }
      }
      else
      {
        cout << "Match not found." << endl;
      }
    }
    else
    {
      cout << "Client not found." << endl;
    }
    break;
  }
  case 2:
  { // Remove reservation
    // Implement remove reservation functionality
    cout << "Enter Client Name: ";
    string nomClient;
    cin >> nomClient;

    Client *client = tennisChampionship.gestionClients.rechercherClient(nomClient);
    if (client != nullptr)
    {
      cout << "Enter Match Name (Player 1 vs. Player 2): ";
      string matchName;
      cin >> matchName;

      Partie *partie = tennisChampionship.gestionParties.rechercherPartie(matchName);
      if (partie != nullptr)
      {
        // Place Selection Logic
        // ...

        tennisChampionship.gestionReservations.supprimerReservation(client, partie);
        cout << "Reservation removed successfully." << endl;
      }
      else
      {
        cout << "Match not found." << endl;
      }
    }
    else
    {
      cout << "Client not found." << endl;
    }
    break;
  }
  case 3:
  { // Update reservation's information
    // Implement update reservation functionality
    cout << "Enter Client Name: ";
    string nomClient;
    cin >> nomClient;

    Client *client = tennisChampionship.gestionClients.rechercherClient(nomClient);
    if (client != nullptr)
    {
      cout << "Enter Match Name (Player 1 vs. Player 2): ";
      string matchName;
      cin >> matchName;

      Partie *partie = tennisChampionship.gestionParties.rechercherPartie(matchName);
      if (partie != nullptr)
      {
        // Place Selection Logic
        // ...

        Reservation *reservation = tennisChampionship.gestionReservations.rechercherReservation(client, partie);
        if (reservation != nullptr)
        {
          // Update reservation details (e.g., change the place)
          // ...
          cout << "Reservation updated successfully." << endl;
        }
        else
        {
          cout << "Reservation not found." << endl;
        }
      }
      else
      {
        cout << "Match not found." << endl;
      }
    }
    else
    {
      cout << "Client not found." << endl;
    }
    break;
  }
  case 4:
  { // Search for reservation
    // Implement search functionality
    cout << "Enter Client Name: ";
    string nomClient;
    cin >> nomClient;

    Client *client = tennisChampionship.gestionClients.rechercherClient(nomClient);
    if (client != nullptr)
    {
      cout << "Enter Match Name (Player 1 vs. Player 2): ";
      string matchName;
      cin >> matchName;

      Partie *partie = tennisChampionship.gestionParties.rechercherPartie(matchName);
      if (partie != nullptr)
      {
        // Place Selection Logic
        // ...

        Reservation *reservation = tennisChampionship.gestionReservations.rechercherReservation(client, partie);
        if (reservation != nullptr)
        {
          reservation->afficher(); // Call afficher() on the Reservation object
        }
        else
        {
          cout << "Reservation not found." << endl;
        }
      }
      else
      {
        cout << "Match not found." << endl;
      }
    }
    else
    {
      cout << "Client not found." << endl;
    }
    break;
  }
  case 5:
  { // Display all reservations
    for (const Reservation &reservation : tennisChampionship.gestionReservations.getReservations())
    {
      cout << "Client: " << reservation.getClient()->getNom() << endl;
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

void displayChampionnatsMenu()
{
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

  switch (choice)
  {
  case 1:
  { // Add championship
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
  case 2:
  { // Remove championship
    // Implement remove championship functionality
    break;
  }
  case 3:
  { // Update championship's information
    // Implement update championship functionality
    break;
  }
  case 4:
  { // Search for championship
    // Implement search functionality
    break;
  }
  case 5:
  { // Display all championships
    // Implement display all championships functionality
    break;
  }
  case 6:
  { // Schedule Matches

    break;
  }
  case 7:
    break; // Exit the championships menu
  default:
    cout << "Invalid choice. Please try again." << endl;
  }
}

// Function to display the score management menu
void displayScoreManagementMenu()
{
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

  switch (choice)
  {
  case 1:
  { // Add score
    // Implement add score functionality
    break;
  }
  case 2:
  { // Remove score
    // Implement remove score functionality
    break;
  }
  case 3:
  { // Update score
    // Implement update score functionality
    break;
  }
  case 4:
  { // Search for score
    // Implement search functionality
    break;
  }
  case 5:
  { // Display all scores
    // Implement display all scores functionality
    tennisChampionship.gestionScores.afficherScores();
    break;
  }
  case 6:
  { // Display Top Scorers
    int numScoresToDisplay;
    cout << "Enter the number of top scores to display: ";
    cin >> numScoresToDisplay;

    vector<Score> topScores = tennisChampionship.gestionScores.getTopScores(numScoresToDisplay);
    if (!topScores.empty())
    {
      for (const Score &score : topScores)
      {
        score.afficher();
      }
    }
    else
    {
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
void displayClientsMenu()
{
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

  switch (choice)
  {
  case 1:
  { // Add a client
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
    tennisChampionship.gestionClients.ajouterClient(client);
    cout << "Client added successfully." << endl;
    break;
  }
  case 2:
  { // Remove a client
    string nom;
    cout << "Enter client name: ";
    cin >> nom;
    if (!tennisChampionship.gestionClients.supprimerClient(nom))
    {
      cout << "Client not found." << endl;
    }
    else
    {
      cout << "Client removed successfully." << endl;
    }
    break;
  }
  case 3:
  { // Update a client's information
    string nom;
    cout << "Enter client name: ";
    cin >> nom;
    Client *clientToUpdate = tennisChampionship.gestionClients.rechercherClient(nom);
    if (clientToUpdate != nullptr)
    {
      string newNom;
      int newAge;
      string newAdresse;
      string newTelephone;

      cout << "Enter new client name: ";
      cin >> newNom;
      clientToUpdate->setNom(newNom); // Use the setter to update the client's name

      cout << "Enter new client age: ";
      cin >> newAge;
      clientToUpdate->setAge(newAge); // Use the setter to update the client's age

      cout << "Enter new client address: ";
      cin >> newAdresse;
      clientToUpdate->setAdresse(newAdresse); // Use the setter to update the client's address

      cout << "Enter new client phone number: ";
      cin >> newTelephone;
      clientToUpdate->setTelephone(newTelephone); // Use the setter to update the client's phone number

      cout << "Client updated successfully." << endl;
    }
    else
    {
      cout << "Client not found." << endl;
    }
    break;
  }
  case 4:
  { // Search for a client
    string nom;
    cout << "Enter client name: ";
    cin >> nom;
    Client *client = tennisChampionship.gestionClients.rechercherClient(nom);
    if (client != nullptr)
    {
      client->afficher();
    }
    else
    {
      cout << "Client not found." << endl;
    }
    break;
  }
  case 5:
  { // Display all clients
    tennisChampionship.gestionClients.trierClientsParNom();
    for (const Client &client : tennisChampionship.gestionClients.getClients())
    {
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

void displayTicketsMenu()
{
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

  switch (choice)
  {
  case 1:
  { // Generate a ticket
    cout << "Enter ticket type (Standard or VIP): ";
    string type;
    cin >> type;

    cout << "Enter ticket price: ";
    double prix;
    cin >> prix;

    cout << "Enter match name (Player 1 vs. Player 2): ";
    string matchName;
    cin >> matchName;

    Ticket ticket = tennisChampionship.gestionTickets.genererTicket(type, prix, matchName);
    tennisChampionship.gestionTickets.ajouterTicket(ticket);
    cout << "Ticket generated successfully!" << endl;
    break;
  }
  case 2:
  { // Sell a ticket
    cout << "Enter ticket number: ";
    int ticketNumber;
    cin >> ticketNumber;

    bool success = tennisChampionship.gestionTickets.vendreTicket(tennisChampionship.gestionClients, ticketNumber);
    if (success)
    {
      cout << "Ticket sold successfully." << endl;
    }
    break;
  }
  case 3:
  { // Display all tickets
    tennisChampionship.gestionTickets.afficherTickets();
    break;
  }
  case 4:
  { // Search for a ticket
    cout << "Enter ticket number: ";
    int ticketNumber;
    cin >> ticketNumber;

    Ticket *ticket = tennisChampionship.gestionTickets.rechercherTicket(ticketNumber);
    if (ticket != nullptr)
    {
      ticket->afficher();
    }
    else
    {
      cout << "Ticket not found." << endl;
    }
    break;
  }
  case 5:
  { // Remove a ticket
    cout << "Enter ticket number: ";
    int ticketNumber;
    cin >> ticketNumber;

    tennisChampionship.gestionTickets.supprimerTicket(ticketNumber);
    cout << "Ticket removed successfully." << endl;
    break;
  }
  case 6:
    break; // Exit the Tickets menu
  default:
    cout << "Invalid choice. Please try again." << endl;
  }
}
TypeTerrain stringToTypeTerrain(const string &terrainType)
{
  if (terrainType == "Dur")
  {
    return DUR;
  }
  else if (terrainType == "Terre battue")
  {
    return TERRE_BATTUE;
  }
  else if (terrainType == "Gazon")
  {
    return GAZON;
  }
  else
  {
    throw std::invalid_argument("Invalid terrain type.");
  }
}

TypePartie getMatchTypeFromUser()
{
  int input;
  cout << "Enter match type (0 - Simple, 1 - Double): ";
  cin >> input;

  if (input == 0)
  {
    return SIMPLE;
  }
  else if (input == 1)
  {
    return DOUBLE;
  }
  else
  {
    cout << "Invalid input. Please enter 0 for Simple or 1 for Double: ";
    return getMatchTypeFromUser();
  }
}

int main()
{

  int selection;
  do
  {
    displayMainMenu();
    selection = getUserChoice();

    switch (selection)
    {
    // ... (Your menu logic here) ...
    case 1:
      displayJoueursMenu(); // Call the helper function
      break;
    case 2:
      displayTerrainsMenu();
      break;
    case 3:
      displayPartiesMenu();
      break;
    case 4:
      displayChampionnatsMenu();
      break;
    case 5:
      displayReservationsMenu();
      break;
    case 6:
      displayScoreManagementMenu();
      break;
    case 7:
      displayClientsMenu();
      break;
    case 8:
      displayTicketsMenu();
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