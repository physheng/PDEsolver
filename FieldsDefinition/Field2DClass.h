#ifndef __FIELDS_2D_CLASS__
#define __FIELDS_2D_CLASS__

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "../GlobalFunctions/saveDataIntoFile.h"

class Field2DClass{

   public:
      
      Field2DClass( void );
      ~Field2DClass( void );

      // This function initialize the field
      bool initialize( int xGridSizeInput, int yGridSizeInput,
                       double vxInput, double vyInput );

      int getXGridSize( void ){ return xGridSize; }
      int getYGridSize( void ){ return yGridSize; }
      int getGridSize( void ){ return gridSize; }
      
      // Return the value of exact solution after time t at point r[index]
      double returnExactSolution(const double time,
                                 int xIndex, int yIndex) ;

      double *returnPhi() const {
         return Phi;
      }
  
  double *returnExactPhi()
  {
    int i,j;
    double *exactPhi = new double[gridSize];
    for(i=0;i<yGridSize;i++){
      for(j=0;j<xGridSize;j++){
        exactPhi[j+i*xGridSize] = returnExactSolution(tempTime, j, i);
      }
    }
    
    return exactPhi;
  }
  

   protected:
   
      double *Phi;

      // Velocities in x,y direction
      double vx;
      double vy;

      int xGridSize;
      int yGridSize;
      int gridSize;
      
   private:
      
      // Initial field for calculating the exact solution
      double *initPhi;
      double tempTime;
};


#endif
