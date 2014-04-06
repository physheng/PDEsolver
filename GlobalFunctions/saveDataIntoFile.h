#ifndef __SAVEDATAINTOFILE__
#define __SAVEDATAINTOFILE__

#include <iostream>
#include <fstream>
using namespace std;
#include <string>

bool saveDataIntoFile(string fname, string header,  const double A[],
                      int arraySize);
bool saveDataIntoFile(string fname, string header, const double A[],
                      const double B[], int arraySize);
bool saveDataIntoFile(string fname, string header, const double A[],
                      const double B[], const double C[], int arraySize);
bool saveDataIntoFile(string fname, string header, const double A[],
                      const double B[], const double C[],
                      const double D[], const double E[], int arraySize);

#endif
