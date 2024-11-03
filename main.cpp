// COMSC-210 | lab 24 | Kent Kawashima
// IDE used: Visual Studio Code
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set> // for std::set
#include <random>
#include <time.h> //for better randomization
#include "Goat.h"
using namespace std;

// global variables
const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

// function prototypes
int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string colors[], string names[]);
void display_trip(set<Goat> trip);
int main_menu();

/************************************************
 * Function: Main
 ************************************************/
int main()
{
    srand(time(0));

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

    // note: names/colors arrays now full of values
    set<Goat> trip; // set of goats is called a trip?

    // my code
    bool again = true;

    while (again)
    {
        int choice = main_menu();
        switch (choice)
        {
        case (1):
        {
            add_goat(trip, colors, names); // pass set of trips, colors[], names[]
            cout << "Added goat!\n";
            break;
        }
        case (2):
        {
            delete_goat(trip);
            break;
        }
        case (3):
        {
            display_trip(trip);
            break;
        }
        case (4): // break
        {
            again = false;
            break;
        }
            // NOTE: no default needed, as int choice validation is in main_menu() function
        }
    }

    return 0;
}

/************************************************
 * Function: prints out the details of the menu
 * for the menu-driven application
 *
 * Parameters: NONE
 * Return: int, value corresponding to user desires
 ************************************************/
int main_menu()
{
    int choice;
    cout << "\n*** GOAT MANAGER 3001 ***\n[1] Add a goat\n[2] Delete a goat\n[3] List goats\n[4] Quit\nChoice --> ";
    cin >> choice;

    while (choice > 4 || choice < 1) // validation loop
    {
        cout << "Invalid choice, please choose one (1-4): ";
        cin >> choice;
    }
    return (choice);
}

/************************************************
 * Function: prints out the details and index
 * of each goat in a set formatted nicely
 *
 * Parameters: trip, set of Goat objects
 * Return: NONE
 ************************************************/
void display_trip(set<Goat> trip) // displays all goats in the "trip"
{
    if (trip.empty())
    {
        cout << "Trip is empty\n"; // infinite loop
        return;
    }
    int i = 1; // keep track of iterations

    cout << "\n";                                             // formatting
    for (auto it = trip.begin(); it != trip.end(); ++it, ++i) // for each element in trip
    {
        cout << "[" << i << "] " << it->get_name() << "(" << it->get_age() << ", " << it->get_color() << ")\n"; // messy to read line, outputs something like: [5] Lena (12, Teal)
    }
}

/************************************************
 * Function: prompts and returns a specific goat object for
 * removal by the user, returning the input of user
 * if it is valid
 *
 * Parameters: trip, set of Goat objects
 * Return: int, value corresponding to user desired
 * goat to remove from the set
 ************************************************/
int select_goat(set<Goat> trip)
{
    int index = 0;

    if (trip.size() > 0)
    {
        display_trip(trip); // display set of all first

        cout << "What is the index of the Goat that you want to remove: ";
        cin >> index;

        while (index > trip.size() || index < 1) // logic may be faulty
        {
            cout << "Please enter a valid value from 1-" << trip.size() << "! ";
            cin >> index;
        }
    }
    else // case empty trip
        cout << "No valid goats, try adding some first!\n";

    return (index - 1);
}

/************************************************
 * Function: deletes a goat of specific index
 * specified by helper function select_goat()
 *
 * Parameters: trip, set of Goat objects
 * Return: NONE
 ************************************************/
void delete_goat(set<Goat> &trip)
{
    int posToDelete = select_goat(trip); // correct implementation of select?
    if (posToDelete == -1)
        return; // no valid target

    auto it = trip.begin();
    for (int i = 0; i < posToDelete; ++it, i++) // iterate "it" to correct location
    {
    }

    trip.erase(it);
}

/************************************************
 * Function: adds a new Goat object to the set
 * with a random name, age, and color, note that
 * the set automatically sorts it by order of
 * its first name, the way in which it sorts
 * could be modified by changing the overloaded
 * < operator. 
 *
 * Parameters:
 * trip, set of Goat objects
 * colors[], array of possible goat colors
 * names[], array of possible goat names
 * Return: NONE
 ************************************************/
void add_goat(set<Goat> &trip, string colors[], string names[])
{
    Goat temp;

    temp.set_name(names[rand() % SZ_NAMES + 1]);    // set temp's name to a random index of names[] array (1-200)
    temp.set_color(colors[rand() % SZ_COLORS + 1]); // set temp's color to a random index of colors[]] array (1-25)
    temp.set_age(rand() % (MAX_AGE + 1));           // set temp age to random num 0-20

    trip.insert(temp); // use insert (instead of push_x function) to add completed goat object to the set
}