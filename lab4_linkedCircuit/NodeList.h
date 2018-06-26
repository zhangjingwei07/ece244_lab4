//
//  NodeList.h
//  lab4_linkedCircuit
//
//  Created by 张经纬 on 2017/11/5.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//
#pragma once
#ifndef NodeList_h
#define NodeList_h
#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"
class Node;
class NodeList{
    
private:
    Node *head = NULL;
    
public:
    
    ~NodeList();
    void addNode(int nodeid);
    int countValidNode();
    bool canAddResistor(string name);
    void addResistor(string r_name, double resistance, int nodeid[]);
    bool modifyResistor(string r_name, double resistance);
    bool printResistor(string r_name);
    void printNode(int nodeID);
    void printAllNodes();
    void deleteR(string r_name);
    void setVoltage(int nodeid, double voltage);
    void unsetV(int nodeid);
    void deleteAll();
    void solve();
    Node* gethead();
    bool canSolve();
    double getNodeVoltage(int nodeid);
};






#endif /* NodeList_h */
