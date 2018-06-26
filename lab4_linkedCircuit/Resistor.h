#pragma once
#ifndef RESISTOR_H
#define RESISTOR_H


#include <string>
using namespace std;
class Resistor
{
    private :
    double resistance = 0.0; // resistance (in Ohms)
    string name; // C++ string holding the label
    int endpointNodeIDs[2]; // IDs of nodes it attaches to
    Resistor* next = NULL;
public:
    Resistor(string name_, double resistance_, int endpoints_[2]);
    // rIndex_ is the index of this resistor in the resistor array
    // endpoints_ holds the node indices to which this resistor connects
    
    ~Resistor();
    int firstEnd() const;
    int secondEnd() const;
    string getName() const; // returns the name
    double getResistance() const; // returns the resistance
    
    void setResistance(double resistance_);
    Resistor * getNextResistor();
    void setNextResistor(Resistor * rptr);
    // you *may* create either of the below to print your resistor
    void print();
    friend ostream & operator << (ostream&, const Resistor&);
    void printnode();
    int getAnotherNode(int nodeid1);};

ostream& operator << (ostream&, const Resistor&);

#endif /* RESISTOR_H */
