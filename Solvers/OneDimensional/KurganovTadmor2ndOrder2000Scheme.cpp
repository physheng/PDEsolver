#include "KurganovTadmor2ndOrder2000Scheme.h"

double KurganovTadmor2ndOrder2000Scheme::Solve(
               const double r[], double Phi[]){

    int i;
    double dr = r[1] - r[0];
    double dt = dr/5;
    double lambda = 0.2;
 
    double *flux = new double[gridSize+1];
    double *rhs  = new double[gridSize];

    // Computing the flux 
    FluxSolver->calcFlux(r, Phi, flux, gridSize);

    // Making the right hand side
    for (i = 0; i < gridSize; i++){
      rhs[i] = ( flux[i+1] - flux[i] ) / dr;
    }

    // Evolve in time (here flux is axillary variable not actually a flux)
    for (i = 2; i < (gridSize-2); i++){
       flux[i] = 0.5 * ( Phi[i+1] + Phi[i-1] ) 
                 - 0.5 * lambda * ( Phi[i+1] - 2*Phi[i] + Phi[i-1] )
                 + 0.25 * lambda * ( lambda + 1 ) 
                   * ( Phi[i+2] - Phi[i+1] - Phi[i-1] + Phi[i-2] ) 
                   / dr
                 + dt * rhs[i];
    }
    flux[1] = 0.5 * ( Phi[2] + Phi[0] ) 
              - 0.5 * lambda * ( Phi[2] - 2*Phi[1] + Phi[0] )
              + 0.25 * lambda * ( lambda + 1 ) 
                * ( Phi[3] - Phi[2] - Phi[0] + Phi[gridSize-1] ) 
                / dr
              + dt * rhs[0];

    flux[0] = 0.5 * ( Phi[1] + Phi[gridSize-1] ) 
              - 0.5 * lambda * ( Phi[1] - 2*Phi[0] + Phi[gridSize-1] )
              + 0.25 * lambda * ( lambda + 1 )
                * ( Phi[2] - Phi[1] - Phi[gridSize-1] + Phi[gridSize-2] )
                / dr
              + dt * rhs[0];

    flux[gridSize-1] = 0.5 * ( Phi[0] + Phi[gridSize-2] ) 
              - 0.5 * lambda * ( Phi[0] - 2*Phi[gridSize-1] + Phi[gridSize-2] )
              + 0.25 * lambda * ( lambda + 1 ) 
                * ( Phi[1] - Phi[0] - Phi[gridSize-2] + Phi[gridSize-3] ) 
                / dr
              + dt * rhs[gridSize-1];

    flux[gridSize-2] = 0.5 * ( Phi[gridSize-1] + Phi[gridSize-3] ) 
              - 0.5 * lambda * ( Phi[gridSize-1] 
                                 - 2*Phi[gridSize-2] + Phi[gridSize-3] )
              + 0.25 * lambda * ( lambda + 1 ) 
                * ( Phi[0] - Phi[gridSize-1] 
                    - Phi[gridSize-3] + Phi[gridSize-4] ) 
                / dr
              + dt * rhs[gridSize-2];

    for (i = 0; i < gridSize; i++){
       Phi[i] = flux[i];
    }

    delete [] flux;
    delete [] rhs;

    return dt;
}

