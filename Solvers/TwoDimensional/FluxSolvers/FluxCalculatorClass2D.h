#ifndef __FLUXCALCULATOR_2D_CLASS__
#define __FLUXCALCULATOR_2D_CLASS__

#include <cmath>
#include <iostream>
using namespace std;

class FluxCalculatorClass2D{

   public:
      
      // This function calculat the flux
      virtual void calcFlux(const double Phi[], double Flux[],
                            const int xGridSize, const int yGridSize,
                            const double vx, const double vy) = 0;

   private:

};

#include "./FluxCalculatorClassLinearReconstructionScheme2D.h"

#endif
