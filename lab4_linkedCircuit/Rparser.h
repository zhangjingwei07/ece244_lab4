#ifndef rparser_h
#define rparser_h
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"


void Rparser(NodeList &NodeList);
void deleteNet();
bool readString(stringstream &lineStream, string &string_name, bool can_be_all );
bool readDouble(stringstream &lineStream, double &double_name );
bool readInt(stringstream &lineStream, int &int_name );
bool tooManyArg(stringstream &lineStream);
bool readPrintNode(stringstream &lineStream, int &nodeid1, NodeList& NodeList);
void modifyR(stringstream &lineStream, NodeList &NodeList);
void deleteR(stringstream &lineStream, NodeList &NodeList);
void setMaxVal(stringstream &lineStream);
void printNode(stringstream &lineStream, NodeList& NodeList);
void insertR(stringstream &lineStream, NodeList &NodeList);
void printR(stringstream &lineStream, NodeList &NodeList);
void setV(stringstream &lineStream, NodeList &NodeList);
void unsetV(stringstream &lineStream, NodeList &NodeList);


#endif
