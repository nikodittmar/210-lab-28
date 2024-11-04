// COMSC 210 | Lab 28 | Niko Dittmar
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <numeric>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();


void sort_goats(list<Goat> &trip);
void goat_exists(list<Goat> &trip);
void total_age(list<Goat> &trip);
void remove_old_goats(list<Goat> &trip);
void remove_young_goats(list<Goat> &trip);
void increment_year(list<Goat> &trip);
void decrement_year(list<Goat> &trip);
void reverse_order(list<Goat> &trip);

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 5:
                cout << "Sorting goats" << endl;
                sort_goats(trip);
                break;
            case 6:
                cout << "Check if a goat exists." << endl;
                goat_exists(trip);
                break;
            case 7:
                cout << "Getting cumulative age of all goats." << endl;
                total_age(trip);
                break;
            case 8:
                cout << "Removing all goats above a certain age." << endl;
                remove_old_goats(trip);
                break;
            case 9:
                cout << "Removing all goats under a certain age." << endl;
                remove_young_goats(trip);
                break;
            case 10:
                cout << "Incrementing all goats ages by one year." << endl;
                increment_year(trip);
                break;
            case 11:
                cout << "Decrementing all goats ages by one year." << endl;
                decrement_year(trip);
                break;
            case 12:
                cout << "Reversing the order of the goats." << endl;
                reverse_order(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "[5] Sort" << endl;
    cout << "[6] Check if goat exists" << endl;
    cout << "[7] Find total age" << endl;
    cout << "[8] Remove old goats" << endl;
    cout << "[9] Remove young goats" << endl;
    cout << "[10] Increment year" << endl;
    cout << "[11] Decrement year" << endl;
    cout << "[12] Reverse order" << endl;
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

// sort_goats() sorts the list of goats.
// arguments the goat trip
// returns none
void sort_goats(list<Goat> &trip) {
    trip.sort();
}

// goat_exists() checks if a goat exists.
// arguments the goat trip
// returns none
void goat_exists(list<Goat> &trip) {
    string searchKey;
    cin >> searchKey;
    auto it = find_if(trip.begin(), trip.end(), [searchKey](const Goat& g){ return g.get_name() == searchKey; });
    if (it != trip.end()) {
        cout << searchKey << " is in the trip!";
    } else {
        cout << searchKey << " is not in the trip!";
    }
}

// total_age() gets the cumulative age of the goats.
// arguments the goat trip
// returns none
void total_age(list<Goat> &trip) {
    int totalAge = std::accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& g){ return sum + g.get_age(); });
    cout << "The total age of the goats is " << totalAge << " years.";
}

// remove_old_goats() removes goats above a certain age.
// arguments the goat trip
// returns none
void remove_old_goats(list<Goat> &trip) {
    int max_age;
    cin >> max_age;
    trip.erase(remove_if(trip.begin(), trip.end(), [max_age](const Goat& g){ return g.get_age() > max_age; }), trip.end());
}

// remove_young_goats() removes goats below a certain age.
// arguments the goat trip
// returns none
void remove_young_goats(list<Goat> &trip) {
    int min_age;
    cin >> min_age;
    trip.erase(remove_if(trip.begin(), trip.end(), [min_age](const Goat& g){ return g.get_age() < min_age; }), trip.end());
}

// increment_year() increments the age of all goats by one year.
// arguments the goat trip
// returns none
void increment_year(list<Goat> &trip) {
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat& g) { g.set_age(g.get_age() + 1); return g; });
}

// decrement_year() decrements the age of all goats by one year (min 0 years).
// arguments the goat trip
// returns none
void decrement_year(list<Goat> &trip) {
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat& g) { if (g.get_age() > 0) { g.set_age(g.get_age() - 1); } return g; });
}

// reverse_order() reverses the order of the goats in the trip.
// arguments the goat trip
// returns none
void reverse_order(list<Goat> &trip) {
    reverse(trip.begin(), trip.end());
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}