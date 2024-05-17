#include <iostream>
#include "type_partie.hpp"

using namespace std;

int main() {
  TypePartie matchType;
  cout << "Enter match type (0 - Simple, 1 - Double): ";
  cin >> matchType;

  if (cin.good()) {
    cout << "Match type: " << (matchType == SIMPLE ? "Simple" : "Double") << endl;
  } else {
    cout << "Invalid input." << endl;
  }

  return 0;
}