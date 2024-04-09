#ifndef GESTIONSCORES_H
#define GESTIONSCORES_H

#include <vector>
#include <random>
#include <algorithm> 
#include <iostream>

using namespace std;

enum Phase {
  ELIMINATOIRES,
  HUITIEMES_DE_FINALE,
  QUARTS_DE_FINALE,
  DEMI_FINALES,
  MATCH_TROISIEME_PLACE,
  FINALE
};

class Joueur {
public:
  string nom;
  int classement;
  int score;

public:
  Joueur(string nom, int classement) : nom(nom), classement(classement), score(0) {}

  void afficher() const {
    cout << "Nom: " << nom << endl;
    cout << "Classement: " << classement << endl;
    cout << "Score: " << score << endl;
  }

  void calculerClassement(const vector<Partie>& parties) {
    for (const Partie& partie : parties) {
      if (partie.joueurs[0] == this) {
        score += partie.phase;
      } else if (partie.joueurs[1] == this) {
        score += partie.phase;
      }
    }
    classement = score;
  }
};

class Partie {
public:
  vector<Joueur*> joueurs;
  Phase phase;

public:
  Partie(Phase phase, Joueur* joueur1, Joueur* joueur2) : phase(phase) {
    joueurs.push_back(joueur1);
    joueurs.push_back(joueur2);
  }

  void afficher() const {
    cout << "Phase: " << phase << endl;
    for (Joueur* joueur : joueurs) {
      joueur->afficher();
    }
  }
};

class Championnat {
public:
  vector<Joueur*> joueurs;
  vector<Partie> parties;

  void ajouterJoueur(const Joueur& joueur) {
    bool joueurExiste = false;
    for (Joueur* j : joueurs) {
      if (j->nom == joueur.nom) {
        joueurExiste = true;
        break;
      }
    }

    if (!joueurExiste) {
      joueurs.push_back(new Joueur(joueur));
      cout << "Joueur ajouté avec succès!" << endl;
    } else {
      cout << "Le joueur " << joueur.nom << " existe déjà." << endl;
    }
  }

  void selectionnerJoueurs(Phase phaseSuivante) {
    // Déterminer le classement minimum requis
    int classementMinimum = 100; // Exemple

    // Calculer le classement des joueurs
    for (Joueur* joueur : joueurs) {
      joueur->calculerClassement(parties);
    }

    // Afficher les joueurs sélectionnés
    cout << "Joueurs sélectionnés pour " << phaseSuivante << " :" << endl;
    for (Joueur* joueur : joueurs) {
      if (joueur->classement >= classementMinimum) {
        joueur->afficher();
      }
    }
  }

  void creerParties(Phase phase) {
    if (joueurs.size() % 2 != 0) {
      cout << "Nombre de joueurs impair. Gestion à implémenter." << endl;
      return;
    }

    vector<Joueur*> joueurs_temp(joueurs.begin(), joueurs.end()); // Crée une copie temporaire
    shuffle(joueurs_temp.begin(), joueurs_temp.end(), std::default_random_engine(random_device{}()));

    for (int i = 0; i < joueurs_temp.size() / 2; i++) {
      parties.push_back(Partie(phase, joueurs_temp[2 * i], joueurs_temp[2 * i + 1]));
    }
  }

  void afficherParties() {
    for (const Partie& partie : parties) {
      partie.afficher();
      cout << endl;
      for (Joueur* joueur : partie.joueurs) {
        joueur->afficher();
        cout << "Classement: " << joueur->classement << endl;
      }
    }
  }
};

#endif