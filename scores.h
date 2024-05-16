#ifndef SCORES_H
#define SCORES_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <map>
#include "joueurs.h"
#include "championnats.h"

using namespace std;

class Score {
public:
  string nomJoueur;
  int score;

public:
  Score(string nomJoueur, int score) : nomJoueur(nomJoueur), score(score) {}

  void afficher() const {
    cout << "Nom: " << nomJoueur << endl;
    cout << "Score: " << score << endl;
  }
};

class GestionScores {
public:
    std::map<std::string, int> scoresMap; 

    // Update a player's score for a match win
    void updateScoreMatchWin(string nomJoueur);

    // Update a player's score for a match loss
    void updateScoreMatchLoss(string nomJoueur);

    // Get the top scores (sorted by score)
    vector<Score> getTopScores(int count);

    // Remove a score from the map
    void supprimerScore(string nomJoueur);

    // Display all scores
    void afficherScores();

    // Update a score for a specific player
    void updateScoreForPlayer(string nomJoueur, int newScore);
};

#endif