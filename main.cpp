#include <iostream>
#include <vector>
#include "joueurs.h"
#include "terrains.h"
#include "parties.h"
#include "reservations.h"
#include "championnats.h"
#include "tickets.h"
#include "scores.h"

using namespace std;

// Global Management Objects 
GestionJoueurs gestionJoueurs;
GestionTerrains gestionTerrains;
GestionReservations gestionReservations;
GestionScores gestionScores; 
GestionParties gestionParties;
ChampionnatSimple championnat; 
PlanificationParties planificateur;

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
}

// Helper Function
void setResultatPartie(Partie& partie, const string& nomJoueur, ResultatPartie resultat) {
    if (nomJoueur == partie.getNomJoueur1()) {
        partie.setResultat(partie.getNomJoueur1(), (int)resultat); // Use setResultat
    } else if (nomJoueur == partie.getNomJoueur2()) {
        partie.setResultat(partie.getNomJoueur2(), (int)resultat); // Use setResultat
    }
}

// Helper Function (Example; Modify for your scoring system)
int calculateScore(const Partie& partie) {
  if (partie.getResultat1() == VICTOIRE) {
    return 3; // Points for a win
  } else if (partie.getResultat2() == VICTOIRE) {
    return 3;
  } else if (partie.getResultat1() == MATCH_NUL && partie.getResultat2() == MATCH_NUL) {
    return 1; // Points for a draw
  }
  return 0; // Points for a loss
}

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

// Menu Functions

void displayJoueursMenu() {
  vector<string> joueursMenuOptions = {
    "Afficher la liste des joueurs",
    "Rechercher un joueur",
    "Modifier un joueur",
    "Supprimer un joueur",
    "Trier les joueurs par classement",
    "Retour au menu principal"
  };
  Menu joueursMenu(joueursMenuOptions);

  int selection;
  do {
    joueursMenu.display();
    selection = joueursMenu.getSelection();

    switch (selection) {
      case 1:
        gestionJoueurs.afficherJoueurs();
        break;
      case 2:
        {
          string nom;
          cout << "Entrez le nom du joueur à rechercher: ";
          cin >> nom;
          gestionJoueurs.rechercherJoueur(nom);
        }
        break;
      case 3:
        {
          string nom;
          cout << "Entrez le nom du joueur à modifier: ";
          cin >> nom;
          Joueur* joueurToModify = gestionJoueurs.rechercherJoueur(nom);
          if (joueurToModify != nullptr) {
            // Implement modifierJoueur logic
            cout << "Enter new player name: ";
            cin >> joueurToModify->nom;

            cout << "Enter new player ranking: ";
            int newRanking;
            cin >> newRanking;
            joueurToModify->setClassement(newRanking);
            
            cout << "Player updated successfully." << endl;
          } else {
            cout << "Joueur non trouvé." << endl;
          }
        }
        break;
      case 4:
        {
          string nom;
          cout << "Entrez le nom du joueur à supprimer: ";
          cin >> nom;
          gestionJoueurs.supprimerJoueur(nom);
        }
        break;
      case 5:
        gestionJoueurs.trierJoueursParClassement();
        break;
      case 6:
        break; // Exit the Joueurs menu
      default:
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 6);
}

void displayTerrainsMenu() {
  vector<string> terrainsMenuOptions = {
    "Afficher la liste des terrains",
    "Rechercher un terrain",
    "Modifier un terrain",
    "Supprimer un terrain",
    "Retour au menu principal"
  };
  Menu terrainsMenu(terrainsMenuOptions);

  int selection;
  do {
    terrainsMenu.display();
    selection = terrainsMenu.getSelection();

    switch (selection) {
      case 1:
        gestionTerrains.afficherTerrains(); 
        break;
      case 2:
        // Implement rechercherTerrain() using gestionTerrains
        break;
      case 3:
        // Implement modifierTerrain() using gestionTerrains
        break;
      case 4:
        // Implement supprimerTerrain() using gestionTerrains
        break;
      case 5:
        break; // Exit the Terrains menu
      default:
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 5);
}

void displayPartiesMenu() {
    vector<string> partiesMenuOptions = { 
        "Afficher la liste des parties", 
        "Rechercher une partie", 
        "Saisir le résultat d'une partie", 
        "Supprimer une partie", 
        "Gestion des championnats", 
        "Retour au menu principal"};
    Menu partiesMenu(partiesMenuOptions);

    int selection;
    do {
        partiesMenu.display();
        selection = partiesMenu.getSelection();

        switch (selection) {
            case 1: 
                gestionParties.afficherParties();
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

                    Partie partie = retrievePartie(nomJoueur1, nomJoueur2); // Find the Partie

                    // Get match results
                    cout << "Enter result for Player 1 (0 - Match Nul, 1 - Victoire, 2 - Defaite): ";
                    int resultPlayer1; 
                    cin >> resultPlayer1; 

                    cout << "Enter result for Player 2 (0 - Match Nul, 1 - Victoire, 2 - Defaite): ";
                    int resultPlayer2; 
                    cin >> resultPlayer2;

                    setResultatPartie(partie, partie.getNomJoueur1(), (ResultatPartie)resultPlayer1);
                    setResultatPartie(partie, partie.getNomJoueur2(), (ResultatPartie)resultPlayer2);

                    // Update scores
                    gestionScores.updateScore(partie.getNomJoueur1(), calculateScore(partie));
                    gestionScores.updateScore(partie.getNomJoueur2(), calculateScore(partie));

                    cout << "Match results updated!" << endl;
                }
                break; 

            case 4: 
                // ... (Implement supprimerPartie using GestionParties)
                break;
            case 5:
              displayChampionnatsMenu();
              break;
            case 6:
              break; // Exit the Parties menu
            default:
                cout << "Choix invalide" << endl;
                break;
        }
    } while (selection != 6);
}

void displayChampionnatsMenu() {
  vector<string> championnatsMenuOptions = {
    "Afficher la liste des championnats",
    "Rechercher un championnat",
    "Modifier un championnat",
    "Supprimer un championnat",
    "Retour au menu des parties"
  };
  Menu championnatsMenu(championnatsMenuOptions);

  int selection;
  do {
    championnatsMenu.display();
    selection = championnatsMenu.getSelection();

    switch (selection) {
      case 1:
        // Implement afficherChampionnats() using your Championnat object
        break;
      case 2:
        // Implement rechercherChampionnat()
        break;
      case 3:
        // Implement modifierChampionnat()
        break;
      case 4:
        // Implement supprimerChampionnat()
        break;
      case 5:
        break; // Exit the championnats menu
      default:
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 5);
}

void displayReservationsMenu() {
  vector<string> reservationsMenuOptions = {
    "Afficher la liste des réservations",
    "Rechercher une réservation",
    "Modifier une réservation",
    "Supprimer une réservation",
    "Retour au menu principal"
  };
  Menu reservationsMenu(reservationsMenuOptions);

  int selection;
  do {
    reservationsMenu.display();
    selection = reservationsMenu.getSelection();

    switch (selection) {
      case 1:
        // Implement afficherReservations() using gestionReservations
        break;
      case 2:
        // Implement rechercherReservation() using gestionReservations
        break;
      case 3:
        // Implement modifierReservation() using gestionReservations
        break;
      case 4:
        // Implement supprimerReservation() using gestionReservations
        break;
      case 5:
        break; // Exit the reservations menu
      default:
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 5);
}

void displayMatchManagementMenu() {
  // ... (Implement your match management logic)
  vector<string> matchMenuOptions = {
        "Create Matches", 
        "Update Scores", 
        "Display Match Details", 
        // ... more match options ...
        "Return to Main Menu" 
    };
  Menu matchMenu(matchMenuOptions);
  int selection;
  do {
    matchMenu.display();
    selection = matchMenu.getSelection();

    switch (selection) {
      case 1:
        // Implement your match creation logic 
        // (e.g., using PlanificationParties or a custom function)
        break;
      case 2: 
        // Get player names or match ID to identify the partie
        // ... (Your logic for getting player names or match ID)
        // Get match results
        // ... (Get results)

        // Get the corresponding Partie 
        Partie partie = retrievePartie(nomJoueur1, nomJoueur2); 

        if (partie.getNomJoueur1() != "unknown" && partie.getNomJoueur2() != "unknown") { 
            gestionScores.updateScore(partie.getNomJoueur1(), calculateScore(partie));
            gestionScores.updateScore(partie.getNomJoueur2(), calculateScore(partie));
            cout << "Scores updated!" << endl;
        } else {
            cout << "Match not found. Could not update scores." << endl;
        }
        break;
      case 3:
        // Implement your logic to display match details
        // ...
        break;
        // ... other cases
      case 5: 
        break; // Exit the Match Management menu
      default: 
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 5); 
}
void displayScoreManagementMenu() {
  vector<string> scoreMenuOptions = {
    "Afficher la liste des scores",
    "Rechercher un score",
    "Modifier un score",
    "Supprimer un score",
    "Afficher les meilleurs scores",
    "Retour au menu principal"
  };
  Menu scoreMenu(scoreMenuOptions);

  int selection;
  do {
    scoreMenu.display();
    selection = scoreMenu.getSelection();

    switch (selection) {
      case 1:
        gestionScores.afficherScores();
        break;
      case 2:
        // Implement rechercherScore() using gestionScores
        break;
      case 3:
        // Implement modifierScore() using gestionScores
        break;
      case 4:
        // Implement supprimerScore() using gestionScores
        break;
      case 5: 
        {
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
        }
        break;
      case 6:
        break; // Exit the Scores menu
      default:
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 6);
}

int main() {
  // Initialize your data (Consider loading from a file)
  gestionJoueurs.ajouterJoueur(Joueur("Roger Federer", 40, 1));
  gestionJoueurs.ajouterJoueur(Joueur("Rafael Nadal", 36, 2));
  // ... (Add other players, terrains, matches, etc.)

  // Championship initialization (you can create a championship in the main function)
  championnat = ChampionnatSimple("Grand Slam", 2023, 4);
  // Add players to the championship
  championnat.ajouterJoueur(Joueur("Novak Djokovic", 35, 3));
  championnat.ajouterJoueur(Joueur("Carlos Alcaraz", 20, 4));
  // ... Add other players as needed

    planificateur.creerParties16emes(); // Create Round of 16 matches 
planificateur.creerPartiesHuitiemesDeFinale(); // Create Round of 8 matches
// ... 
  // Add some matches for testing
  // ... 

  // Main Menu
  vector<string> mainMenuOptions = {
    "Gestion des Joueurs",
    "Gestion des Terrains",
    "Gestion des Parties",
    "Gestion des Championnats",
    "Gestion des Réservations",
    "Gestion des Scores",
    "Quitter"
  };
  Menu mainMenu(mainMenuOptions);

  int selection;
  do {
    mainMenu.display();
    selection = mainMenu.getSelection();

    switch (selection) {
      case 1:
        displayJoueursMenu();
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
        cout << "Au revoir!" << endl;
        break;
      default:
        cout << "Choix invalide" << endl;
        break;
    }
  } while (selection != 7);

  return 0;
}