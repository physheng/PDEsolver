#ifndef __FLUXCALCULATOR_CLASS__
#define __FLUXCALCULATOR_CLASS__

#include <cmath>
#include <iostream>
using namespace std;

class FluxCalculatorClass{

   public:
      
      // This function calculat the flux
      virtual void calcFlux(const double r[],
                            const double Phi[],
                            double Flux[],
                            const int gridSize) = 0;

   private:

};

#include "./FluxCalculatorClassMUSCLScheme.h"
#include "./FluxCalculatorClassLinearReconstructionScheme.h"
#include "./FluxCalculatorPiecewiseParabolicReconstructionScheme.h"

#endif
