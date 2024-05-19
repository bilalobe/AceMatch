
using namespace std;

// --- Tennis Championship Application ---
TennisChampionship tennisChampionship;
ChampionnatSimple championnat("Grand Slam", 2023, 4);
PlanificationParties planificateur(&tennisChampionship);
GestionScores gestionScores; // Create an instance of GestionScores

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

// Helper function for menu selection
int getUserChoice()
{
  int choice;
  while (!(cin >> choice) || choice < 1 || choice > 9)
  {
    cout << "Invalid input. Please enter a number between 1 and 9: ";
    cin.clear();                                         // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining input
  }
  return choice;
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
  cout << "7. Go Back" << endl;
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
      string newNom;
      cout << "Enter new player name: ";
      cin >> newNom;
      joueurToModify->setNom(newNom); // Use the setter method

      cout << "Enter new player ranking: ";
      int newRanking;
      cin >> newRanking;

      // Input Validation
      if (newRanking < 1 || newRanking > 100)
      {
        cout << "Invalid ranking. Ranking must be between 1 and 100." << endl;
      }
      else
      {
        joueurToModify->setClassement(newRanking); // Use the setter method
        cout << "Player updated successfully." << endl;
      }
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
    break; // Go Back
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
  cout << "6. Go Back" << endl;
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
    break; // Go Back
  default:
    cout << "Invalid choice. Please try again." << endl;
  }
}

// Function to display the parties menu
void displayReservationsMenu()
{
  cout << "Reservation Management Menu" << endl;
  cout << "---------------------" << endl;
  cout << "1. Add a reservation" << endl;
  cout << "2. Remove a reservation" << endl;
  cout << "3. Update a reservation's information" << endl;
  cout << "4. Search for a reservation" << endl;
  cout << "5. Display all reservations" << endl;
  cout << "6. Go Back" << endl;
  cout << "Enter your choice: ";
  int choice = getUserChoice();

  switch (choice)
  {
  case 1:
  { // Add reservation
    cout << "Enter Client Name: ";
    string nomClient;
    cin >> nomClient;

    Client *client = tennisChampionship.gestionClients.rechercherClient(nomClient);
    if (client != nullptr)
    {
      cout << "Enter Player 1 Name: ";
      string nomJoueur1;
      cin >> nomJoueur1;

      cout << "Enter Player 2 Name: ";
      string nomJoueur2;
      cin >> nomJoueur2;

      Partie *partie = tennisChampionship.gestionParties.rechercherPartie(nomJoueur1, nomJoueur2);
      if (partie != nullptr)
      {
        int typeAsInt;
        cout << "Enter terrain type (0 - Dur, 1 - Terre battue, 2 - Gazon): ";
        cin >> typeAsInt;

        if (typeAsInt < 0 || typeAsInt > 2)
        {
          cout << "Invalid terrain type. Please enter a number between 0 and 2." << endl;
          break;
        }

        TypeTerrain type = static_cast<TypeTerrain>(typeAsInt);

        int longueur, largeur;
        cout << "Enter terrain length: ";
        cin >> longueur;

        cout << "Enter terrain width: ";
        cin >> largeur;

        Terrain *terrain = tennisChampionship.gestionTerrains.rechercherTerrain(type, longueur, largeur);

        if (terrain == nullptr)
        {
          cout << "No available terrains for this match. Cannot create reservation." << endl;
          break;
        }

        int row, col;
        terrain->afficherSeatingPlan();

        cout << "Enter the row number: ";
        cin >> row;
        cout << "Enter the column number: ";
        cin >> col;

        if (terrain->isSeatAvailable(row, col))
        {
          terrain->reserveSeat(row, col);
          Reservation reservation(client, partie, terrain, row, col);
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
    cout << "Enter Client Name: ";
    string nomClient;
    cin >> nomClient;

    Client *client = tennisChampionship.gestionClients.rechercherClient(nomClient);
    if (client != nullptr)
    {
      cout << "Enter Player 1 Name: ";
      string nomJoueur1;
      cin >> nomJoueur1;

      cout << "Enter Player 2 Name: ";
      string nomJoueur2;
      cin >> nomJoueur2;

      Partie *partie = tennisChampionship.gestionParties.rechercherPartie(nomJoueur1, nomJoueur2);
      if (partie != nullptr)
      {
        int row, col;
        cout << "Enter the row number: ";
        cin >> row;
        cout << "Enter the column number: ";
        cin >> col;

        tennisChampionship.gestionReservations.supprimerReservation(client, partie, row, col);
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
  { // Update reservation
    cout << "Enter Client Name: ";
    string nomClient;
    cin >> nomClient;

    Client *client = tennisChampionship.gestionClients.rechercherClient(nomClient);
    if (client != nullptr)
    {
      cout << "Enter Player 1 Name: ";
      string nomJoueur1;
      cin >> nomJoueur1;

      cout << "Enter Player 2 Name: ";
      string nomJoueur2;
      cin >> nomJoueur2;

      Partie *partie = tennisChampionship.gestionParties.rechercherPartie(nomJoueur1, nomJoueur2);
      if (partie != nullptr)
      {
        // Add terrain details and reservation search logic if needed
                        int row, col;
        cout << "Enter the row number: ";
        cin >> row;
        cout << "Enter the column number: ";
        cin >> col;

        Reservation *reservation = tennisChampionship.gestionReservations.rechercherReservation(client, partie, row, col);
        if (reservation != nullptr)
        {
          // Update reservation details
          // ...
          cout << "Reservation updated successfully." << endl;
        }
        else
        {
          cout << "Reservation not found." << endl;
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

  case 4: // Search for reservation
  {
    cout << "Enter Client Name: ";
    string nomClient;
    cin >> nomClient;

    Client *client = tennisChampionship.gestionClients.rechercherClient(nomClient);
    if (client != nullptr)
    {
      cout << "Enter Player 1 Name: ";
      string joueur1;
      cin >> joueur1;

      cout << "Enter Player 2 Name: ";
      string joueur2;
      cin >> joueur2;

      Partie *partie = tennisChampionship.gestionParties.rechercherPartie(joueur1, joueur2);
      if (partie != nullptr)
      {
        cout << "Enter the row number: ";
        int row;
        cin >> row;
        cout << "Enter the column number: ";
        int col;
        cin >> col;

        Reservation *reservation = tennisChampionship.gestionReservations.rechercherReservation(client, partie, row, col);
        if (reservation != nullptr)
        {
          reservation->afficher();
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
      cout << "Terrain: " << reservation.getTerrain()->getType() << endl;
      cout << "Row: " << reservation.getRow() << endl;
      cout << "Column: " << reservation.getCol() << endl;
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
  cout << "7. Go Back" << endl;
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
    // Implement scheduling functionality
    cout << "Scheduling matches..." << endl;
    planificateur.creerParties16emes();
    // ... other scheduling logic
    cout << "Matches scheduled!" << endl;
    break;
  }
  case 7:
    break; // Go Back
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
  cout << "4. Search for a score" << endl; // You can add this if needed
  cout << "5. Display all scores" << endl;
  cout << "6. Display Top Scorers" << endl;
  cout << "7. Go Back" << endl;
  cout << "Enter your choice: ";
  int choice = getUserChoice();

  switch (choice)
  {
  case 1:
  { // Add score
    int matchNumber;
    int scorePlayer1, scorePlayer2;
    cout << "Enter the match number: ";
    cin >> matchNumber;

    // Get the match name based on matchNumber (you need to implement this logic)
    string matchName = getMatchNameFromMatchNumber(matchNumber); // Add this function

    Partie *partie = tennisChampionship.gestionParties.rechercherPartie(matchName); // Search by name

    if (partie != nullptr)
    {
      Score score(*partie, scorePlayer1, scorePlayer2);
      gestionScores.ajouterScore(score);
      cout << "Score added successfully." << endl;
    }
    else
    {
      cout << "Match not found." << endl;
    }
    break;
  }
  case 2:
  { // Remove score
    int matchNumber;
    cout << "Enter the match number to remove the score: ";
    cin >> matchNumber;
    gestionScores.supprimerScore(matchNumber);
    cout << "Score removed successfully." << endl;
    break;
  }
  case 3:
  { // Update a score
    int matchNumber;
    int scorePlayer1, scorePlayer2;
    cout << "Enter the match number to update the score: ";
    cin >> matchNumber;
    cout << "Enter the new score for player 1: ";
    cin >> scorePlayer1;
    cout << "Enter the new score for player 2: ";
    cin >> scorePlayer2;
    gestionScores.mettreAJourScore(matchNumber, scorePlayer1, scorePlayer2);
    cout << "Score updated successfully." << endl;
    break;
  }
  case 4:
  { // Display all scores
    gestionScores.afficherScores();
    break;
  }
  case 5:
  { // Display Top Scorers
    int numScoresToDisplay;
    cout << "Enter the number of top scores to display: ";
    cin >> numScoresToDisplay;
    vector<Score> topScores = gestionScores.getTopScores(numScoresToDisplay);
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
  case 6:
    break;
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
  cout << "6. Sort clients by name" << endl;
  cout << "7. Go Back" << endl;
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
  {
    tennisChampionship.gestionClients.trierClientsParNom();
    cout << "Clients sorted by name!" << endl;
    break;
  }
  case 7:
    break; // Go Back
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
  cout << "6. Go Back" << endl;
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

    Partie *partie = tennisChampionship.gestionParties.rechercherPartie(matchName);
    if (partie == nullptr)
    {
      cout << "Match not found." << endl;
      break;
    }

    Reservation *reservation = tennisChampionship.gestionReservations.rechercherReservation(nullptr, partie);
    if (reservation == nullptr)
    {
      cout << "No reservation found for this match. Cannot generate ticket." << endl;

      break;
    }

    // Get the terrain from the reservation
    Terrain *terrain = reservation->getTerrain();
    int row = reservation->getRow();
    int col = reservation->getCol();

    if (terrain->isSeatAvailable(row, col))
    {
      terrain->reserveSeat(row, col);
      Ticket ticket = tennisChampionship.gestionTickets.genererTicket(type, prix, matchName, reservation); // Pass the reservation
      cout << "Ticket generated successfully!" << endl;
    }
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

      // Data Consistency: Mark the seat as occupied (assuming you have a way to get the reservation from the ticket)
      Ticket *ticket = tennisChampionship.gestionTickets.rechercherTicket(ticketNumber);
      if (ticket != nullptr)
      {
        Reservation *reservation = ticket->getReservation();
        if (reservation != nullptr)
        {
          // Assuming you have a way to get the row and col from the Reservation object
          int row = reservation->getRow();
          int col = reservation->getCol();
          reservation->getTerrain()->reserveSeat(row, col);
        }
      }
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
      cout << "Exiting program. Goodbye!" << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  } while (selection != 9);

  return 0;
}
