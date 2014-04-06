#ifndef __INTINPUT__
#define __INTINPUT__

#include <iostream>
#include <fstream>
using namespace std;
#include <string>

// Print out the string and ask for an integer then
// get an integer input from user. This function check the type of input
// if it is not an integer it returns error value defined in constants 
// ask for 1 integer, 2 integer, and reading file type integer
int intInput(string);
void intInput(string, int &integerInput);
void intInput(string, int &integerInput1, int &integerInput2);
void intInput(ifstream &inFile, int &integerInput);

#endif
