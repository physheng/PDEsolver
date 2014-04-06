#include "LaxFriedrichsScheme.h"

double LaxFriedrichsScheme::Solve( const double r[], double Phi[]){

    int i;
    double dr = r[1] - r[0];
    double dt = dr/5;

    double *flux = new double[gridSize+1];
    double *rhs  = new double[gridSize];

    // Computing the flux 
    //FluxSolver->calcFlux(r, Phi, flux, gridSize);

    // Evolve in time (here flux is axillary variable not actually a flux)
    for (i = 1; i < (gridSize-1); i++){
       flux[i] = 0.5 * ( Phi[i+1] + Phi[i-1] )
                 - 0.5 * dt * ( Phi[i+1] - Phi[i-1] ) / dr;
    }
    flux[0] = 0.5 * ( Phi[1] + Phi[gridSize-1] )
                 - 0.5 * dt * ( Phi[1] - Phi[gridSize-1] ) / dr;
    flux[gridSize-1] = 0.5 * ( Phi[0] + Phi[gridSize-2] )
                 - 0.5 * dt * ( Phi[0] - Phi[gridSize-2] ) / dr;

    for (i = 0; i < gridSize; i++){
       Phi[i] = flux[i];
    }

    delete [] flux;
    delete [] rhs;

    return dt;
}

