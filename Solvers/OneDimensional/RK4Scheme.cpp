#include "RK4Scheme.h"

double RK4Scheme::Solve(const double r[], double Phi[]){

    int i;
    double dr = r[1] - r[0];
    double dt = dr/5;

    double *axPhi = new double[gridSize];
    double *flux = new double[gridSize+1];
    double *rhs = new double[gridSize];
    double *K1 = new double[gridSize];
    double *K2 = new double[gridSize];
    double *K3 = new double[gridSize];
    double *K4 = new double[gridSize];

    /// Computing K1 factor
    // Computing the flux 
    FluxSolver->calcFlux(r, Phi, flux, gridSize);
    // Making the right hand side
    for (i = 0; i < gridSize; i++){
      K1[i] = ( flux[i+1] - flux[i] ) / dr;
    }

    /// Computing K2 factor
    // Computing Phi + h/2 K1
    for (i = 0; i < gridSize; i++){
      axPhi[i] = Phi[i] + dt*K1[i]/2.;
    }
    // Computing the flux 
    FluxSolver->calcFlux(r, axPhi, flux, gridSize);
    for (i = 0; i < gridSize; i++){
      K2[i] = ( flux[i+1] - flux[i] ) / dr;
    }

    /// Computing K3 factor
    // Computing Phi + h/2 K2
    for (i = 0; i < gridSize; i++){
      axPhi[i] = Phi[i] + dt*K2[i]/2.;
    }
    // Computing the flux 
    FluxSolver->calcFlux(r, axPhi, flux, gridSize);
    for (i = 0; i < gridSize; i++){
      K3[i] = ( flux[i+1] - flux[i] ) / dr;
    }

    /// Computing K4 factor
    // Computing Phi + h K3
    for (i = 0; i < gridSize; i++){
      axPhi[i] = Phi[i] + dt*K3[i];
    }
    // Computing the flux 
    FluxSolver->calcFlux(r, axPhi, flux, gridSize);
    for (i = 0; i < gridSize; i++){
      K4[i] = ( flux[i+1] - flux[i] ) / dr;
    }

    // Evolve in time
    for (i = 0; i < gridSize; i++){
      Phi[i] = Phi[i] + dt * ( K1[i] + 2.0*K2[i] + 2.0*K3[i] + K4[i] ) / 6.0;
    }

    delete [] axPhi;
    delete [] flux;
    delete [] rhs;
    delete [] K1;
    delete [] K2;
    delete [] K3;
    delete [] K4;

    return dt;
}

