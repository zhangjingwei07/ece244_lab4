//
//  ResistorList.h
//  lab4_linkedCircuit
//
//  Created by Jingwei Zhang on 2017/11/6.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//
#pragma once
#ifndef ResistorList_h
#define ResistorList_h
#include "Resistor.h"

#endif /* ResistorList_h */

class ResistorList{
    private:
    Resistor* rhead = NULL;
public:
    Resistor* getrhead();
    void setrhead(Resistor* rptr);
    Resistor* findResistor(string r_name);
    void printNode();
};
