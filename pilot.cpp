#include "pilot.h"
#include <limits> // Add this line to include the limits header



// Helper functions (example) 
void displayMainMenu();
void displayJoueursMenu();
void displayTerrainsMenu();
void displayPartiesMenu();
void displayChampionnatsMenu();
void displayReservationsMenu();
void displayScoreManagementMenu();
void displayClientsMenu();
void displayTicketsMenu();

// Helper function for menu selection
int getUserChoice() {
  int choice;
  while (!(cin >> choice) || choice < 1 || choice > 9) {
    cout << "Invalid input. Please enter a number between 1 and 9: ";
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining input
  }
  return choice;
}

void TennisChampionship::scheduleMatches(int championshipIndex, int round) {
    if (championshipIndex >= 0 && championshipIndex < championnats.size() && round >= 1 && round <= championnats[championshipIndex]->numRounds) {
        Championnat* championnat = championnats[championshipIndex];
        championship->scheduleRound(round);
    }
}
// Operator >> for TypePartie
std::istream& operator>>(std::istream& is, TypePartie& tp) {
  int input;
  is >> input; 
  if (input == 0) {
    tp = SIMPLE;
  } else if (input == 1) {
    tp = DOUBLE;
  } else {
    is.setstate(ios_base::failbit); 
  }
  return is;
}

MatchSchedule TennisChampionship::createMatchSchedule(const ChampionnatSimple& championnat) {
  return MatchSchedule(championnat);
}

void TennisChampionship::scheduleMatch(const Match& match) {
  schedule.addMatch(match); 
}

MatchSchedule& TennisChampionship::getMatchSchedule() {
  return schedule;
}
TournamentRanking TennisChampionship::getTournamentRanking() {
  return rankings;
}

void TennisChampionship::updateTournamentRanking(const Match& match) {
  rankings.updateRanking(match);
}

void TennisChampionship::addChampionship(ChampionnatSimple championnat) {
  championnats.push_back(make_shared<ChampionnatSimple>(championnat));
}

void TennisChampionship::removeChampionship(int index) {
  if (index >= 0 && index < championnats.size()) {
    championnats.erase(championnats.begin() + index);
  }
}

vector<shared_ptr<ChampionnatSimple>> TennisChampionship::getChampionnats() const {
  return championnats;
}

void TennisChampionship::setChampionnats(vector<shared_ptr<ChampionnatSimple>> newChampionnats) {
  championnats = newChampionnats;
}

void TennisChampionship::addPlayer(const Joueur& joueur) {
  gestionJoueurs.ajouterJoueur(joueur);
}

void TennisChampionship::removePlayer(const string& nomJoueur) {
  gestionJoueurs.supprimerJoueur(nomJoueur);
}

void TennisChampionship::updatePlayer(const Joueur& joueur) {
  gestionJoueurs.modifierJoueur(joueur);
}

Joueur* TennisChampionship::findPlayer(const string& nomJoueur) {
  return gestionJoueurs.rechercherJoueur(nomJoueur);
}

vector<Joueur> TennisChampionship::getPlayers() const {
  return gestionJoueurs.getJoueurs();
}

void TennisChampionship::addTerrain(const Terrain& terrain) {
  gestionTerrains.ajouterTerrain(terrain);
}

void TennisChampionship::removeTerrain(const Terrain& terrain) {
  gestionTerrains.supprimerTerrain(terrain);
}

void TennisChampionship::updateTerrain(const Terrain& terrain) {
  gestionTerrains.modifierTerrain(terrain);
}

Terrain* TennisChampionship::findTerrain(const Terrain& terrain) {
  return gestionTerrains.rechercherTerrain(terrain);
}

vector<Terrain> TennisChampionship::getTerrains() const {
  return gestionTerrains.getTerrains();
}

void TennisChampionship::addPartie(const Partie& partie) {
  gestionParties.ajouterPartie(partie);
}




