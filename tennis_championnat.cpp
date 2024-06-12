#include "tennis_championnat.h"
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

// ... Other helper functions you may need ... 

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