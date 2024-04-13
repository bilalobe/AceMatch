#include <iostream>
#include <vector>
#include "joueurs.h"
#include "scores.h"
using namespace std;


class Menu {
public:
  Menu(const vector<string>& options) : options(options) {}

  void display() {
    for (int i = 0; i < options.size(); i++) {
      cout << i + 1 << ". " << options[i] << endl;
    }
    cout << "Your choice: ";
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
  vector<string> joueursMenuOptions = {"Afficher la liste des joueurs", "Rechercher un joueur", "Modifier un joueur", "Supprimer un joueur", "Retour au menu principal"};
  Menu joueursMenu(joueursMenuOptions);

  // Display the joueurs menu
  joueursMenu.display();

  // Get the user's selection
  int selection = joueursMenu.getSelection();

  // Handle the user's selection
  switch (selection) {
    case 1:
      afficherJoueurs();
      break;
    case 2:
      rechercherJoueur();
      break;
    case 3:
      modifierJoueur();
      break;
    case 4:
      supprimerJoueur();
      break;
    case 5:
      displayJoueursMenu();
      break;
    case 6:
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
      afficherTerrains();
      break;
    case 2:
      rechercherTerrain();
      break;
    case 3:
      modifierTerrain();
      break;
    case 4:
      supprimerTerrain();
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
  vector<string> partiesMenuOptions = {"Afficher la liste des parties", "Rechercher une partie", "Modifier une partie", "Supprimer une partie", "Retour au menu principal"};
  Menu partiesMenu(partiesMenuOptions);

  // Display the parties menu
  partiesMenu.display();

  // Get the user's selection
  int selection = partiesMenu.getSelection();

  // Handle the user's selection
  switch (selection) {
    case 1:
      afficherParties();
      break;
    case 2:
      rechercherPartie();
      break;
    case 3:
      modifierPartie();
      break;
    case 4:
      supprimerPartie();
      break;
    case 5:
      displayPartiesMenu();
      break;
    case 6:
      exit(0); // Quitter le programme
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
      afficherReservations();
      break;
    case 2:
      rechercherReservation();
      break;
    case 3:
      modifierReservation();
      break;
    case 4:
      supprimerReservation();
      break;
    case 5:
      displayReservationsMenu();
      break;
    case 6:
      exit(0); // Quitter le programme
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
