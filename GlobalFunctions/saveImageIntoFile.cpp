#include "saveImageIntoFile.h"

bool saveImageIntoFile(string fname, const double A[],
                      int arraySizeX, int arraySizeY){
   ofstream outFile;
   outFile.open(fname.c_str());
   if (outFile.fail()){
      //cout << "ERROR: It can not open " << fname << " to save data" << endl;
      return false;
   }
   // Header
   outFile << arraySizeX << "  " << arraySizeY;
   for (int i=0; i < arraySizeX*arraySizeY; i++){
      if ( i%arraySizeX == 0 ){
         outFile << endl;
      }
      outFile << A[i] << "  ";
   }
   outFile.close();
   //cout << fname << " is saved successfully." << endl;
   return true;
}
