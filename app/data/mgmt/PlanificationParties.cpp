#include "PlanificationParties.h"
#include <algorithm>
#include <random>
#include <QMessageBox> // For error messages

PlanificationParties::PlanificationParties(TennisChampionship *tennisChampionship)
    : tennisChampionship(tennisChampionship)
{
    // You can initialize the default match type here or get it from the user later
    matchType = SIMPLE;
}

void PlanificationParties::creerTournoi(int nbRounds) {
    // Get sorted players based on rankings
    std::vector<Joueur> joueurs = tennisChampionship->gestionJoueurs.getJoueurs(tennisChampionship->db);
    std::sort(joueurs.begin(), joueurs.end(), [](const Joueur &a, const Joueur &b) {
        return a.getClassement() > b.getClassement();
    });

    // Check for minimum number of players
    if (joueurs.size() < 2) {
        throw std::runtime_error("Not enough players to start a tournament.");
    }

    // Create the Round of 16 matches
    creerParties16emes();

    // Create the rest of the rounds
    for (int round = 1; round < nbRounds; round++) {
        creerRound(round);
    }

    // Create the final match
    creerPartieFinale();
}

void PlanificationParties::creerParties16emes() {
    std::vector<Joueur> joueurs = tennisChampionship->gestionJoueurs.getJoueurs(tennisChampionship->db);

    // Sort players based on rankings
    std::sort(joueurs.begin(), joueurs.end(), [](const Joueur &j1, const Joueur &j2) {
        return j1.getClassement() > j2.getClassement();
    });

    if (joueurs.size() < 16) {
        QMessageBox::warning(nullptr, "Error", "Not enough players for Round of 16.");
        return;
    }

    // Pair players based on rankings
    for (int i = 0; i < 8; ++i) {
        Partie partie(matchType, joueurs[i].getNom(), joueurs[joueurs.size() - 1 - i].getNom());
        tennisChampionship->gestionParties.ajouterPartie(tennisChampionship->db, partie);
    }
}

void PlanificationParties::creerRound(int round) {
    std::vector<Joueur> winners = getWinnersFromPreviousRound();

    // Check if there are enough winners to create a round
    if (winners.size() < 2) {
        throw std::runtime_error("Not enough winners to create round " + QString::number(round).toStdString());
    }

    // Sort winners based on rankings (you might need to adjust this logic)
    std::sort(winners.begin(), winners.end(), [](const Joueur &j1, const Joueur &j2) {
        return j1.getClassement() > j2.getClassement();
    });

    // Create matches for the round
    for (int i = 0; i < winners.size(); i += 2) {
        Partie partie(matchType, winners[i].getNom(), winners[i + 1].getNom());
        tennisChampionship->gestionParties.ajouterPartie(tennisChampionship->db, partie);
    }
}

void PlanificationParties::creerPartieFinale() {
    std::vector<Joueur> winners = getWinnersFromPreviousRound();

    if (winners.size() != 2) {
        throw std::runtime_error("Unexpected number of winners for the final.");
    }

    Partie partie(matchType, winners[0].getNom(), winners[1].getNom());
    tennisChampionship->gestionParties.ajouterPartie(tennisChampionship->db, partie);
}

std::vector<Joueur> PlanificationParties::getWinnersFromPreviousRound() {
    std::vector<Joueur> winners;
    std::vector<Partie> previousRoundMatches = tennisChampionship->gestionParties.getPreviousRoundMatches(tennisChampionship->db);

    for (const Partie& partie : previousRoundMatches) {
        if (partie.getResultat1() == VICTOIRE) {
            winners.push_back(Joueur(partie.getNomJoueur1()));
        } else if (partie.getResultat2() == VICTOIRE) {
            winners.push_back(Joueur(partie.getNomJoueur2()));
        } else {
            // Handle ties: Here, we randomly choose a winner for simplicity.
            // You can adjust this based on your tournament rules.
            std::random_device rd;
            std::mt19937 g(rd());
            std::uniform_int_distribution<> distrib(0, 1);
            int winnerIndex = distrib(g);
            winners.push_back(winnerIndex == 0 ? Joueur(partie.getNomJoueur1()) : Joueur(partie.getNomJoueur2()));
        }
    }

    return winners;
}
