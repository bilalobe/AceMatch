#include "Tennis.h"

void TennisChampionship::scheduleMatches(int championshipIndex, int round) {
    if (championshipIndex >= 0 && championshipIndex < championnats.size() && round >= 1 && round <= championnats[championshipIndex]->numRounds) {
        Championnat* championnat = championnats[championshipIndex];
        championship->scheduleRound(round);
    }
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




