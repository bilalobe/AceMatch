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
  Score(string nomJoueur, int score);

  void afficher() const;
};

class GestionScores {
public:
    std::map<std::string, int> scoresMap; 

    void ajouterScore(string nomJoueur, int score);
    void updateScore(string nomJoueur, int newScore);
    vector<Score> getTopScores(int count);
    void supprimerScore(string nomJoueur);
    void afficherScores();
};

#endif