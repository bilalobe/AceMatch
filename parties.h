#ifndef PARTIES_H
#define PARTIES_H

#include <string>
#include <vector>
#include <map>

enum TypePartie {
  SIMPLE,
  DOUBLE
};

enum ResultatPartie {
  MATCH_NUL,
  VICTOIRE,
  DEFAITE
};

class Partie {
public:
  Partie(TypePartie type, std::string nomJoueur1, std::string nomJoueur2);
  void afficher() const;
  int getNumero() const { return numero; } 
  string getNomJoueur1() const { return nomJoueur1; } 
  string getNomJoueur2() const { return nomJoueur2; }
  TypePartie getType() const { return type; }
  void setNumero(int numero) { this->numero = numero; }
  void setResultat(const std::string& nomJoueur, int resultatAsInt);
  ResultatPartie getResultat1() const;
  ResultatPartie getResultat2() const;
  std::string getNomJoueur1() const;
  std::string getNomJoueur2() const;
  void setNomJoueur1(std::string nomJoueur1);
  void setNomJoueur2(std::string nomJoueur2);

  // Declare the operator>> as a friend function of the Partie class
  friend std::istream& operator>>(std::istream& is, TypePartie& tp); 

private:
  TypePartie type;
  std::string nomJoueur1;
  std::string nomJoueur2;
  ResultatPartie resultat1;
  ResultatPartie resultat2;
  int numero;
  static int nextMatchNumber;
};

class GestionParties {
public:
  GestionParties();
  std::vector<Partie> getParties();
  std::vector<Partie> getPreviousRoundMatches();
  bool isPartieFromPreviousRound(Partie partie);
  int getPreviousRoundMaxMatchNumber() const;
  void setPreviousRoundMaxMatchNumber(int newMax);
  void setParties(std::vector<Partie> parties);
  void ajouterPartie(Partie partie);
  void afficherParties();
  void supprimerPartie(TypePartie type, std::string nomJoueur1, std::string nomJoueur2);
  Partie* rechercherPartie(const std::string& nomJoueur1, const std::string& nomJoueur2);
  Partie* rechercherPartie(const std::string& matchName);

private:
  std::vector<Partie> parties;
  std::map<std::pair<std::string, std::string>, Partie*> partiesMap;
  int previousRoundMaxMatchNumber;
};

#endif // PARTIES_H