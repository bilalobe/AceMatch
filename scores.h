#ifndef SCORES_H
#define SCORES_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for sort() function
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
    vector<pair<string, int>> scores; 

    void ajouterScore(string nomJoueur, int score) {
        scores.push_back(make_pair(nomJoueur, score));
    }

    void updateScore(string nomJoueur, int newScore) {
        for (auto &scorePair : scores) {
            if (scorePair.first == nomJoueur) {
                scorePair.second = newScore;
                return; 
            }
        }
    
vector<Score> getTopScorers(int count) {
    vector<Score> topScores(scores); // Make a copy of scores 
    std::sort(topScores.begin(), topScores.end(), 
        [](const Score& score1, const Score& score2) {
            return score1.score > score2.score; 
        });  // Sort in descending order of score

    if (count < topScores.size()) {
        topScores.resize(count); // Return only the top 'count' scores
    }

    return topScores;
}
void supprimerScore(string nomJoueur) {
    Score* score = findScore(nomJoueur);
    if (score != nullptr) {
        scores.erase(remove(scores.begin(), scores.end(), *score), scores.end());
    }
  }


private:
  Score* findScore(string nomJoueur) {
    for (Score& score : scores) {
        if (score.nomJoueur == nomJoueur) {
            return &score;
        }
    }
    return nullptr;
  }
};
};
#endif