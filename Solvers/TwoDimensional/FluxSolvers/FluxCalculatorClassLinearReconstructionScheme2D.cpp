#include "FluxCalculatorClassLinearReconstructionScheme2D.h"

void FluxCalculatorClassLinearReconstructionScheme2D::calcFlux(
               const double Phi[], double Flux[],
               const int xGridSize, const int yGridSize,
               const double vx, const double vy){

    int i, index, gridSize;
    gridSize = xGridSize*yGridSize;

    // Bulk
    for ( i = xGridSize; i < gridSize; i++){
       index = i+(xGridSize+1)*(i/xGridSize);
       Flux[index] =  -0.5 * vy * ( Phi[i-xGridSize] + Phi[i] );
       Flux[index+xGridSize] =  -0.5 * vx * ( Phi[i-1] + Phi[i] );
    }
 
    // Periodic Boundary Condition
    // Lower boundary   
    for ( i = 1; i < xGridSize; i++){
       index = i+(xGridSize+1)*(i/xGridSize);
       Flux[index] =  -0.5 * vy * ( Phi[i+gridSize-xGridSize] + Phi[i] );
       Flux[index+xGridSize] =  -0.5 * vx * ( Phi[i-1] + Phi[i] );
    }
    Flux[0] =  -0.5 * vy * ( Phi[0] + Phi[(yGridSize-1)*xGridSize] );

    // Left boundary and right boundary
    for ( i = 0; i < gridSize; i+=xGridSize){
       index = i+(xGridSize+1)*(i/xGridSize);
       Flux[index+xGridSize] =  -0.5 * vx * ( Phi[i+xGridSize-1] + Phi[i] );
       Flux[index+2*xGridSize] = Flux[index+xGridSize];
    }

    // Upper boundary
    for ( i = gridSize-xGridSize; i < gridSize; i++){
       index = i+(xGridSize+1)*(i/xGridSize);
       Flux[index+2*xGridSize+1] = Flux[i-gridSize+xGridSize];
    }
    
}

