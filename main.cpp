#include <iostream>
#include <string>
#include <vector>
#include <limits> // For handling invalid input
#include "personne.h" 
#include "joueurs.h"
#include "championnats.h"
#include "parties.h"
#include "tickets.h"
#include "clients.h" 

using namespace std;

// Function to clear the console screen (implementation might vary depending on your OS)
void clearScreen() {
    // You might need to implement this based on your operating system 
    // (e.g., using system("cls") on Windows or system("clear") on Linux/macOS)
} 

// Function to display the main menu options
void displayMainMenu() {
    clearScreen(); // Clear the screen for a clean menu display
    cout << "Tennis Championship Application" << endl;
    cout << "------------------------------" << endl;
    cout << "1. Manage Players" << endl;
    cout << "2. Manage Championships" << endl; 
    cout << "3. Manage Matches" << endl;
    cout << "4. Manage Tickets" << endl;
    cout << "5. Manage Clients" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to get the user's menu choice with input validation
int getUserChoice() {
    int choice;
    while (!(cin >> choice) || choice < 0 || choice > 5) {
        cout << "Invalid input. Please enter a number between 0 and 5: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining input
    }
    return choice;
}

int main() {
    // Initialize necessary objects (e.g., GestionJoueurs, GestionChampionnats, etc.)
    GestionJoueurs gestionJoueurs;
    // ... (initialize other management objects as needed) 

    int choice;
    do {
        displayMainMenu();
        choice = getUserChoice();

        switch (choice) {
            case 1: 
                // Implement player management functionality here
                // (e.g., add, remove, search, display players)
                break; 
            case 2:
                // Implement championship management functionality
                break;
            case 3:
                // Implement match management functionality
                break;
            case 4:
                // Implement ticket management functionality 
                break;
            case 5:
                // Implement client management functionality
                break;
            case 0:
                cout << "Exiting the application. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0; 
}