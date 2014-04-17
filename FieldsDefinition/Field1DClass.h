#ifndef __FIELDS1D_CLASS__
#define __FIELDS1D_CLASS__

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Initial Condition Template
#include "../InitialCondition/InitialConditionClass.h"

class Field1DClass{

   public:
      
      Field1DClass( void );
      ~Field1DClass( void );

      // This function initialize the field
      bool initialize( int gridSizeInput, string icName );

      int getGridSize( void ){ return gridSize; }
      
      // Return the value of exact solution after time t at point r[index]
      double returnExactSolution(const double time, int index) const;

   protected:
   
      double *Phi;
      double *r;
   
      int gridSize;
      
   private:

      InitialConditionClass *IC;

      // Initial field for calculating the exact solution
      double *initPhi;
      
};


#endif
