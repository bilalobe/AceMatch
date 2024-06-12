#include "partie.h"

// GestionParties implementation
GestionParties::GestionParties() {}

// Get the list of matches
vector<Partie> GestionParties::getParties() {
  return parties;
}

// Get the list of matches from the previous round
vector<Partie> GestionParties::getPreviousRoundMatches() {
  vector<Partie> previousRoundMatches;
  for (const Partie& partie : parties) {
    if (partie.getNumero() <= previousRoundMaxMatchNumber) {
      previousRoundMatches.push_back(partie);
    }
  }
  return previousRoundMatches;
}

// Check if a match is from the previous round
bool GestionParties::isPartieFromPreviousRound(Partie partie) {
  return partie.getNumero() <= previousRoundMaxMatchNumber;
}

// Get the maximum match number from the previous round
int GestionParties::getPreviousRoundMaxMatchNumber() const {
  return previousRoundMaxMatchNumber;
}

// Set the maximum match number from the previous round
void GestionParties::setPreviousRoundMaxMatchNumber(int newMax) {
  previousRoundMaxMatchNumber = newMax;
}

// Set the list of matches
void GestionParties::setParties(vector<Partie> parties) {
  this->parties = parties;
}

// Add a match
void GestionParties::ajouterPartie(Partie partie) {
  parties.push_back(partie);
  partiesMap[make_pair(partie.getNomJoueur1(), partie.getNomJoueur2())] = &partie;
  partiesMap[make_pair(partie.getNomJoueur2(), partie.getNomJoueur1())] = &partie;
}

// Display all matches
void GestionParties::afficherParties() {
  for (Partie partie : parties) {
    partie.afficher();
    cout << endl;
  }
}

void GestionParties::supprimerPartie(TypePartie type, string nomJoueur1, string nomJoueur2) {
  parties.erase(
    std::remove_if(parties.begin(), parties.end(),
      [type, nomJoueur1, nomJoueur2](const Partie& partie) {
        return partie.getType() == type && partie.getNomJoueur1() == nomJoueur1 && partie.getNomJoueur2() == nomJoueur2;
      }),
    parties.end()
  );
}


// Function to retrieve a Partie by player names
Partie* GestionParties::rechercherPartie(const string& nomJoueur1, const string& nomJoueur2) {
  auto it = partiesMap.find(make_pair(nomJoueur1, nomJoueur2));
  if (it != partiesMap.end()) {
    return it->second;
  }
  return nullptr;
}


void GestionParties::setMatchResult(int numero, const std::string& winnerName) {
    for (int i = 0; i < parties.size(); i++) {
        if (parties[i].getNumero() == numero) {
            if (parties[i].getNomJoueur1() == winnerName) {
                parties[i].setResultat(parties[i].getNomJoueur1(), 1);
                parties[i].setResultat(parties[i].getNomJoueur2(), 2);
            } else if (parties[i].getNomJoueur2() == winnerName) {
                parties[i].setResultat(parties[i].getNomJoueur2(), 1);
                parties[i].setResultat(parties[i].getNomJoueur1(), 2);
            }
            break;
        }
    }
}
