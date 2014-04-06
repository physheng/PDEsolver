#ifndef __FLUXCALCULATOR_CLASS_LINEARRECONSTRUCTIONSCHEME_2D__
#define __FLUXCALCULATOR_CLASS_LINEARRECONSTRUCTIONSCHEME_2D__

#include "FluxCalculatorClass2D.h"

class FluxCalculatorClassLinearReconstructionScheme2D:
      public FluxCalculatorClass2D{

   public:
      
      // This function calculat the flux
      void calcFlux(const double Phi[], double Flux[],
                    const int xGridSize, const int yGridSize,
                    const double vx, const double vy);

   private:

};


#endif
