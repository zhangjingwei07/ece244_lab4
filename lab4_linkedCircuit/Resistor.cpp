//
//  Resistor.cpp
//  Lab3_Circuit
//
//  Created by 张经纬 on 2017/10/11.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//

#include "Node.h"
#include "Rparser.h"
#include "Resistor.h"
#include <string>
#include <iostream>
// the constructor for Resistor
Resistor::Resistor(string name_, double resistance_, int endpoints_[2]) {
    resistance = resistance_;
    name = name_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    next = NULL;
}

// default destructor for Resistor
Resistor::~Resistor() {
}

// get the name of a resistor
string Resistor::getName() const {
    return name;
}

// get the name of a resistor
double Resistor::getResistance() const {
    return resistance;
}

// set the resistance of a resistor
void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
}

// get the pointer to the next resistor
Resistor* Resistor::getNextResistor() {
    return (next);
}

// set the pointor to the next resistor
void Resistor::setNextResistor(Resistor* rptr) {
    next = rptr;
}

// function to print out the resistor info
void Resistor::print() {
    cout.width(21);
    cout << left << name;
    cout.width(8);
    cout << right << fixed
    << setprecision(2) << resistance
    << " Ohms "
    << endpointNodeIDs[0] << " -> "
    << endpointNodeIDs[1] << endl;
}

// function to return the other end of the resistor
int Resistor::getAnotherNode(int nodeid1) {
    if (endpointNodeIDs[0] == nodeid1)
        return endpointNodeIDs[1];
    else return endpointNodeIDs[0];
}

// function to print the resistor info when printing the node
void Resistor::printnode() {
    cout << "  ";
    cout.width(21);
    cout << left << name;
    cout.width(8);
    cout << right << fixed
    << setprecision(2) << resistance
    << " Ohms "
    << endpointNodeIDs[0] << " -> "
    << endpointNodeIDs[1] << endl;
}



