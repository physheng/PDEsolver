#include "intInput.h"

int intInput(string str){
   int integerInput;
   cout << str ;
   cin >> integerInput;
   if (cin.fail()){
      cin.clear();
      cin.ignore(200, '\n');
      cout << "ERROR: Try again. Please Enter an Integer number! \n";
      return 0;
   }
   return integerInput;
} 

void intInput(ifstream &inFile, int &integerInput){
   inFile >> integerInput;
   if (cin.fail()){
      cin.clear();
      cin.ignore(200, '\n');
      cout << "ERROR: Non-integer number is founded!\n";
      integerInput = 0;
   }
   else if (integerInput < 0){
      cout << "ERROR: Not in RGB format!\n";
      integerInput = 0;
   }
} 

void intInput(string str, int &integerInput){
   cout << str ;
   cin >> integerInput;
   if (cin.fail()){
      cin.clear();
      cin.ignore(200, '\n');
      cout << "ERROR: Try again. Please Enter an Integer number! \n";
      integerInput = 0;
   }
} 

void intInput(string str, int &integerInput1, int &integerInput2){
   cout << str ;
   cin >> integerInput1 >> integerInput2;
   if (cin.fail()){
      cin.clear();
      cin.ignore(200, '\n');
      cout << "ERROR: Try again. Please Enter an Integer number! \n";
      integerInput1 = 0;
      integerInput2 = 0; 
   }
} 

