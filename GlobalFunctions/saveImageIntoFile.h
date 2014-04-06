#ifndef __SAVEIMAGEINTOFILE__
#define __SAVEIMAGEINTOFILE__

#include <iostream>
#include <fstream>
using namespace std;
#include <string>

bool saveImageIntoFile(string fname, const double A[],
                      int arraySizeX, int arraySizeY);

#endif
