#include "scores.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <map>
#include "joueurs.h"
#include "championnats.h"

using namespace std;

// Constructor for Score
Score::Score(string nomJoueur, int score) : nomJoueur(nomJoueur), score(score) {}

// Display a score's details
void Score::afficher() const {
  cout << "Nom: " << nomJoueur << endl;
  cout << "Score: " << score << endl;
}

// GestionScores implementation
GestionScores::GestionScores() {}



// Get the top scores (sorted by score)
vector<Score> GestionScores::getTopScores(int count) {
  vector<Score> topScores;
  for (const auto& pair : scoresMap) {
    topScores.emplace_back(pair.first, pair.second);
  }
  std::sort(topScores.begin(), topScores.end(),
            [](const Score& score1, const Score& score2) {
              return score1.score > score2.score;
            });
  if (count < topScores.size()) {
    topScores.resize(count);
  }
  return topScores;
}

// Remove a score from the map
void GestionScores::supprimerScore(string nomJoueur) {
  auto it = scoresMap.find(nomJoueur);
  if (it != scoresMap.end()) {
    scoresMap.erase(it);
  }
}

// Display all scores
void GestionScores::afficherScores() {
  for (const auto& pair : scoresMap) {
    cout << "Nom: " << pair.first << endl;
    cout << "Score: " << pair.second << endl;
  }
}

void GestionScores::updateScoreMatchWin(string nomJoueur) {
  if (scoresMap.find(nomJoueur) != scoresMap.end()) { // Check if the player exists
    scoresMap[nomJoueur] += 3; // Add 3 points for a win
  } else {
    scoresMap[nomJoueur] = 3;  // Initialize the player's score if they are new
  }
}

// Update a player's score for a match loss
void GestionScores::updateScoreMatchLoss(string nomJoueur) {
  if (scoresMap.find(nomJoueur) != scoresMap.end()) { // Check if the player exists
    scoresMap[nomJoueur] += 1; // Add 1 point for a loss
  } else {
    scoresMap[nomJoueur] = 1;  // Initialize the player's score if they are new
  }
}

void GestionScores::updateScoreForPlayer(string nomJoueur, int newScore) {
    scoresMap[nomJoueur] = newScore;
}