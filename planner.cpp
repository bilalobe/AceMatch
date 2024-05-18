#include "parties.h"
#include "championnats.h"
#include "joueurs.h"
#include "tennis_championnat.h"
#include <random>
// PlanificationParties implementation
class PlanificationParties
{
private:
    TennisChampionship *tennisChampionship;

public:
    // Constructor (take TennisChampionship as an argument)
    PlanificationParties(TennisChampionship *tennisChampionship) : tennisChampionship(tennisChampionship) {}
    PlanificationParties::PlanificationParties(TennisChampionship *tennisChampionship)
        : tennisChampionship(tennisChampionship) {}
    vector<Joueur> getWinnersFromPreviousRound()
    {
        vector<Joueur> winners;

        // Retrieve the list of played matches from the previous round
        vector<Partie> previousRoundMatches = tennisChampionship->gestionParties.getPreviousRoundMatches();

        // Iterate through matches and identify winners
        for (Partie partie : previousRoundMatches)
        {
            if (partie.getResultat1() == VICTOIRE)
            {
                winners.push_back(Joueur(partie.getNomJoueur1()));
            }
            else if (partie.getResultat2() == VICTOIRE)
            {
                winners.push_back(Joueur(partie.getNomJoueur2()));
            }
            else
            {
                // Handle draws (optional, logic not provided)
                // You can throw an exception or implement logic to handle draws here
                // For example, if you want both players to advance:
                winners.push_back(Joueur(partie.getNomJoueur1()));
                winners.push_back(Joueur(partie.getNomJoueur2()));
            }
        }
        return winners;
    }

    void creerPartiesEliminatoires()
    {
        // Retrieve the list of enrolled players from the championnat object
        vector<Joueur> joueursInscrits = tennisChampionship->championnat.getJoueursInscrits();

        // Create a new match for each pair of players
        for (int i = 0; i < joueursInscrits.size(); i++)
        {
            for (int j = i + 1; j < joueursInscrits.size(); j++)
            {
                TypePartie type = getMatchTypeFromUser();
                Partie partie(type, joueursInscrits[i].getNom(), joueursInscrits[j].getNom());
                tennisChampionship->gestionParties.ajouterPartie(partie);
            }
        }
    }

    void attribuerJoueursParties()
    {
        // Retrieve the list of matches from the gestionParties object
        vector<Partie> matches = tennisChampionship->gestionParties.getParties();

        // Retrieve the list of enrolled players from the championnat object
        vector<Joueur> joueursInscrits = tennisChampionship->championnat.getJoueursInscrits();

        // Randomly assign players to matches
        for (Partie &partie : matches)
        {
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(joueursInscrits.begin(), joueursInscrits.end(), g);
            // Assign the first two players to the match
            partie.setNomJoueur1(joueursInscrits[0].getNom());
            partie.setNomJoueur2(joueursInscrits[1].getNom());
        }
    }

    void PlanificationParties::creerParties16emes()
    {
        // Get sorted players based on rankings (assuming you have a ranking system)
        std::vector<Joueur> joueurs = tennisChampionship->gestionJoueurs.getJoueurs(); // Get players from TennisChampionship
        std::sort(joueurs.begin(), joueurs.end(), [](const Joueur &a, const Joueur &b)
                  {
                      return a.getClassement() > b.getClassement(); // Sort by descending ranking
                  });

        // Pair players based on rankings
        for (int i = 0; i < joueurs.size() / 2; ++i)
        {
            TypePartie type = getMatchTypeFromUser();
            Partie partie(type, joueurs[i].getNom(), joueurs[joueurs.size() - 1 - i].getNom());
            tennisChampionship->gestionParties.ajouterPartie(partie);
        }
    }

    // ... (other methods of the PlanificationParties class) ...

    TypePartie getMatchTypeFromUser()
    {
        int input;
        cout << "Enter match type (0 - Simple, 1 - Double): ";
        cin >> input;

        if (input == 0)
        {
            return SIMPLE;
        }
        else if (input == 1)
        {
            return DOUBLE;
        }
        else
        {
            cout << "Invalid input. Please enter 0 for Simple or 1 for Double: ";
            return getMatchTypeFromUser();
        }
    }

    void creerPartiesHuitiemesDeFinale()
    {
        std::vector<Joueur> vainqueurs = getWinnersFromPreviousRound();

        // Sort winners based on rankings
        std::sort(vainqueurs.begin(), vainqueurs.end(), [](const Joueur &j1, const Joueur &j2)
                  { return j1.getClassement() > j2.getClassement(); });

        // Pair and create matches
        for (int i = 0; i < vainqueurs.size(); i += 2)
        {
            TypePartie type = getMatchTypeFromUser();
            Partie partie(type, vainqueurs[i].getNom(), vainqueurs[i + 1].getNom());
            tennisChampionship->gestionParties.ajouterPartie(partie);
        }
    }

    void creerPartiesQuartsDeFinale()
    {
        std::vector<Joueur> vainqueurs = getWinnersFromPreviousRound();

        std::sort(vainqueurs.begin(), vainqueurs.end(), [](const Joueur &j1, const Joueur &j2)
                  { return j1.getClassement() > j2.getClassement(); });

        // Pair and create matches (Handling both winners advancing)
        for (int i = 0; i < vainqueurs.size(); i += 2)
        {
            TypePartie type = getMatchTypeFromUser();
            Partie partie(type, vainqueurs[i].getNom(), vainqueurs[i + 1].getNom());
            tennisChampionship->gestionParties.ajouterPartie(partie);
        }
    }

    void creerPartiesDemiFinales()
    {
        std::vector<Joueur> vainqueurs = getWinnersFromPreviousRound();

        std::sort(vainqueurs.begin(), vainqueurs.end(), [](const Joueur &j1, const Joueur &j2)
                  { return j1.getClassement() > j2.getClassement(); });

        // Pair and create matches (Handling both winners advancing)
        for (int i = 0; i < vainqueurs.size(); i += 2)
        {
            TypePartie type = getMatchTypeFromUser();
            Partie partie(type, vainqueurs[i].getNom(), vainqueurs[i + 1].getNom());
            tennisChampionship->gestionParties.ajouterPartie(partie);
        }
    }

    void creerPartieFinale()
    {
        std::vector<Joueur> vainqueurs = getWinnersFromPreviousRound();

        // Check if there are exactly two winners (assuming semifinals)
        if (vainqueurs.size() != 2)
        {
            throw runtime_error("Unexpected number of winners in semifinals.");
        }

        // Create a new match for the two winners
        TypePartie type = getMatchTypeFromUser();
        Partie partie(type, vainqueurs[0].getNom(), vainqueurs[1].getNom());
        tennisChampionship->gestionParties.ajouterPartie(partie);
    }

    TypePartie getMatchTypeFromUser()
    {
        int input;
        cout << "Enter match type (0 - Simple, 1 - Double): ";
        cin >> input;

        if (input == 0)
        {
            return SIMPLE;
        }
        else if (input == 1)
        {
            return DOUBLE;
        }
        else
        {
            cout << "Invalid input. Please enter 0 for Simple or 1 for Double: ";
            return getMatchTypeFromUser();
        }
    }
};