#ifndef __MAINSOLVER_CLASS__
#define __MAINSOLVER_CLASS__

#include <cmath>
#include <iostream>
#include <string>
using namespace std;
#include "../../constants.h"
#include "./FluxSolvers/FluxCalculatorClass.h"

class MainSolverClass{

   public:

      MainSolverClass(){
         cout << " Main Solver is Initialized (Flux Solver is defined)." << endl;
         FluxSolver = new \
             FluxCalculatorClassLinearReconstructionScheme;
         cout << " Flux Solver is Initialized." << endl;
         gridSize = 100;
      }

     virtual ~MainSolverClass(){
		 delete FluxSolver;
	  }

      
      virtual bool setFluxSolver( string fluxCalculatorSchemeName ){
		 if ( fluxCalculatorSchemeName == 
		      "LinearReconstruction" ){
            delete FluxSolver; 
            FluxSolver = new \
                FluxCalculatorClassLinearReconstructionScheme;      
            return true;
	     }
	     else if( fluxCalculatorSchemeName == 
		      "PiecewiseParabolicReconstruction" ){
            delete FluxSolver; 
            FluxSolver = new \
                FluxCalculatorPiecewiseParabolicReconstructionScheme;      
            return true;
	     }
	     else if( fluxCalculatorSchemeName == "MUSCLS" ){
            delete FluxSolver; 
            FluxSolver = new \
                FluxCalculatorClassMUSCLScheme;      
            return true;
	     }
	     else{
            delete FluxSolver; 
            FluxSolver = new \
                FluxCalculatorClassLinearReconstructionScheme;      
            return false;
	     }
	  }

      virtual void setGridSize( int gridSizeInput ){
         gridSize = gridSizeInput;
      }
            
      // Solve the field for 1 time step and return the 
      // new value of Phi (will modify Phi array)
      // return the value of dt
      virtual double Solve(const double r[], double Phi[] ) = 0;

   protected:

      int gridSize;
      FluxCalculatorClass *FluxSolver;

   private:

};

#include "RK4Scheme.h"
#include "MacCormackScheme.h"
#include "ForwardEulerScheme.h"
#include "LaxFriedrichsScheme.h"
#include "KurganovTadmor2000Scheme.h"
#include "RK4KurganovTadmor2000Scheme.h"
#include "KurganovTadmor2ndOrder2000Scheme.h"

#endif
