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

// Add a score to the map
void GestionScores::ajouterScore(string nomJoueur, int score) {
  scoresMap[nomJoueur] = score;
}

// Update an existing score in the map
void GestionScores::updateScore(string nomJoueur, int newScore) {
  scoresMap[nomJoueur] = newScore;
}

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