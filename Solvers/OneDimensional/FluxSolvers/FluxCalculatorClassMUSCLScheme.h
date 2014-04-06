#ifndef __FLUXCALCULATOR_CLASS_MUSCLSCHEME__
#define __FLUXCALCULATOR_CLASS_MUSCLSCHEME__

#include "FluxCalculatorClass.h"

class FluxCalculatorClassMUSCLScheme:public FluxCalculatorClass{

   public:
      
      // This function calculat the flux
      // This function calculat the flux
      void calcFlux(const double r[], const double Phi[],
                    double Flux[], const int gridSize);

   private:

};


#endif
