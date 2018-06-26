/* 
 * File:   Node.h
 * Author: JC and VB
 * Author: TSA
 *
 * Updated on August 24, 2016, 01:40 PM
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef NODE_H
#define NODE_H
#define MAX_RESISTORS_PER_NODE 5
#include "Resistor.h"
#include "ResistorList.h"
#include "NodeList.h"

class NodeList;
class Node
{

private:
    double voltage = 0;
    int nodeid=0;
    ResistorList rhead;
    Node* next = NULL;
    int rIndex = 0;
    bool vset = false;
    double tempV = 0 ;
    // number of resistors currently connected
    // stores the index of each resistor connected
   
public:
    
    
   Node(int nodeid_);
   ~Node();
    Node* getNextNode() {return next;}
    Resistor* getResistorHead();
    void addResistor ();
    void reduceR();
    bool status();
    void unset();
    double getTempV();
    void setTempV(double tempVol);
    
   // Checks to see if the resistor can be added to poistion rIndex
   // in the resistor array. Returns true if yes, otherwise false.
    bool canAddResistor(int rIndex);
    int getNodeid();
    // Checks to see if the resistor can be added to poistion
    // in the node array. Returns true if yes, otherwise false.
    bool canAddNode();
    void setResistorHead(Resistor* rptr);
   // Updates resIDArray to make the resistor in position rIndex in
   // the resistor array connected to this node.
   void addResistor (int rIndex); 
    double getVoltage();
   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   void print ();
    void printnode();
    void setNextNode(Node* nextptr);
    Resistor* findResistor(string r_name);
    int getrIndex();
    bool deleteRes(string r_name);
    void setrhead(Resistor* newhead);
    void setVoltage(double voltage_);
    double solveNode(NodeList &nodeList);
};

#endif	/* NODE_H */

