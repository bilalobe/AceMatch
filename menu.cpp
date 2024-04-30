#include <iostream>
#include <vector>
#include "joueurs.h"
#include "terrains.h"
#include "parties.h"
#include "reservations.h"
#include "menu.h"
#include "championnats.h"
#include "tickets.h"
#include "scores.h"

vector<Joueur> joueurs;
vector<Terrain> terrains;
vector<Partie> parties;
vector<Reservation> reservations;

using namespace std;
GestionParties gestionParties;
Championnat championnat;
Joueur joueur;
class Menu {
public:
  Menu(const vector<string>& options) : options(options) {}

  void display() {
    for (int i = 0; i < options.size(); i++) {
      cout << i + 1 << ". " << options[i] << endl;
    }
    cout << "Choix: ";
  }

  int getSelection() {
    int selection;
    cin >> selection;
    return selection;
  }

private:
  vector<string> options;
};

void displayJoueursMenu() {
  // Create the joueurs menu
  vector<string> joueursMenuOptions = {"Afficher la liste des joueurs", "Rechercher un joueur", "Modifier un joueur", "Supprimer un joueur","Trier les joueurs par classement","Retour au menu principal"};
  Menu joueursMenu(joueursMenuOptions);

  // Display the joueurs menu
  joueursMenu.display();

  // Get the user's selection
  int selection = joueursMenu.getSelection();

  // Handle the user's selection
  switch (selection) {
    case 1:
      void afficherJoueurs();
      break;
    case 2:
      void rechercherJoueur();
      break;
    case 3:
      void modifierJoueur();
      break;
    case 4:
      void supprimerJoueur();
      break;
    case 5:
       void trierJoueursParClassement();
      break;
    case 6:
      displayJoueursMenu();
      break;
    case 7:
      exit(0); // Quitter le programme
      break;
    default:
      cout << "Choix invalide" << endl;
      break;
  }
}

void displayTerrainsMenu() {
  // Create the terrains menu
  vector<string> terrainsMenuOptions = {"Afficher la liste des terrains", "Rechercher un terrain", "Modifier un terrain", "Supprimer un terrain", "Retour au menu principal"};
  Menu terrainsMenu(terrainsMenuOptions);

  // Display the terrains menu
  terrainsMenu.display();

  // Get the user's selection
  int selection = terrainsMenu.getSelection();

  // Handle the user's selection
  switch (selection) {
    case 1:
      void afficherTerrains();
      break;
    case 2:
      void rechercherTerrain();
      break;
    case 3:
      void modifierTerrain();
      break;
    case 4:
      void supprimerTerrain();
      break;
    case 5:
      displayTerrainsMenu();
      break;
    case 6:
      exit(0); // Quitter le programme
      break;
    default:
      cout << "Choix invalide" << endl;
      break;
  }
}

void displayPartiesMenu() {
    // Create the parties menu
    vector<string> partiesMenuOptions = { 
        "Afficher la liste des parties", 
        "Rechercher une partie", 
        "Saisir le résultat d'une partie", // Replace 'Modifier une partie' 
        "Supprimer une partie", 
        "Gestion des championnats", 
        "Retour au menu principal"};
    Menu partiesMenu(partiesMenuOptions);

    // Display the parties menu
    partiesMenu.display();

    // Get the user's selection
    int selection = partiesMenu.getSelection();

    // Handle the user's selection
    switch (selection) {
        case 1: 
            GestionParties.afficherParties();
            break;
        case 2: 
            // ... (Implement search functionality)
            break;
        case 3: // Saisir le résultat d'une partie
            { 
                cout << "Enter Player 1 Name: ";
                string nomJoueur1;
                cin >> nomJoueur1;

                cout << "Enter Player 2 Name: ";
                string nomJoueur2;
                cin >> nomJoueur2;

                Partie partie = retrievePartie(nomJoueur1, nomJoueur2);

                // Get match results
                cout << "Enter result for Player 1 (0 - Match Nul, 1 - Victoire, 2 - Defaite): ";
                int resultPlayer1; 
                cin >> resultPlayer1; 

                // ... Similar input for Player 2

                setResultatPartie(partie, partie.getNomJoueur1(), (ResultatPartie)resultPlayer1);
                setResultatPartie(partie, partie.getNomJoueur2(), (ResultatPartie)resultPlayer2);
                cout << "Match results updated!" << endl;
            }
            break; 

        case 4: 
            // ... (Implement supprimerPartie using GestionParties)
            break;
        // ... other cases
    }
}

void displayChampionnatsMenu() {
  // Create the championnats menu
  vector<string> championnatsMenuOptions = {"Afficher la liste des championnats", "Rechercher un championnat", "Modifier un championnat", "Supprimer un championnat", "Retour au menu des parties"};
  Menu championnatsMenu(championnatsMenuOptions);

  // Display the championnats menu
  championnatsMenu.display();

  // Get the user's selection
  int selection = championnatsMenu.getSelection();

  // Handle the user's selection
  switch (selection) {
    case 1:
    void afficherChampionnats();
      break;
    case 2:
     void rechercherChampionnat();
      break;
    case 3:
     void modifierChampionnat();
      break;
    case 4:
     void supprimerChampionnat();
      break;
    case 5:
      // Retour au menu des parties
      displayPartiesMenu();
      break;
      // Inside your menu loop (modify the menu structure as needed)
case 5: // Update Scores
    // Get player names or match ID to identify the partie
    Partie partie = retrievePartie(nomJoueur1, nomJoueur2); // Using the function we created
    // Get match results
    GestionScores.updateScore(partie.getNomJoueur1(), calculateScore(partie));
    GestionScores.updateScore(partie.getNomJoueur2(), calculateScore(partie));
    cout << "Scores updated!" << endl;
    break;

case 6: // Display Top Scorers
    vector<Score> topScores = GestionScores.getTopScorers(3); // Get top 3
    for (Score score : topScores) {
        score.afficher();
    } 
    break;

    default:
      cout << "Choix invalide" << endl;
      break;
  }
}
void displayReservationsMenu() {
  // Create the reservations menu
  vector<string> reservationsMenuOptions = {"Afficher la liste des réservations", "Rechercher une réservation", "Modifier une réservation", "Supprimer une réservation", "Retour au menu principal"};
  Menu reservationsMenu(reservationsMenuOptions);

  // Display the reservations menu
  reservationsMenu.display();

  // Get the user's selection
  int selection = reservationsMenu.getSelection();

  // Handle the user's selection
  switch (selection) {
    case 1:
      // Afficher la liste des réservations
      break;
    case 2:
      // Rechercher une réservation
      break;
    case 3:
      // Modifier une réservation
      break;
    case 4:
      // Supprimer une réservation
      break;
    case 5:
      // Retour au menu principal
      break;
    default:
      cout << "Choix invalide" << endl;
      break;
  }
}
void displayMatchManagementMenu() {
    vector<string> matchMenuOptions = { 
        "Update Scores", 
        "Display Match Details", 
        // ... more match options ...
        "Return to Main Menu" 
    };
    Menu matchMenu(matchMenuOptions);
    // ... (Handle menu display and input similar to your main menu loop)
}
void displayScoreManagementMenu() {
    // Create the score management menu
  vector<string> scoreMenuOptions = {"Afficher la liste des scores", "Rechercher un score", "Modifier un score", "Supprimer un score", "Retour au menu principal"};
  Menu scoreMenu(scoreMenuOptions);

  // Display the score management menu
  scoreMenu.display();

  // Get the user's selection
  int selection = scoreMenu.getSelection();

  // Handle the user's selection
  switch (selection) {
    case 1:
      // Afficher la liste des scores des scores
      break;
    case 2:
      // Rechercher un score
      break;
    case 3:
      // Modifier un score
      break;
    case 4:
      // Supprimer un score score
      break;
    case 5:
      // Retour au menu principal
      break;
    default:
      cout << "Choix invalide" << endl;
      break;
  }
};
int main() {
  // Create the main menu
  vector<string> mainMenuOptions = {"Gestion des joueurs", "Gestion des terrains", "Gestion des parties", "Gestion des réservations", "Gestion des matches",
    "Gestion des scores","Quitter"};
  Menu mainMenu(mainMenuOptions);

  // Main loop
  int selection;
  do {
    // Display the main menu
    mainMenu.display();

    // Get the user's selection
    selection = mainMenu.getSelection();

    // Handle the user's selection
    switch (selection) {
      case 1:
        // Display the joueurs menu
        displayJoueursMenu();
        break;
      case 2:
        // Display the terrains menu
        displayTerrainsMenu();
        break;
      case 3:
        // Display the parties menu
        displayPartiesMenu();
        break;
      case 4:
        // Display the reservations menu
        displayReservationsMenu();
        break;
    
      case 5:
        // Display the matches menu
        displayMatchesMenu();
        break;
      case 6:
        // Display the scores menu
        displayScoresMenu();
        break;
      case 7:
      exit (0); // Quitter le programme
        break;
      default:
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 7);

  return 0;
}
