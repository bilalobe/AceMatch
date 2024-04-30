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

    void ajouterScore(string nomJoueur, int score) {
        scoresMap[nomJoueur] = score; 
    }

    void updateScore(string nomJoueur, int newScore) {
        scoresMap[nomJoueur] = newScore; 
    }

    vector<Score> getTopScores(int count) {
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

    void supprimerScore(string nomJoueur) {
        auto it = scoresMap.find(nomJoueur);
        if (it != scoresMap.end()) {
            scoresMap.erase(it);
        }
    }

    void afficherScores() {
        for (const auto& pair : scoresMap) {
            cout << "Nom: " << pair.first << endl;
            cout << "Score: " << pair.second << endl;
        }
    }
};



#endif