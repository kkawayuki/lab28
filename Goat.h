// Goat.h
#ifndef GOAT_H
#define GOAT_H
#include <iostream>
using namespace std;

class Goat {
private:
    string name;
    int age;
    string color;
public: 
    Goat()                          { name = ""; age = 0; color = ""; }
    
    // three more constructors (n/na/nac)
    Goat(string n)
    {
        name = n; age = 0; color = "";
    };

    Goat(string n, int a)
    {
        name = n; age = a; color = "";
    };

    Goat(string n, int a, string c)
    {
        name = n; age = a; color = c;
    };
    
    // setters and getters
    void set_name(string n)         { name = n; };
    string get_name() const         { return name; };
    void set_age(int a)             { age = a; };
    int get_age() const             { return age; }
    void set_color(string c)        { color = c; }
    string get_color() const        { return color; }

    // overloaded < operator for the std::list
    bool operator<(const Goat &second) const
    {
        return(this->name < second.name); //returns a boolean expression based on the name of the two goats
    };
};

#endif