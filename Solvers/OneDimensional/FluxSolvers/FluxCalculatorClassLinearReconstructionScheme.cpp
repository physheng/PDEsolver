#include "FluxCalculatorClassLinearReconstructionScheme.h"

void FluxCalculatorClassLinearReconstructionScheme::calcFlux(
               const double r[], const double Phi[], double Flux[],
               const int gridSize){

    int i;

    for (i = 1; i < gridSize; i++){
       Flux[i] =  -0.5 * ( Phi[i-1] + Phi[i] );
    }
    
    // Periodic Boundary Condition
    Flux[0] =  -0.5 * ( Phi[0] + Phi[gridSize-1] );
    Flux[gridSize] = Flux[0];

}

