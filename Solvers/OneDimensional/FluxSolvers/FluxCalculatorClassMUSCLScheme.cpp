#include "FluxCalculatorClassMUSCLScheme.h"

void FluxCalculatorClassMUSCLScheme::calcFlux(
               const double r[], const double Phi[], double Flux[],
               const int gridSize){

    int i;
    double ur, ul, ri, FluxLimiter;


    for (i = 2; i < gridSize; i++){
       ri = (Phi[i-1] - Phi[i-2]) / (Phi[i] - Phi[i-1]);
       FluxLimiter = 2. * ri / ( 1. + ri * ri);
       ul = Phi[i-1] + 0.5 * FluxLimiter * (Phi[i] - Phi[i-1]); 
       Flux[i] =  -0.5 * ul;
    }

    ri = (Phi[0] - Phi[gridSize-1]) / (Phi[1] - Phi[0]);
    FluxLimiter = 2. * ri / ( 1. + ri * ri);
    ul = Phi[1] + 0.5 * FluxLimiter * (Phi[1] - Phi[0]); 
    Flux[1] =  -0.5 * ul;

    ri = (Phi[gridSize-1] - Phi[gridSize-2]) / (Phi[0] - Phi[gridSize-1]);
    FluxLimiter = 2. * ri / ( 1. + ri * ri);
    ul = Phi[gridSize-1] + 0.5 * FluxLimiter * (Phi[0] - Phi[gridSize-1]); 
    Flux[0] =  -0.5 * ul;



    for (i = 1; i < (gridSize-1); i++){
       ri = (Phi[i] - Phi[i-1]) / (Phi[i+1] - Phi[i]);
       FluxLimiter = 2. * ri / ( 1. + ri * ri);
       ur = Phi[i] + 0.5 * FluxLimiter * (Phi[i+1] - Phi[i]);
       Flux[i] +=  -0.5 * ur;
    }

    ri = (Phi[0] - Phi[gridSize-1]) / (Phi[1] - Phi[0]);
    FluxLimiter = 2. * ri / ( 1. + ri * ri);
    ur = Phi[0] + 0.5 * FluxLimiter * (Phi[1] - Phi[0]);
    Flux[0] +=  -0.5 * ur;

    ri = (Phi[gridSize-1] - Phi[gridSize-2]) / (Phi[0] - Phi[gridSize-1]);
    FluxLimiter = 2. * ri / ( 1. + ri * ri);
    ur = Phi[gridSize-1] + 0.5 * FluxLimiter * (Phi[0] - Phi[gridSize-1]);
    Flux[gridSize-1] +=  -0.5 * ur;

    Flux[gridSize] = Flux[0];

}

