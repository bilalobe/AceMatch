#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <vector>

using namespace std;

class ScoreBoard
{
public:
    vector<Score *> scores;

    void addScore(Score *score)
    {
        scores.push_back(score);
    }

    Score *getScore(int matchIndex)
    {
        if (matchIndex >= 0 && matchIndex < scores.size())
        {
            return scores[matchIndex];
        }
        return nullptr;
    }

    void updateScore(int matchIndex, int scorePlayer1, int scorePlayer2)
    {
        if (matchIndex >= 0 && matchIndex < scores.size())
        {
            scores[matchIndex]->setScoreJoueur1(scorePlayer1);
            scores[matchIndex]->setScoreJoueur2(scorePlayer2);
        }
    }

    void displayScores() const
    {
        for (int i = 0; i < scores.size(); i++)
        {
            cout << "Match " << i + 1 << ": ";
            scores[i]->afficher();
            cout << endl;
        }
    }
};

#endif