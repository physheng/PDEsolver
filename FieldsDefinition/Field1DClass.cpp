#include "./Field1DClass.h"

Field1DClass::Field1DClass( ){
   gridSize = 100;
   r = new double[gridSize];
   Phi = new double[gridSize];
   initPhi = new double[gridSize];
   IC = new InitialConditionClass_Sin;
   cout << "FIELD CONSTRUCTED SUCCESSFULLY !" << endl;
}
      
Field1DClass::~Field1DClass( ){
   delete [] r;
   delete [] Phi;
   delete [] initPhi;
   cout << "FIELD DECONSTRUCTED SUCCESSFULLY !" << endl;
}

bool Field1DClass::initialize( int gridSizeInput, string icName ){
		  
   delete [] r;
   delete [] Phi;
   delete [] initPhi;
   delete [] IC;
                   
   gridSize = gridSizeInput;
   r = new double[gridSize];
   Phi = new double[gridSize];
   initPhi = new double[gridSize];
         
   if ( icName == "Sin" ){ 
      IC = new InitialConditionClass_Sin;
   }
   else if ( icName == "Step" ){ 
      IC = new InitialConditionClass_Step;
   }
   else if ( icName == "RndNoise" ){ 
      IC = new InitialConditionClass_RndNoise;
   }
   else { 
      IC = new InitialConditionClass_Sin;
   }
   
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
   int indexp = index - (int) (time/dx);
   double dxp = (double)index * dx - time - (double)indexp * dx;
   dxp = -dxp;

   while ( indexp < 0 ){
      indexp += gridSize;   
   }

   while ( indexp >= gridSize ){
      indexp -= gridSize;   
   }
   
   if ( indexp != 0 ){
      return initPhi[indexp] + dxp*(initPhi[indexp-1]-initPhi[indexp])/dx;
   }
   else{
      return initPhi[0] + dxp*(initPhi[gridSize-1]-initPhi[0])/dx;
   }

}

