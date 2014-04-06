#ifndef __FLUXCALCULATOR_CLASS_PIECEWISEPARABOLICRECONSTRUCTIONSCHEME__
#define __FLUXCALCULATOR_CLASS_PIECEWISEPARABOLICRECONSTRUCTIONSCHEME__

#include "FluxCalculatorClass.h"

class FluxCalculatorPiecewiseParabolicReconstructionScheme:
      public FluxCalculatorClass{

   public:
      
      // This function calculat the flux
      void calcFlux(const double r[], const double Phi[],
                    double Flux[], const int gridSize);

   private:

};


#endif
