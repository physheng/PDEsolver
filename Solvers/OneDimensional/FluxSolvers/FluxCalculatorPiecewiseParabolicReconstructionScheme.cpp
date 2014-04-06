#include "FluxCalculatorPiecewiseParabolicReconstructionScheme.h"

void FluxCalculatorPiecewiseParabolicReconstructionScheme::calcFlux(
               const double r[], const double Phi[], double Flux[],
               const int gridSize){

    int i;
    double ur, ul, ri, FluxLimiter;


    for (i = 2; i < gridSize; i++){
       ri = (Phi[i-1] - Phi[i-2]) / (Phi[i] - Phi[i-1]);
       FluxLimiter = max(0.0,min(1.0,ri));//2. * ri / ( 1. + ri * ri);
       ul = Phi[i-1] 
            + FluxLimiter * ( 4*Phi[i] - 2*Phi[i-1] - 2*Phi[i-2] ) / 12;
       Flux[i] = -0.5 * ul;
    }

    ri = (Phi[0] - Phi[gridSize-1]) / (Phi[1] - Phi[0]);
    FluxLimiter = max(0.0,min(1.0,ri));//2. * ri / ( 1. + ri * ri);
    ul = Phi[0] 
         + FluxLimiter*( 4*Phi[1] - 2*Phi[0] - 2*Phi[gridSize-1])/12;
    Flux[1] = -0.5 * ul;

    ri = (Phi[gridSize-1] - Phi[gridSize-2]) / (Phi[0] - Phi[gridSize-1]);
    FluxLimiter = max(0.0,min(1.0,ri));//2. * ri / ( 1. + ri * ri);
    ul = Phi[gridSize-1] 
         + FluxLimiter*( 4*Phi[0] - 2*Phi[gridSize-1] - 2*Phi[gridSize-2])/12;
    Flux[0] = -0.5 * ul;



    for (i = 1; i < (gridSize-1); i++){
       ri = (Phi[i] - Phi[i-1]) / (Phi[i+1] - Phi[i]);
       FluxLimiter = max(0.0,min(1.0,ri));//2. * ri / ( 1. + ri * ri);
       ur = Phi[i] 
            - 0.5 * FluxLimiter * ( 2*Phi[i+1] + 2*Phi[i] - 4*Phi[i-1] );
       Flux[i] +=  -0.5 * ur;
    }

    ri = (Phi[0] - Phi[gridSize-1]) / (Phi[1] - Phi[0]);
    FluxLimiter = max(0.0,min(1.0,ri));//2. * ri / ( 1. + ri * ri);
    ur = Phi[0] 
         - 0.5 * FluxLimiter * ( 2*Phi[1] + 2*Phi[0] - 4*Phi[gridSize-1] );
    Flux[0] +=  -0.5 * ur;

    ri = (Phi[gridSize-1] - Phi[gridSize-2]) / (Phi[0] - Phi[gridSize-1]);
    FluxLimiter = max(0.0,min(1.0,ri));//2. * ri / ( 1. + ri * ri);
    ur = Phi[0] 
         - 0.5*FluxLimiter*(2*Phi[0] + 2*Phi[gridSize-1] - 4*Phi[gridSize-2]);
    Flux[gridSize-1] +=  -0.5 * ur;

    Flux[gridSize] = Flux[0];

}

