#include "KurganovTadmor2000Scheme.h"

double KurganovTadmor2000Scheme::Solve(const double r[], double Phi[]){

    int i;
    double dr = r[1] - r[0];
    double dt = dr/5;

    double *flux = new double[gridSize+1];
    double *rhs  = new double[gridSize];

    // Computing the flux 
    FluxSolver->calcFlux(r, Phi, flux, gridSize);

    // Making the right hand side
    for (i = 0; i < gridSize; i++){
      rhs[i] = ( flux[i+1] - flux[i] ) / dr;
    }
    
    // Evolve in time (here flux is axillary variable not actually a flux)
    for (i = 1; i < (gridSize-1); i++){
       flux[i] = Phi[i] 
                 + 0.5 * ( Phi[i+1] - 2*Phi[i] + Phi[i-1] )
                 + dt * rhs[i];
    }
    flux[0] = Phi[0]
              + 0.5 * ( Phi[1] - 2*Phi[0] + Phi[gridSize-1] )
              + dt * rhs[0];
    flux[gridSize-1] =  Phi[gridSize-1]
            + 0.5 * ( Phi[0] - 2*Phi[gridSize-1] + Phi[gridSize-2] )
            + dt * rhs[gridSize-1];

    for (i = 0; i < gridSize; i++){
       Phi[i] = flux[i];
    }

    delete [] flux;
    delete [] rhs;

    return dt;
}

