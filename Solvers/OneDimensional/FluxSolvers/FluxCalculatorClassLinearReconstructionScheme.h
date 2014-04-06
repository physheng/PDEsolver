#ifndef __FLUXCALCULATOR_CLASS_LINEARRECONSTRUCTIONSCHEME__
#define __FLUXCALCULATOR_CLASS_LINEARRECONSTRUCTIONSCHEME__

#include "FluxCalculatorClass.h"

class FluxCalculatorClassLinearReconstructionScheme:
      public FluxCalculatorClass{

   public:
      
      // This function calculat the flux
      void calcFlux(const double r[], const double Phi[],
                    double Flux[], const int gridSize);

   private:

};


#endif
