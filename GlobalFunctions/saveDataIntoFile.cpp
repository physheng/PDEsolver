#include "saveDataIntoFile.h"

bool saveDataIntoFile(string fname, string header, const double A[],
                      int arraySize){
   ofstream outFile;
   outFile.open(fname.c_str());
   if (outFile.fail()){
      //cout << "ERROR: It can not open " << fname << " to save data" << endl;
      return false;
   }
   // Header
   outFile << header << endl;
   for (int i=0; i < arraySize; i++){
      outFile << A[i] << endl;
   }
   outFile.close();
   //cout << fname << " is saved successfully." << endl;
   return true;
}

bool saveDataIntoFile(string fname, string header, const double A[], 
                      const double B[], int arraySize){
   ofstream outFile;
   outFile.open(fname.c_str());
   if (outFile.fail()){
      //cout << "ERROR: It can not open " << fname << " to save data" << endl;
      return false;
   }
   // Header
   outFile << header << endl;
   for (int i=0; i < arraySize; i++){
      outFile << A[i] << "  " << B[i] << endl;
   }
   outFile.close();
   //cout << fname << " is saved successfully." << endl;
   return true;
}


bool saveDataIntoFile(string fname, string header, const double A[],
                      const double B[], const double C[],
                      const double D[], const double E[],
                      int arraySize){

   ofstream outFile;
   outFile.open(fname.c_str());
   if (outFile.fail()){
      //cout << "ERROR: It can not open " << fname << " to save data" << endl;
      return false;
   }
   // Header
   outFile << header << endl;
   for (int i=0; i < arraySize; i++){
      outFile << A[i] << " "
              << B[i] << " "
              << C[i] << " "
              << D[i] << " "
              << E[i] << " " << endl;
   }
   outFile.close();
   //cout << fname << " is saved successfully." << endl;
   return true;
}

