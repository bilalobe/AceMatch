#include "TournamentScheduler.h"
#include <algorithm>
#include <random>
#include <QMessageBox> // For error messages

TournamentScheduler::TournamentScheduler(TennisChampionship *tennisChampionship)
    : tennisChampionship(tennisChampionship)
{
    // You can initialize the default match type here or get it from the user later
    matchType = SIMPLE;
}

void TournamentScheduler::createTournament(int nbRounds) { // renamed from createTournament
    // Get sorted players based on rankings
    std::vector<Player> players = tennisChampionship->playerManager.getPlayers(tennisChampionship->db);
    std::sort(joueurs.begin(), joueurs.end(), [](const Player &a, const Player &b) {
        return a.getClassement() > b.getClassement();
    });

    // Check for minimum number of players
    if (joueurs.size() < 2) {
        throw std::runtime_error("Not enough players to start a tournament.");
    }

    // Create the Round of 16 matches
    createRoundOf16(); // renamed from createRoundOf16()

    // Create the rest of the rounds
    for (int round = 1; round < nbRounds; round++) {
        createRound(round);
    }

    // Create the final match
    createFinalMatch(); // renamed from createFinalMatch()
}

void TournamentScheduler::createRoundOf16() { // renamed from createRoundOf16
    std::vector<Player> players = tennisChampionship->playerManager.getPlayers(tennisChampionship->db);

    // Sort players based on rankings
    std::sort(joueurs.begin(), joueurs.end(), [](const Player &j1, const Player &j2) {
        return j1.getClassement() > j2.getClassement();
    });

    if (joueurs.size() < 16) {
        QMessageBox::warning(nullptr, "Error", "Not enough players for Round of 16.");
        return;
    }

    // Pair players based on rankings
    for (int i = 0; i < 8; ++i) {
        Game partie(matchType, players[i].getName(), joueurs[joueurs.size() - 1 - i].getName());
        tennisChampionship->gestionParties.addPartie(tennisChampionship->db, partie);
    }
}

void TournamentScheduler::createRound(int round) {
    std::vector<Player> winners = getWinnersFromPreviousRound();

    // Check if there are enough winners to create a round
    if (winners.size() < 2) {
        throw std::runtime_error("Not enough winners to create round " + QString::number(round).toStdString());
    }

    // Sort winners based on rankings (you might need to adjust this logic)
    std::sort(winners.begin(), winners.end(), [](const Player &j1, const Player &j2) {
        return j1.getClassement() > j2.getClassement();
    });

    // Create matches for the round
    for (int i = 0; i < winners.size(); i += 2) {
        Game partie(matchType, winners[i].getName(), winners[i + 1].getName());
        tennisChampionship->gestionParties.addPartie(tennisChampionship->db, partie);
    }
}

void TournamentScheduler::createFinalMatch() { // renamed from createFinalMatch
    std::vector<Player> winners = getWinnersFromPreviousRound();

    if (winners.size() != 2) {
        throw std::runtime_error("Unexpected number of winners for the final.");
    }

    Game partie(matchType, winners[0].getName(), winners[1].getName());
    tennisChampionship->gestionParties.addPartie(tennisChampionship->db, partie);
}

std::vector<Player> TournamentScheduler::getWinnersFromPreviousRound() {
    std::vector<Player> winners;
    std::vector<Game> previousRoundMatches = tennisChampionship->gestionParties.getPreviousRoundMatches(tennisChampionship->db);

    for (const Game& partie : previousRoundMatches) {
        if (partie.getResultat1() == VICTOIRE) {
            winners.push_back(Player(partie.getNameJoueur1()));
        } else if (partie.getResultat2() == VICTOIRE) {
            winners.push_back(Player(partie.getNameJoueur2()));
        } else {
            // Handle ties: Randomly choose a winner for simplicity.
            std::random_device rd;
            std::mt19937 g(rd());
            std::uniform_int_distribution<> distrib(0, 1);
            int winnerIndex = distrib(g);
            winners.push_back(winnerIndex == 0 ? Player(partie.getNameJoueur1()) : Player(partie.getNameJoueur2()));
        }
    }

    return winners;
}
