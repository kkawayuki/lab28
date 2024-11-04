// COMSC-210 | lab 28 | Kent Kawashima
// IDE used: Visual Studio Code
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list> // for std::list
#include <random>
#include <time.h>    //for better randomization
#include <algorithm> //for a lot of the new changes
#include "Goat.h"

#include <numeric> //needed?
using namespace std;

// global variables
const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

// function prototypes
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string colors[], string names[]);
void display_trip(list<Goat> trip);
int main_menu();

// algorithm prototypes
void average_ages(list<Goat> trip);
void clear_goats(list<Goat> &trip);
void merge_trip(list<Goat> &trip);
void print_ages(list<Goat> trip);
void copy_trip(list<Goat> trip);
void add_year(list<Goat> trip);
void shuffle_trip(list<Goat> trip);
void has_senior(list<Goat> trip);

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
    while (fin >> names[i++])
        ;
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++])
        ;
    fin1.close();

    // note: names/colors arrays now full of values
    list<Goat> trip; // list of goats is called a trip?

    // my code
    bool again = true;

    while (again)
    {
        int choice = main_menu();
        switch (choice)
        {
        case (1):
        {
            add_goat(trip, colors, names); // pass list of trips, colors[], names[]
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
        case (5):
        {
            average_ages(trip);
            break;
        }
        case (6):
        {
            clear_goats(trip);
            break;
        }
        case (7):
        {
            merge_trip(trip);
            break;
        }
        case (8):
        {
            print_ages(trip);
            break;
        }
        case (9):
        {
            copy_trip(trip);
            break;
        }
        case (10):
        {
            add_year(trip);
            break;
        }
        case (11):
        {
            shuffle_trip(trip);
            break;
        }
        case (12):
        {
            has_senior(trip);
            break;
        }
        }
    }

    return 0;
}

int main_menu()
{
    int choice;
    cout << "\n*** GOAT MANAGER 3001 ***\n"
         << "[1] Add a goat\n"
         << "[2] Delete a goat\n"
         << "[3] List goats\n"
         << "[4] Quit\n"
         << "[5] Average Ages\n"
         << "[6] Clear Set\n"
         << "[7] Merge trip\n"
         << "[8] Print All Ages\n"
         << "[9] Copy Trip\n"
         << "[10] Add +1 Year to All\n"
         << "[11] Shuffle Trip\n"
         << "[12] Check for Senior Goats\n"
         << "Choice --> ";
    cin >> choice;

    while (choice > 12 || choice < 1) // validation loop
    {
        cout << "Invalid choice, please choose one (1-4): ";
        cin >> choice;
    }
    return (choice);
}

void display_trip(list<Goat> trip) // displays all goats in the "trip"
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

int select_goat(list<Goat> trip)
{
    int index = 0;

    if (trip.size() > 0)
    {
        display_trip(trip); // display list of all first

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

void delete_goat(list<Goat> &trip)
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

void add_goat(list<Goat> &trip, string colors[], string names[])
{
    Goat temp;

    temp.set_name(names[rand() % SZ_NAMES + 1]);    // list temp's name to a random index of names[] array (1-200)
    temp.set_color(colors[rand() % SZ_COLORS + 1]); // list temp's color to a random index of colors[]] array (1-25)
    temp.set_age(rand() % (MAX_AGE + 1));           // list temp age to random num 0-20

    trip.push_back(temp); // push back to add completed goat object to the list
}

/************************************************
 * Function: Calculates and prints the average
 * age of the goats in the trip, uses the accumulate()
 * algorithm to do this.
 *
 * Parameters: trip, list containing the goat objects
 ************************************************/
void average_ages(list<Goat> trip)
{
    double totalAge = accumulate(trip.begin(), trip.end(), 0, [](int sum, Goat goat)
                                 { return sum + goat.get_age(); }); // lambda function
    cout << "Average age of the goats: " << (totalAge / trip.size()) << '\n';
}

/************************************************
 * Function: Wipes the trip of all goats, uses the
 * .clear() algorithm
 *
 * Parameters: &trip, list containing the goat objects
 * passed by reference, as modification of the original
 * list happens in the function
 ************************************************/
void clear_goats(list<Goat> &trip)
{
    cout << "Clearing all goats...\n";
    trip.clear();
    cout << "Result of call to display all: ";
    display_trip(trip); // to show that now empty
}

/************************************************
 * Function: Merges the existing trip with a new
 * trip containing three more Goats, could additionally
 * implement logic that allows for random or user 
 * specified goats. Uses the merge() algorithm
 *
 * Parameters: &trip, list containing the goat objects
 * passed by reference, as modification of the original
 * list happens in the function
 ************************************************/
void merge_trip(list<Goat> &trip)
{
    list<Goat> temp = {{"Timmy",15,"Turquoise"},{"John",12,"Yellow"},{"Bing",11,"Black"}}; //3 goats
    list<Goat> mergedVec(trip.size() + temp.size());
    merge(trip.begin(), trip.end(), temp.begin(), temp.end(), mergedVec.begin());
    trip = mergedVec; 
}

/************************************************
 * Function: Prints all ages only of the goats in
 * the list using the for_each() algorithm
 *
 * Parameters: trip, list containing the goat objects
 ************************************************/
void print_ages(list<Goat> trip)
{
    cout << "All Ages: \n";
    for_each(trip.begin(), trip.end(), [](Goat goat)
             { cout << goat.get_age() << '\n'; }); // changed functionality to print all ages with single line
}

/************************************************
 * Function: Iterates through the trip using the
 * any_of() algorithm as a boolean check to see
 * if any of the goats are over the age of 15,
 * (considered a senior)
 *
 * Parameters: trip, list containing the goat objects
 ************************************************/
void has_senior(list<Goat> trip)
{
    bool isOld = any_of(trip.begin(), trip.end(), [](Goat goat)
                        { return goat.get_age() > 15; });
    cout << "Is a Senior: " << (isOld ? "Yes" : "No") << '\n';
}

/************************************************
 * Function: Copies all data from list trip to a 
 * seperate trip, shows the depth of the copy by
 * calling various functions to change trip2
 *
 * Parameters: trip, list containing the goat objects
 ************************************************/
void copy_trip(list<Goat> trip)
{
    list<Goat> trip2;                     
    copy(trip.begin(), trip.end(), trip2.begin()); // copy contents of trip 1 into vector 2
    cout << "Copy complete, data stored in a seperate list.\n";

    //modifications to trip 2 copy
    merge_trip(trip2);
    display_trip(trip2);
    clear_goats(trip2);
    cout << "After modifying trip 2: \n";
    display_trip(trip2);
}

/************************************************
 * Function: Creates a vector that contains the
 * result of incrementing all age fields of the
 * original trip and compares the values to the
 * original through iterative print statements
 * using the transform() algorithm.
 *
 * Parameters: trip, list containing the goat objects
 ************************************************/
void add_year(list<Goat> &trip)
{
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat &n)
              { return (n.get_age() + 1); });

    // display changes
    cout << "Resultant Ages: \n";
    print_ages(trip);
    cout << '\n';
}

/************************************************
 * Function: Creates a vector that contains a random-
 * ized order of the list elements, randomizing
 * the order using the shuffle() algorithm, then
 * outputs the data of the vector to compare to
 * the original, sorted version.
 *
 * Parameters: trip, list containing the goat objects
 ************************************************/
void shuffle_trip(list<Goat> trip)
{
    vector<Goat> shuffledTrip(trip.size());
    copy(trip.begin(), trip.end(), shuffledTrip.begin()); // copy contents of trip 1 into vector 2
    shuffle(shuffledTrip.begin(), shuffledTrip.end(), default_random_engine());

    int i = 1;
    for (auto it = shuffledTrip.begin(); it != shuffledTrip.end(); ++it, ++i) // for each element in trip
    {
        cout << "[" << i << "] " << it->get_name() << "(" << it->get_age() << ", " << it->get_color() << ")\n"; // print result of shuffle
    }
}
