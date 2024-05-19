#ifndef TENNIS_EVENT_H
#define TENNIS_EVENT_H

#include <iostream>
#include <vector>

#include "Terrain.h"
#include "Client.h"
#include "GestionJoueurs.h"
#include "Ticket.h"
#include "Reservation.h"
#include "scoreboard.h"


using namespace std;

class TennisEvent {
public:
  string name;
  int year;
  vector<Terrain*> terrains;
  vector<Client*> clients;
  vector<Ticket*> tickets;
  vector<Reservation*> reservations;
  ScoreBoard* scoreBoard;
  GestionJoueurs* gestionJoueurs;

  TennisEvent(string name, int year) : name(name), year(year) {}

  void addTerrain(Terrain* terrain) {
    terrains.push_back(terrain);
  }

  void addClient(Client* client) {
    clients.push_back(client);
  }

  void addTicket(Ticket* ticket) {
    tickets.push_back(ticket);
  }

  void addReservation(Reservation* reservation) {
    reservations.push_back(reservation);
  }

  Terrain* getTerrain(int index) {
    if (index >= 0 && index < terrains.size()) {
      return terrains[index];
    }
    return nullptr;
  }

  Client* getClient(int index) {
    if (index >= 0 && index < clients.size()) {
      return clients[index];
    }
    return nullptr;
  }

  Ticket* getTicket(int index) {
    if (index >= 0 && index < tickets.size()) {
      return tickets[index];
    }
    return nullptr;
  }

  Reservation* getReservation(int index) {
    if (index >= 0 && index < reservations.size()) {
      return reservations[index];
    }
    return nullptr;
  }

  void displayTerrains() {
    cout << "Terrains in " << name << " (" << year << "):" << endl;
    for (int i = 0; i < terrains.size(); i++) {
      cout << i + 1 << ". ";
      terrains[i]->afficher();
    }
  }

  void displayClients() {
    cout << "Clients in " << name << " (" << year << "):" << endl;
    for (int i = 0; i < clients.size(); i++) {
      cout << i + 1 << ". ";
      clients[i]->afficher();
    }
  }

  void displayTickets() {
    cout << "Tickets in " << name << " (" << year << "):" << endl;
    for (int i = 0; i < tickets.size(); i++) {
      cout << i + 1 << ". ";
      tickets[i]->afficher();
    }
  }

  void displayReservations() {
    cout << "Reservations in " << name << " (" << year << "):" << endl;
    for (int i = 0; i < reservations.size(); i++) {
      cout << i + 1 << ". ";
      reservations[i]->afficher();
    }
  }

  void displayScores() {
    cout << "Scores in " << name << " (" << year << "):" << endl;
    scoreBoard->displayScores(); 
  }
  void displayJoueurs() {
    cout << "Joueurs in " << name << " (" << year << "):" << endl;
    gestionJoueurs->afficherJoueurs();
  }

  void addScore(Score* score) {
    scoreBoard->addScore(score);
  }

  void updateScore(int matchIndex, int scorePlayer1, int scorePlayer2) {
    scoreBoard->updateScore(matchIndex, scorePlayer1, scorePlayer2);
  }

  void displayMatches() {
    cout << "Matches in " << name << " (" << year << "):" << endl;
    for (int i = 0; i < scoreBoard->getScoreJoueur1().size(); i++) {
      cout << i + 1 << ". ";
      scoreBoard->getScore(i)->afficher();
    }
  }

  
};



#endif