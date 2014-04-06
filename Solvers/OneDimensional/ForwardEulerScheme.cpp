#include "ForwardEulerScheme.h"

double ForwardEulerScheme::Solve(
               const double r[], double Phi[]){

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

    // Evolve in time
    for (i = 0; i < gridSize; i++){
       Phi[i] = Phi[i] + dt * rhs[i];
    }

    delete [] flux;
    delete [] rhs;

    return dt;
}

