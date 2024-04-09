#ifndef PARTIES_H
#define PARTIES_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum TypePartie {
  SIMPLE,
  DOUBLE
};

enum ResultatPartie {
  VICTOIRE,
  DEFAITE,
   MATCH_NUL,
};

class Joueur {
  public:
  Joueur(string nom, int classement) : nom(nom), classement(classement) {}
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
    TypePartie type;
    Joueur* joueur1;
    Joueur* joueur2;
    ResultatPartie resultat1;
    ResultatPartie resultat2;

    Partie(TypePartie type, Joueur* joueur1, Joueur* joueur2) {
      this->type = type;
      this->joueur1 = joueur1;
      this->joueur2 = joueur2;
      resultat1 =  MATCH_NUL;
      resultat2 =  MATCH_NUL;
    }

    void afficher() {
      cout << "Type: " << (type == SIMPLE ? "Simple" : "Double") << endl;
      cout << "Joueur 1: ";
      joueur1->afficher();
      cout << "Joueur 2: ";
      joueur2->afficher();
      cout << "Résultat 1: " << (resultat1 == VICTOIRE ? "Victoire" : "Défaite") << endl;
      cout << "Résultat 2: " << (resultat2 == VICTOIRE ? "Victoire" : "Défaite") << endl;
    }

    void setResultat(Joueur* joueur, int resultatAsInt) {
        ResultatPartie actualResultat;
        switch (resultatAsInt) {
        case 0:
            actualResultat =  MATCH_NUL; 
            break;
        case 1: 
            actualResultat = VICTOIRE;
            break;
        case 2:
            actualResultat = DEFAITE;
            break;
        default: 
            break; // Gestion d'erreur éventuelle ou résultat inchangé
        }

        if (joueur == joueur1) {
            resultat1 = actualResultat; 
        } else if (joueur == joueur2) {
            resultat2 = actualResultat; 
        }
    }

};

class GestionParties {
public:
    vector<Partie> parties;

    void ajouterPartie(Partie partie) {
        parties.push_back(partie);
    }

    void afficherParties() {
        for (Partie partie : parties) {
            partie.afficher();
            cout << endl;
        }
    }

    void supprimerPartie(TypePartie type, Joueur* joueur1, Joueur* joueur2) {
        for (int i = 0; i < parties.size(); i++) {
            if (parties[i].type == type &&
                parties[i].joueur1 == joueur1 &&
                parties[i].joueur2 == joueur2) {
                parties.erase(parties.begin() + i);
                break;
            }
        }
    }
};

#endif