#include "Joueur.h"
#include "Partie.h"
#include "Reservation.h"
#include "Scoreboard.h"
#include "Paiements.h"
#include "DataManager.h"
#include "TournamentRanking.h"
#include "DataManager.h"

int main() {
    DataManager dataManager;
    TournamentRanking ranking;
    Paiements paiements;

    std::vector<Joueur> joueurs;
    std::vector<Partie> parties;
    std::vector<Reservation> reservations;
    Scoreboard scoreboard;

    // Load data
    dataManager.chargerJoueurs("joueurs.dat", joueurs);
    dataManager.chargerParties("parties.dat", parties);
    dataManager.chargerReservations("reservations.dat", reservations);
    dataManager.chargerScores("scores.dat", scoreboard);
    paiements.chargerPaiements("paiements.dat");

    // Example usage
    ranking.ajouterMatch("Joueur1", "Joueur2", 3, 1);
    ranking.afficherClassement();

    Paiement newPaiement("Client1", 50.0, "2024-05-19");
    paiements.ajouterPaiement(newPaiement);
    paiements.afficherPaiements();

    // Save data
    dataManager.sauvegarderJoueurs("joueurs.dat", joueurs);
    dataManager.sauvegarderParties("parties.dat", parties);
    dataManager.sauvegarderReservations("reservations.dat", reservations);
    dataManager.sauvegarderScores("scores.dat", scoreboard);
    paiements.sauvegarderPaiements("paiements.dat");

    return 0;
}
