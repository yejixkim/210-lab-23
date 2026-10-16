// COMSC 210 | Lab 23 | Yeji Kim

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(const list<Goat>& trip);
void delete_goat(list<Goat>& trip);
void add_goat(list<Goat>& trip, string names[],
              string colors[], int nameCount, int colorCount);
void display_trip(const list<Goat>& trip);
int main_menu();

int main() {
    srand(static_cast<unsigned int>(time(0)));

    string names[SZ_NAMES];
    string colors[SZ_COLORS];
    int nameCount = 0;
    int colorCount = 0;

    // read names
    ifstream fin("names.txt");

    if (!fin) {
        cout << "Error: Could not open names.txt.\n";
        return 1;
    }

    while (nameCount < SZ_NAMES && fin >> names[nameCount]) {
        nameCount++;
    }
    fin.close();

    // Read colors
    ifstream fin1("colors.txt");

    if (!fin1) {
        cout << "Error: Could not open colors.txt.\n";
        return 1;
    }

    while (colorCount < SZ_COLORS && fin1 >> colors[colorCount]) {
        colorCount++;
    }
    fin1.close();

    if (nameCount == 0 || colorCount == 0) {
        cout << "Error: Names or colors file is empty.\n";
        return 1;
    }

    list<Goat> trip;
    int choice;

    do {
        choice = main_menu();

        switch (choice) {
        case 1:
            add_goat(trip, names, colors, nameCount, colorCount);
            break;
        case 2:
            delete_goat(trip);
            break;
        case 3:
            display_trip(trip);
            break;
        case 4:
            cout << "\nThanks for using Goat Manager 3001!\n";
            break;
        }
    } while (choice != 4);

    return 0;
}

// display the menu and validate input
int main_menu() {
    int choice;

    while (true) {
        cout << "\n*** GOAT MANAGER 3001 ***\n";
        cout << "[1] Add a goat\n";
        cout << "[2] Delete a goat\n";
        cout << "[3] List goats\n";
        cout << "[4] Quit\n";
        cout << "Choice --> ";

        if (cin >> choice && choice >= 1 && choice <= 4) {
            return choice;
        }

        cout << "Invalid choice. Enter a number from 1 to 4.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// add a randomly generated goat
void add_goat(list<Goat>& trip, string names[],
              string colors[], int nameCount, int colorCount) {
    string name = names[rand() % nameCount];
    string color = colors[rand() % colorCount];
    int age = rand() % (MAX_AGE + 1);

    trip.push_back(Goat(name, age, color));

    cout << "\nAdded " << name << " to the trip!\n";
}

// display numbered goats and return the user's selection
int select_goat(const list<Goat>& trip) {
    if (trip.empty()) {
        cout << "\nThere are no goats in the trip.\n";
        return 0;
    }

    int number = 1;

    for (const Goat& goat : trip) {
        cout << "[" << number << "] "
             << goat.get_name() << " ("
             << goat.get_age() << ", "
             << goat.get_color() << ")\n";
        number++;
    }

    int choice;

    while (true) {
        cout << "Select a goat (0 to cancel): ";

        if (cin >> choice &&
            choice >= 0 &&
            choice <= static_cast<int>(trip.size())) {
            return choice;
        }

        cout << "Invalid selection. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}



