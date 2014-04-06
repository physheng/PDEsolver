#include "./Field1DClass.h"

Field1DClass::Field1DClass( ){
		 gridSize = 100;
         r   = new double[gridSize];
         Phi = new double[gridSize];
         initPhi = new double[gridSize];
         cout << "FIELD CONSTRUCTED SUCCESSFULLY !" << endl;
      }
      
Field1DClass::~Field1DClass( ){
         delete [] r;
         delete [] Phi;
         delete [] initPhi;
         cout << "FIELD DECONSTRUCTED SUCCESSFULLY !" << endl;
}

bool Field1DClass::initialize( int gridSizeInput ){
		  
         delete [] r;
         delete [] Phi;
         delete [] initPhi;
         
         gridSize = gridSizeInput;
         r   = new double[gridSize];
         Phi = new double[gridSize];
         initPhi = new double[gridSize];
          
         IC = new InitialConditionClass_Sin(1.0,3);
         bool status = IC->Initialize(r, Phi, gridSize);
         status = IC->Initialize(r, initPhi, gridSize);
         if (!status){
            cout << " ERROR: Field could not be initialized." << endl;
            return false;
         }
         return true;
}      


double Field1DClass::returnExactSolution(const double time, int index) const{

   double dx = r[1] - r[0];
   index = index - (int) (time/dx);

   while ( index < 0 ){
      index += gridSize;   
   }

   while ( index >= gridSize ){
      index -= gridSize;   
   }
   
   return initPhi[index];

}

