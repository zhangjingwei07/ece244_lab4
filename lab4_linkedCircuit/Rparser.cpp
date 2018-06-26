
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Rparser.h"
#include "Node.h"
#include "NodeList.h"
#include "Resistor.h"



// The Parser function

void Rparser(NodeList &NodeList) {
    
    // Setup variables
    
    string line, command;
    bool endloop = false;
    getline(cin, line); // Get a line from standard input
    cout << "> ";
    while (!cin.eof()) {
        // Put the line in a stringstream for parsing
        
        string test_space;
        stringstream lineStream(line);
        lineStream >> command;
        // set max resistor and node number of the net
        
        if (command == "insertR") {
            
            
            insertR(lineStream, NodeList);
            
            
        }
        else if (command == "setV") {
            
            setV(lineStream, NodeList);
        }
        else if (command == "unsetV") {
            
            unsetV(lineStream, NodeList);
        }
        // to modify the value of an existing R
        else if (command == "modifyR") {
            
            
            
            
            modifyR(lineStream, NodeList);
            
        } else if (command == "solve") {
            
            NodeList.solve();
        }
        
        // to print the information of resistors
        else if (command == "printR") {
            
            printR(lineStream, NodeList);
            
        }
        // to print nodes
        else if (command == "printNode") {
            
            printNode(lineStream, NodeList);
            
            
            
        }
        // delete resistor
        else if (command == "deleteR") {
            deleteR(lineStream, NodeList);
        }            // If the command is invalid
        else {
            cout << "Error: invalid command" << endl;
        }
        // Get new command
        getline(cin, line);
        endloop = false;
        cout << "> ";
    } // End input loop until EOF.
}


// The function to read string and check valid

bool readString(stringstream &lineStream, string &string_name, bool can_be_all) {
    bool endloop = false;
    lineStream >> string_name;
    // Name of resistor cannot be "all"
    if (string_name == "all" && can_be_all == false) {
        
        cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
        lineStream.clear();
        return endloop = true;
    }
    // if the name is invalid
    if (lineStream.fail()) {
        lineStream.clear();
        if (lineStream.peek() > 0)
            // Actually a read string won't be invalid, just put it here for fun
            cout << "Error: invalid argument" << endl;
        // If no available char detected
        else if (lineStream.peek() < 0)
            cout << "Error: too few arguments" << endl;
        endloop = true;
    }
    lineStream.clear();
    return endloop;
}

// The function to read double and check valid

bool readDouble(stringstream &lineStream, double &double_name) {
    bool endloop = false;
    lineStream >> double_name;
    // if fail reading r value
    
    if (lineStream.fail()) {
        lineStream.clear();
        // Check too few or invalid argument
        if (lineStream.peek() < 0) {
            cout << "Error: too few arguments" << endl;
        } else
            cout << "Error: invalid argument" << endl;
        return endloop = true;
    }
    // If the int is followed by a invalid char
    if (lineStream.peek() != 32 && lineStream.peek() != -1) {
        cout << "Error: invalid argument" << endl;
        return endloop = true;
    }
    lineStream.clear();
    return endloop;
}

// The function to read int and check valid

bool readInt(stringstream &lineStream, int &int_name) {
    bool endloop = false;
    lineStream >> int_name;
    // If fail reading the int
    if (lineStream.fail()) {
        lineStream.clear();
        // Determine too few or invalid argument
        if (lineStream.peek() < 0)
            cout << "Error: too few arguments" << endl;
        else
            cout << "Error: invalid argument" << endl;
        
        return endloop = true;
    }
    // If the int is followed by a invalid char
    if (lineStream.peek() != 32 && lineStream.peek() != -1) {
        cout << "Error: invalid argument" << endl;
        return endloop = true;
    }
    lineStream.clear();
    return endloop;
}

// The function to detect too many arguments

bool tooManyArg(stringstream &lineStream) {
    bool endloop = false;
    // If a space detected after the last valid argument
    if (lineStream.peek() == 32) {
        string test_space;
        // Put the stream into a new string to see whether there are spaces or chars
        lineStream >> test_space;
        if (test_space != "") {
            cout << "Error: too many arguments" << endl;
            return endloop = true;
        }
    }
    // If the last int is followed by a invalid char
    if (lineStream.peek() != 32 && lineStream.peek() > 0) {
        cout << "Error: invalid argument" << endl;
        endloop = true;
    }
    lineStream.clear();
    return endloop;
}

// The function to check the command of printing an existing node

bool readPrintNode(stringstream &lineStream, int &nodeid1, NodeList& NodeList) {
    bool endloop = false;
    string node_all;
    lineStream >> nodeid1;
    // If fail reading the int
    if (lineStream.fail()) {
        lineStream.clear();
        // Argument is too few
        if (lineStream.peek() < 0) {
            cout << "Error: too few arguments" << endl;
            return endloop = true;
        }
        // Check whether the failed reading is caused by name "all"
        if (lineStream.peek() >= 0) {
            lineStream >> node_all;
            lineStream.clear();
            // If all argument detected
            if (node_all == "all") {
                NodeList.printAllNodes();
            }// If other invalid argument detected
            else
                cout << "Error: invalid argument" << endl;
            endloop = true;
            
            
            
            return endloop;
        }
    }
    
    lineStream.clear();
    // Check whether the nodeid is in range
    
    
    
    
    return endloop;
}
// function to delete resistors


// function to build a new circuit net after deleting the existing one


// function to insert resistors

void insertR(stringstream &lineStream, NodeList &NodeList) {
    bool endloop = false;
    string r_name;
    double r_value;
    int nodeid1, nodeid2 = 0;
    bool can_be_all;
    // Read the resistor name and determine if the name is valid
    can_be_all = false;
    if (readString(lineStream, r_name, can_be_all))
        return;
    
    lineStream.clear();
    
    // Read the resistor value and determine if the value is valid
    if (readDouble(lineStream, r_value))
        return;
    
    if (r_value < 0) {
        cout << "Error: negative resistance" << endl;
        return;
    }
    lineStream.clear();
    
    // Read the value for nodeid1 and check valid
    if (readInt(lineStream, nodeid1))
        return;
    
    lineStream.clear();
    
    // Read nodeid2 and check valid
    if (readInt(lineStream, nodeid2))
        return;
    
    
    // Nodeid1 and nodeid2 cannot be equal
    if (nodeid1 == nodeid2) {
        
        cout << "Error: both terminals of resistor connect to node " << nodeid1 << endl;
        return;
    }
    
    // Detect too many argument and int followed by other syntax
    if (tooManyArg(lineStream))
        return;
    
    int node[2];
    node[0] = nodeid1;
    node[1] = nodeid2;
    
    // Determine whether a resistor can be added and add corresponding nodes
    if (NodeList.canAddResistor(r_name)) {
        NodeList.addNode(nodeid1);
        NodeList.addNode(nodeid2);
        NodeList.addResistor(r_name, r_value, node);
    }
    
    // cout the input info
    cout << fixed << setprecision(2) << "Inserted: resistor " << r_name << " " << r_value << " Ohms " << nodeid1 << " -> " << nodeid2 << endl;
    
    endloop = true;
    
    
}

// function to modify existing resistor

void modifyR(stringstream &lineStream, NodeList &NodeList) {
    string r_name;
    double r_value;
    bool can_be_all = false;
    // read rName and check valid
    if (readString(lineStream, r_name, can_be_all))
        return;
    
    // Read the resistor value and check valid
    if (readDouble(lineStream, r_value))
        return;
    
    // Check whether the value of resistor is negative
    if (r_value < 0) {
        cout << "Error: negative resistance" << endl;
        return;
    }
    
    // Check if there are too many arguments
    if (tooManyArg(lineStream))
        return;
    // modifyR
    if (!NodeList.modifyResistor(r_name, r_value))
        cout << "Error: resistor " << r_name << " not found" << endl;
    
    
    return;
}


// function to delete resistors

void deleteR(stringstream &lineStream, NodeList &NodeList) {
    bool can_be_all = true;
    string r_name;
    // Read the resistor name to be deleted and check valid
    if (readString(lineStream, r_name, can_be_all))
        return;
    
    lineStream.clear();
    // Check too many arguments
    if (tooManyArg(lineStream))
        return;
    // Check whether the name is all
    if (r_name != "all") {
        
        NodeList.deleteR(r_name);
        
    }        // Output the outcome
    else {
        cout << "Deleted: all resistors" << endl;
        NodeList.deleteAll();
        
    }
    
    return;
}




// function to print resistors

void printR(stringstream &lineStream, NodeList &NodeList) {
    // Read the resistor name and check valid
    string r_name;
    bool can_be_all = true;
    // read rName and check valid
    if (readString(lineStream, r_name, can_be_all))
        return;
    lineStream.clear();
    
    // Read the resistor value and check valid
    if (tooManyArg(lineStream))
        return;
    
    // Check whether to print all resistors
    if (r_name != "all") {
        NodeList.printResistor(r_name);
    }
    // print all resistors
    
    return;
}

// function to print nodes

void printNode(stringstream &lineStream, NodeList& NodeList) {
    int nodeid1;
    // Read the node to be printed and check valid
    if (readPrintNode(lineStream, nodeid1, NodeList))
        return;
    
    // Check too many arguments
    if (tooManyArg(lineStream))
        return;
    
    // Output the print outcome
    
    NodeList.printNode(nodeid1);
    
    return;
}

// function to set the voltage for a node
void setV(stringstream &lineStream, NodeList &NodeList) {
    int nodeid;
    double voltage;
    readInt(lineStream, nodeid);
    readDouble(lineStream, voltage);
    NodeList.setVoltage(nodeid, voltage);
    
}

// function to unset the voltage for a node

void unsetV(stringstream &lineStream, NodeList &NodeList) {
    int nodeid;
    readInt(lineStream, nodeid);
    NodeList.unsetV(nodeid);
}




