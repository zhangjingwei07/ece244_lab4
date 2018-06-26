//
//  main.cpp
//  Lab3_Circuit
//
//  Created by 张经纬 on 2017/10/11.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.

#include <iostream>

#define MAX_NODE_NUMBER  5000
#define MIN_NODE_NUMBER  0
#include <sstream>
#include <string>
#include <iomanip>
#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"


// the main function
int main(int argc, const char * argv[]) {
    
    NodeList NodeList;

    Rparser(NodeList);
    
    return 0;
}
