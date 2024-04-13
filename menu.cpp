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



using namespace std;


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
  vector<string> partiesMenuOptions = {"Afficher la liste des parties", "Rechercher une partie", "Modifier une partie", "Supprimer une partie", "Gestion des championnats", "Retour au menu principal"};
  Menu partiesMenu(partiesMenuOptions);

  // Display the parties menu
  partiesMenu.display();

  // Get the user's selection
  int selection = partiesMenu.getSelection();

  // Handle the user's selection
  switch (selection) {
    case 1:
      // Afficher la liste des parties
      break;
    case 2:
      // Rechercher une partie
      break;
    case 3:
      // Modifier une partie
      break;
    case 4:
      // Supprimer une partie
      break;
    case 5:
      // Gestion des championnats
      displayChampionnatsMenu();
      break;
    case 6:
      // Retour au menu principal
      break;
    default:
      cout << "Choix invalide" << endl;
      break;
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
      // Afficher la liste des championnats
      break;
    case 2:
      // Rechercher un championnat
      break;
    case 3:
      // Modifier un championnat
      break;
    case 4:
      // Supprimer un championnat
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
    gestionScores.updateScore(partie.getNomJoueur1(), calculateScore(partie));
    gestionScores.updateScore(partie.getNomJoueur2(), calculateScore(partie));
    cout << "Scores updated!" << endl;
    break;

case 6: // Display Top Scorers
    vector<Score> topScores = gestionScores.getTopScorers(3); // Get top 3
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

int main() {
  // Create the main menu
  vector<string> mainMenuOptions = {"Gestion des joueurs", "Gestion des terrains", "Gestion des parties", "Gestion des réservations", "Quitter"};
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
        // Quitter le programme
        break;
      default:
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 5);

  return 0;
}
