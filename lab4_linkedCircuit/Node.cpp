//
//  Node.cpp
//  Lab3_Circuit
//
//  Created by Jingwei Zhang on 2017/10/11.
//  Copyright © 2017 Jingwei Zhang. All rights reserved.
//
#include <cstdlib>
#include <iomanip>
#include <string>
#include <iostream>
#include "Node.h"
#include "Rparser.h"
#include "Resistor.h"

// the node constructor
Node::Node(int nodeid_) {
    nodeid = nodeid_;
    rhead.setrhead(NULL);
    voltage = 0;
    next = NULL;
}

// the node destructor which deletes every resistor
Node::~Node() {
    Resistor* rptr;
    while (getResistorHead() != NULL) {
        rptr = getResistorHead();
        setResistorHead(getResistorHead()->getNextResistor());
        delete rptr;
    }
}

// function to get the temp voltage
double Node::getTempV() {
    return tempV;
}

// funciton to set the temp voltage
void Node::setTempV(double tempVol) {
    tempV = tempVol;
}

// the function to get the voltage
double Node::getVoltage() {
    return voltage;
}

// function to add the resistor number
void Node::addResistor() {
    rIndex++;
}

// function to reduce the resistor number
void Node::reduceR() {
    rIndex--;
}

// function to get the nodeid of a node
int Node::getNodeid() {
    return (nodeid);
}

// The member function to print the node connection
void Node::printnode() {
    Resistor* rptr = getResistorHead();
    if (rIndex != 0)
        cout << "Connections at node " << nodeid << ": " << getrIndex() << " resistor(s)" << endl;
    
    while (rptr != NULL) {
        rptr -> printnode();
        rptr = rptr->getNextResistor();
    }
}

// the function to find a resistor by name
Resistor* Node::findResistor(string r_name) {
    return (rhead.findResistor(r_name));
}

// the function to get the head of a resistor list
Resistor* Node::getResistorHead() {
    return rhead.getrhead();
}

// the function to set next node
void Node::setNextNode(Node* nextNode) {
    next = nextNode;
}

// the function to set the head of a resistor list
void Node::setResistorHead(Resistor* rptr) {
    rhead.setrhead(rptr);
}

// the function to get the resistor number of the node
int Node::getrIndex() {
    return (rIndex);
}

// the function to delete a resistor
bool Node::deleteRes(string r_name) {
    Resistor* rptr = getResistorHead();
    // if there is no resistor
    if (rptr == NULL)
        return false;
    // if the resistor to be deleted is the head
    if (rptr -> getName() == r_name) {
        if (rptr -> getNextResistor() == NULL) {
            rhead.setrhead(NULL);
            delete rptr;
            rIndex--;
            return true;
        }
        rhead.setrhead(rptr-> getNextResistor());
        delete rptr;
        rIndex--;
        return true;
    }
    // search the resistor to be deleted
    while (rptr -> getNextResistor() != NULL) {
        if (rptr -> getNextResistor() -> getName() == r_name) {
            Resistor* temp = rptr -> getNextResistor();
            rptr -> setNextResistor(rptr -> getNextResistor() ->getNextResistor());
            delete temp;
            rIndex--;
            return true;
        }
        rptr = rptr -> getNextResistor();
        
    }
    return false;
}

// function to set the voltage of the node
void Node::setVoltage(double voltage_) {
    vset = true;
    voltage = voltage_;
}

// function to solve the node and returns the outcome
double Node::solveNode(NodeList &nodeList) {
    double oneOverR = 0;
    double vOverR = 0;
    Resistor* rptr = getResistorHead();
    double newV = 0;
    int anotherNode;
    // Calculate the outcome using the formula
    while (rptr != NULL) {
        anotherNode = rptr -> getAnotherNode(nodeid);
        vOverR = vOverR + nodeList.getNodeVoltage(anotherNode) / (rptr ->getResistance());
        oneOverR = oneOverR + 1 / (rptr -> getResistance());
        rptr = rptr -> getNextResistor();
    }
    newV = (1 / oneOverR) * vOverR;
    tempV = newV;
    return newV;
}

// function to change the status of the node to unset
void Node::unset() {
    vset = false;
}

// get the voltage status of the node
bool Node::status() {
    return vset;
}







