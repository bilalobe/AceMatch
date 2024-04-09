#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <map>
#include "terrains.h"

using namespace std;

class Place {
  public:
    virtual ~Place() {delete[] data; }// Libération de la mémoire allouée dynamiquement}
    virtual string getType() const = 0;
    virtual double getPrix() const = 0;

  protected:
    int numeroPlace;
    char* data;

  public:
    Place(int numeroPlace) {
      this->numeroPlace = numeroPlace;
    }

    int getNumeroPlace() const { return numeroPlace; }
    virtual int choisirNumeroPlace(vector<int> placesDisponibles) const = 0;
};

class StandardPlace : public Place {
 public:
      StandardPlace(int numeroPlace) : Place(numeroPlace) {}
     string getType() const override { return "Standard"; }
     double getPrix() const override { return 50.0; } 

     int choisirNumeroPlace(vector<int> placesDisponibles) const override {
         return placesDisponibles.front(); // Premier numéro disponible
     }
};

class VipPlace : public Place {
 public:
      VipPlace(int numeroPlace) : Place(numeroPlace) {}
     string getType() const override { return "VIP"; }
     double getPrix() const override { return 100.0; } 

     int choisirNumeroPlace(vector<int> placesDisponibles) const override {
         if (placesDisponibles.empty()) return -1; // Aucune place dispo

         
     }
};


class Joueur {
  public:
    string nom;
    int classement;

    Joueur(string nom, int classement) {
      this->nom = nom;
      this->classement = classement;
    }

    void afficher() {
      cout << "Nom: " << nom << endl;
      cout << "Classement: " << classement << endl;
    }
};


class Partie {
  public:
  Partie(time_t dateHeureDebut, time_t dateHeureFin, Terrain* terrain) 
        : dateHeureDebut(dateHeureDebut), dateHeureFin(dateHeureFin), terrain(terrain) {}
    time_t dateHeureDebut= time(0);
    time_t dateHeureFin;
    Terrain* terrain;

    Partie(time_t dateHeureDebut, time_t dateHeureFin, Terrain* terrain) {
      this->dateHeureDebut = dateHeureDebut;
      this->dateHeureFin = dateHeureFin;
      this->terrain = terrain;
    }

    void afficher() {
      cout << "Date et heure de début: " << ctime(&dateHeureDebut);
      cout << "Date et heure de fin: " << ctime(&dateHeureFin);
      cout << "terrain: ";
      terrain->afficher();
    }
};

class Reservation {
    public:
    
    Reservation(Joueur* joueur, Partie* partie, Place* place) : 
                joueur(joueur), partie(partie), place(place) {}
                
    Joueur* getJoueur() const { return joueur; }
    Partie* getPartie() const { return partie; }
    Place* getPlace() const { return place; }


    Joueur* joueur;
    Partie* partie;
    Place* place;

        bool operator==(const Reservation& other) const {
            return joueur == other.joueur && 
                   partie == other.partie &&
                   place == other.place;
        }
};

class GestionReservations {
public:
    vector<Reservation> reservations;
    map<Partie*, map<string, int>> placesDisponibles; // Utilisation de 'string' pour le type Place //conteneur STL

public:

    void GestionReservations::ajouterReservation(Reservation& reservation) {
  reservations.push_back(reservation);
  placesDisponibles[reservation.partie][reservation.place->getType()]--;
}


    bool verifierDisponibilite(Partie* partie, string typePlace, int nombrePlaces) {    // Vérifier si la capacité du terrain est suffisante
    if (nombrePlaces > partie->terrain->capacite) {
        return false;
    }

    // Vérifier le nombre de places déjà réservées
    for (Reservation reservation : reservations) {
        if (reservation.partie == partie && reservation.place->getType() == typePlace) {
        nombrePlaces--;
        }
    }
    return true;;
    }

    double calculerPrix(Partie* partie, string typePlace, int nombrePlaces, const Place& place) { // Passez la place en référence constante
    return place.getPrix() * nombrePlaces;
    }
        double calculerPrixTotal(Reservation reservation) {
        return reservation.place->getPrix(); 
    }

    bool verifierDisponibilite(Partie* partie, string typePlace, int nombrePlaces) {
        // Vérifier si la capacité du terrain est suffisante
        if (nombrePlaces > placesDisponibles[partie][typePlace]) {
            return false;
        }
        // Vérifier le nombre de places déjà réservées
        for (Reservation reservation : reservations) {
            if (reservation.partie == partie && reservation.place->getType() == typePlace) {
              nombrePlaces--;
            }
        }

        return nombrePlaces >= 0;
    }
    bool effectuerPaiement(Reservation reservation, Paiement paiement) {
        // Simuler la transaction de paiement
        cout << "Paiement effectué pour " << reservation.joueur->nom << " pour " << reservation.partie->dateHeureDebut << endl;
        return true;
    }
    bool annulerReservation(Reservation reservation) {
        // Rechercher la réservation et la supprimer
        for (int i = 0; i < reservations.size(); i++) {
            if (reservations[i] == reservation) {
              reservations.erase(reservations.begin() + i);
              placesDisponibles[reservation.partie][reservation.place->getType()]++;
              return true;
            }
        }

        return false;
    }
};

class Paiement {
  public:
    enum MethodePaiement {
        CARTE_BANCAIRE,
        ESPECES,
        CHEQUE
      };

    MethodePaiement methode;
    double montant;

    Paiement(MethodePaiement methode, double montant) {
        this->methode = methode;
        this->montant = montant;
    }
};
#endif