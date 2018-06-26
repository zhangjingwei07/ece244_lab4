//
//  ResistorList.cpp
//  lab4_linkedCircuit
//
//  Created by 张经纬 on 2017/11/6.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//

#include "ResistorList.h"
#include "Resistor.h"

// function to get the head pointer to the resistor linked list
Resistor* ResistorList::getrhead() {
    return rhead;
}

// function to set the head pointer of the resistor list
void ResistorList::setrhead(Resistor* rptr) {
    rhead = rptr;
}

// function to find a resistor
Resistor* ResistorList::findResistor(string r_name) {
    Resistor* rptr = rhead;
    while (rptr != NULL) {
        if (rptr->getName() == r_name)
            return rptr;
        rptr = rptr -> getNextResistor();
    }
    return rptr;
}

// function to print every resistor in this list
void ResistorList::printNode() {
    Resistor* rptr = rhead;
    while (rptr != NULL) {
        rptr -> print();
        rptr = rptr -> getNextResistor();
    }
}





