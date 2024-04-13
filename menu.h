#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

using namespace std;

class Menu {
public:
  Menu(const vector<string>& options);

  void display();

  int getSelection();

private:
  vector<string> options;
};

void displayJoueursMenu(Menu& menu);

void displayTerrainsMenu(Menu& menu);

void displayPartiesMenu(Menu& menu);

void displayReservationsMenu(Menu& menu);

#endif
