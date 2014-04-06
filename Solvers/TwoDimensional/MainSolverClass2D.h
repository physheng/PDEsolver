#ifndef __MAINSOLVER_CLASS_2D__
#define __MAINSOLVER_CLASS_2D__

#include <cmath>
#include <iostream>
#include <string>
using namespace std;
#include "../../constants.h"
#include "./FluxSolvers/FluxCalculatorClass2D.h"

class MainSolverClass2D{

   public:

      MainSolverClass2D(){
         //cout << " Main Solver is Initialized (Flux Solver is defined)." << endl;
         FluxSolver = new \
             FluxCalculatorClassLinearReconstructionScheme2D;
         //cout << " Flux Solver is Initialized." << endl;
         gridSize = 100;
      }

      ~MainSolverClass2D(){
		 delete FluxSolver;
	  }

      
      virtual bool setFluxSolver( string fluxCalculatorSchemeName ){
		 if ( fluxCalculatorSchemeName == 
		      "LinearReconstruction" ){
            delete FluxSolver; 
            FluxSolver = new \
                FluxCalculatorClassLinearReconstructionScheme2D;      
            return true;
	     }
	     else{
            delete FluxSolver; 
            FluxSolver = new \
                FluxCalculatorClassLinearReconstructionScheme2D;      
            return false;
	     }
	  }

      virtual void setGridSize( int xGridSizeInput, int yGridSizeInput ){
        xGridSize = xGridSizeInput;
        yGridSize = yGridSizeInput;
        gridSize = xGridSizeInput * yGridSizeInput;
      }
            
      // Solve the field for 1 time step and return the 
      // new value of Phi (will modify Phi array)
      // return the value of dt
      virtual double Solve( double Phi[], double vx,  double vy ) = 0;

      // From cell index to flux index
      virtual int i2index( const int i ) const{
         return i+(xGridSize+1)*(i/xGridSize);
	  }

   protected:

      int xGridSize, yGridSize, gridSize;
      FluxCalculatorClass2D *FluxSolver;

   private:

};

#include "RK4Scheme2D.h"
#include "ForwardEulerScheme2D.h"
#include "LaxFriedrichsScheme2D.h"

#endif
