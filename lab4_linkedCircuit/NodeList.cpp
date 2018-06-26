//
//  linkedlist.cpp
//  lab4_linkedCircuit
//  Xcode 9.1 beta on MacOS 10.13.2 beta
//
//  Created by Jingwei Zhang on 2017/11/5.
//  Copyright © 2017 Jingwei Zhang. All rights reserved.
//

#include "NodeList.h"
#include "Node.h"
#include <iostream>
#include <iomanip>

// destructor to delete the nodelist
NodeList::~NodeList() {
    
    Node* ptr;
    while (head != NULL) {
        ptr = head;
        head = ptr -> getNextNode();
        delete ptr;
    }
}

// the function to get node head
Node* NodeList::gethead() {
    return head;
}

// the function to add a node if the node does't exist
void NodeList::addNode(int nodeid) {
    
    Node* tptr = head;
    // if the node is found, return
    while (tptr != NULL) {
        if (tptr->getNodeid() == nodeid) return;
        tptr = tptr->getNextNode();
    }
    Node* nptr = new Node(nodeid);
    
    // if the node not found, insert in ascending order
    tptr = head;
    // insert at head
    if (head == NULL) {
        head = nptr;
        nptr ->setNextNode(NULL);
        return;
    }
    // insert before the existing head node
    if (head->getNodeid() > nodeid) {
        nptr->setNextNode(head);
        head = nptr;
        return;
    }
    // insert in middle
    while (tptr ->getNextNode() != NULL) {
        
        if (tptr->getNextNode()->getNodeid() > nodeid) {
            
            nptr->setNextNode(tptr->getNextNode());
            tptr->setNextNode(nptr);
            return;
        }
        tptr = tptr-> getNextNode();
    }
    tptr ->setNextNode(nptr);
    nptr -> setNextNode(NULL);
    return;
    
    
}

// function to determine whether a resistor can be added
bool NodeList::canAddResistor(string name) {
    Node* nodeptr = head;
    while (nodeptr != NULL) {
        Resistor *rptr = nodeptr->getResistorHead();
        while (rptr != NULL) {
            if (rptr->getName() == name)
                return false;
            rptr = rptr -> getNextResistor();
        }
        nodeptr = nodeptr->getNextNode();
    }
    return true;
}

// function to insert a resistor
void NodeList::addResistor(string r_name, double r_value, int nodeid[]) {
    Resistor* temp;
    temp = new Resistor(r_name, r_value, nodeid);
    Node* nodeptr = head;
    bool inserted1 = false;
    // insert to the first node
    while (nodeptr != NULL && !inserted1) {
        if (nodeptr->getNodeid() == nodeid[0]) {
            nodeptr -> addResistor();
            if (nodeptr -> getResistorHead() == NULL) {
                nodeptr ->setResistorHead(temp);
                break;
            }
            Resistor *rptr = nodeptr->getResistorHead();
            while (rptr != NULL) {
                if (rptr->getNextResistor() == NULL) {
                    rptr->setNextResistor(temp);
                    temp->setNextResistor(NULL);
                    inserted1 = true;
                    break;
                }
                
                rptr = rptr -> getNextResistor();
            }
            
        }
        nodeptr = nodeptr->getNextNode();
    }
    
    nodeptr = head;
    // insert to the second node
    Resistor* temp2 = new Resistor(r_name, r_value, nodeid);
    while (nodeptr != NULL) {
        if (nodeptr->getNodeid() == nodeid[1]) {
            nodeptr -> addResistor();
            if (nodeptr -> getResistorHead() == NULL) {
                nodeptr ->setResistorHead(temp2);
                break;
            }
            Resistor *rptr = nodeptr->getResistorHead();
            while (rptr != NULL) {
                if (rptr->getNextResistor() == NULL) {
                    rptr->setNextResistor(temp2);
                    return;
                }
                
                rptr = rptr -> getNextResistor();
            }
            
        }
        nodeptr = nodeptr->getNextNode();
    }
}

bool NodeList::modifyResistor(string r_name, double resistance) {
    Node* nodeptr = head;
    bool modified = false;
    while (nodeptr != NULL) {
        Resistor *rptr = nodeptr->getResistorHead();
        while (rptr != NULL) {
            if (rptr->getName() == r_name) {
                if (!modified)
                    cout << fixed << setprecision(2) << "Modified: resistor " << rptr->getName() << " from " <<
                    rptr ->getResistance() << " Ohms" << " to " << resistance << " Ohms" << endl;
                
                rptr -> setResistance(resistance);
                modified = true;
            }
            rptr = rptr -> getNextResistor();
        }
        nodeptr = nodeptr -> getNextNode();
    }
    return modified;
}

// function to print a existing resistor by searching the name
bool NodeList::printResistor(string r_name) {
    Node* nodeptr = head;
    while (nodeptr != NULL) {
        Resistor* rPrint = nodeptr->findResistor(r_name);
        if (rPrint != NULL) {
            cout << "Print:" << endl;
            rPrint -> print();
            return true;
        } else
            nodeptr = nodeptr->getNextNode();
    }
    cout << "Error: resistor " << r_name << " not found" << endl;
    return true;
}

// the function to print a given nodeid
void NodeList::printNode(int nodeID) {
    Node* nodeptr = head;
    cout << "Print:" << endl;
    while (nodeptr != NULL) {
        if (nodeID == nodeptr ->getNodeid())
            nodeptr -> printnode();
        nodeptr = nodeptr -> getNextNode();
    }
}

// print all the nodes
void NodeList::printAllNodes() {
    Node* nodeptr = head;
    cout << "Print:" << endl;
    while (nodeptr != NULL) {
        nodeptr -> printnode();
        nodeptr = nodeptr -> getNextNode();
    }
}

// function to delete a resistor given a name
void NodeList::deleteR(string r_name) {
    Node* nodeptr = head;
    bool deleted = false;
    // search and delete R node by node
    while (nodeptr != NULL && deleted == false) {
        
        if (nodeptr -> deleteRes(r_name))
            deleted = true;
        nodeptr = nodeptr -> getNextNode();
    }
    // if the resistor is not found after searching the whole list
    if (deleted == false) {
        cout << "Error: resistor " << r_name << " not found" << endl;
        return;
    }
    cout << "Deleted: resistor " << r_name << endl;
    deleted = false;
    nodeptr = head;
    while (nodeptr != NULL && deleted == false) {
        deleted = nodeptr -> deleteRes(r_name);
        nodeptr = nodeptr -> getNextNode();
        
    }
    
}

// the function to delete all the resistors
void NodeList::deleteAll() {
    Node* nodeptr = head;
    while (nodeptr != NULL) {
        
        Resistor* rptr = nodeptr -> getResistorHead();
        while (rptr != NULL) {
            nodeptr -> reduceR();
            nodeptr -> setResistorHead(nodeptr -> getResistorHead() ->getNextResistor());
            delete rptr;
            rptr = nodeptr -> getResistorHead();
        }
        nodeptr = nodeptr -> getNextNode();
    }
    
}

// the function to set the voltage of a node
void NodeList::setVoltage(int nodeid, double voltage) {
    Node* nodeptr = head;
    while (nodeptr != NULL) {
        if (nodeptr->getNodeid() == nodeid) {
            nodeptr -> setVoltage(voltage);
            nodeptr -> setTempV(voltage);
            cout << "Set: node " << nodeid << " to " << voltage << " Volts" << endl;
            return;
        }
        
        nodeptr = nodeptr -> getNextNode();
    }
    cout << "Error: node " << nodeid << " not found" << endl;
}

// the function to unset voltage of a node
void NodeList::unsetV(int nodeid) {
    Node* nodeptr = head;
    while (nodeptr != NULL) {
        if (nodeptr->getNodeid() == nodeid) {
            nodeptr -> setVoltage(0);
            nodeptr -> setTempV(0);
            nodeptr -> unset();
            cout << "Unset: the solver will determine the voltage of node " << nodeid << endl;
            return;
        }
        
        nodeptr = nodeptr -> getNextNode();
    }
    cout << "Error: node " << nodeid << " not found" << endl;
}

// the function to count the number of nodes that can be solved
int NodeList::countValidNode() {
    Node* nodeptr = head;
    int count = 0;
    while (nodeptr != NULL) {
        if (nodeptr->getrIndex() != 0 && !nodeptr -> status())
            count++;
        nodeptr = nodeptr-> getNextNode();
    }
    return count;
}

// function to determine whether there is at least a set voltage in the list
bool NodeList::canSolve() {
    Node* nodeptr = head;
    while (nodeptr != NULL) {
        if (nodeptr -> status())
            return true;
        nodeptr = nodeptr -> getNextNode();
    }
    return false;
}

// the function to solve the node list
void NodeList::solve() {
    double oldV[countValidNode()];
    double newV[countValidNode()];
    bool firstCalc = true;
    bool thisDiffOK = false;
    if (!canSolve()) {
        cout << "Error: no nodes have their voltage set" << endl;
        return;
    }
    cout << "Solve:" << endl;
    
    while (!thisDiffOK) {
        Node* nodeptr = head;
        int i = 0;
        while (nodeptr != NULL) {
            
            if (nodeptr -> getrIndex() != 0 && !nodeptr -> status()) {
                
                oldV[i] = newV[i];
                newV[i] = nodeptr -> solveNode(*this);
                i++;
            }
            nodeptr = nodeptr -> getNextNode();
        }
        thisDiffOK = true;
        if (true) {
            for (int i = 0; i < countValidNode(); i++) {
                
                double diff = (oldV[i] - newV[i]);
                if (oldV[i] < newV[i])
                    diff = -diff;
                if (diff > 0.0001) {
                    thisDiffOK = false;
                    break;
                }
                
                
            }
            
            
        }
        firstCalc = false;
        
    }
    
    int i = 0;
    Node* nodeptr = head;
    while (nodeptr != NULL) {
        if (nodeptr ->status())
            cout << "  " << "Node " << nodeptr -> getNodeid() << ": " << nodeptr ->getVoltage() << " V" << endl;
        if (nodeptr->getrIndex() != 0 && !nodeptr ->status()) {
            cout << "  " << "Node " << nodeptr -> getNodeid() << ": " << newV[i] << " V" << endl;
            i++;
        }
        nodeptr = nodeptr -> getNextNode();
    }
    
    nodeptr = head;
    while (nodeptr != NULL) {
        nodeptr -> setTempV(nodeptr -> getVoltage());
        nodeptr = nodeptr -> getNextNode();
    }
    
    
    
}

// the function to get the voltage of a node
double NodeList::getNodeVoltage(int nodeid) {
    Node* nodeptr = head;
    while (nodeptr != NULL) {
        if (nodeid == nodeptr -> getNodeid())
            return (nodeptr -> getTempV());
        nodeptr = nodeptr->getNextNode();
    }
    return 0;
}













