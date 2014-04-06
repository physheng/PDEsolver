#include "RK4KurganovTadmor2000Scheme.h"

double RK4KurganovTadmor2000Scheme::Solve(
               const double r[], double Phi[]){

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


    // Computing the K1 
    FluxSolver->calcFlux(r, Phi, flux, gridSize);
    for (i = 0; i < gridSize; i++){
      rhs[i] = ( flux[i+1] - flux[i] ) / dr;
    }
    for (i = 1; i < (gridSize-1); i++){
       K1[i] = rhs[i] - 0.5 * ( Phi[i+1] - 2*Phi[i] + Phi[i-1] ) / dr;
    }
    K1[0] = rhs[0] - 0.5 * ( Phi[1] - 2*Phi[0] + Phi[gridSize-1] ) / dr;
    K1[gridSize-1] = rhs[gridSize-1]
            - 0.5 * ( Phi[0] - 2*Phi[gridSize-1] + Phi[gridSize-2] ) / dr;


    // Computing the K2 
    for (i = 1; i < (gridSize-1); i++){
       axPhi[i] = 0.5 * ( Phi[i+1] + Phi[i-1] ) + dt * K1[i] / 2;
    }
    axPhi[0] = 0.5 * ( Phi[1] + Phi[gridSize-1] ) + dt * K1[0] / 2;
    axPhi[i] = 0.5 * ( Phi[0] + Phi[gridSize-2] ) + dt * K1[gridSize-1] / 2;

    FluxSolver->calcFlux(r, axPhi, flux, gridSize);
    for (i = 0; i < gridSize; i++){
      rhs[i] = ( flux[i+1] - flux[i] ) / dr;
    }
    for (i = 1; i < (gridSize-1); i++){
       K2[i] = rhs[i] - 0.5 * ( axPhi[i+1] - 2*axPhi[i] + axPhi[i-1] ) / dr;
    }
    K2[0] = rhs[0] - 0.5 * ( axPhi[1] - 2*axPhi[0] + axPhi[gridSize-1] ) / dr;
    K2[gridSize-1] = rhs[gridSize-1]
        - 0.5 * ( axPhi[0] - 2*axPhi[gridSize-1] + axPhi[gridSize-2] ) / dr;



    // Computing the K3
    for (i = 1; i < (gridSize-1); i++){
       axPhi[i] = 0.5 * ( Phi[i+1] + Phi[i-1] ) + dt * K2[i] / 2;
    }
    axPhi[0] = 0.5 * ( Phi[1] + Phi[gridSize-1] ) + dt * K2[0] / 2;
    axPhi[i] = 0.5 * ( Phi[0] + Phi[gridSize-2] ) + dt * K2[gridSize-1] / 2;

    FluxSolver->calcFlux(r, axPhi, flux, gridSize);
    for (i = 0; i < gridSize; i++){
      rhs[i] = ( flux[i+1] - flux[i] ) / dr;
    }
    for (i = 1; i < (gridSize-1); i++){
       K3[i] = rhs[i] - 0.5 * ( axPhi[i+1] - 2*axPhi[i] + axPhi[i-1] ) / dr;
    }
    K3[0] = rhs[0] - 0.5 * ( axPhi[1] - 2*axPhi[0] + axPhi[gridSize-1] ) / dr;
    K3[gridSize-1] = rhs[gridSize-1]
        - 0.5 * ( axPhi[0] - 2*axPhi[gridSize-1] + axPhi[gridSize-2] ) / dr;



    // Computing the K4
    for (i = 1; i < (gridSize-1); i++){
       axPhi[i] = 0.5 * ( Phi[i+1] + Phi[i-1] ) + dt * K3[i];
    }
    axPhi[0] = 0.5 * ( Phi[1] + Phi[gridSize-1] ) + dt * K3[0];
    axPhi[i] = 0.5 * ( Phi[0] + Phi[gridSize-2] ) + dt * K3[gridSize-1];

    FluxSolver->calcFlux(r, axPhi, flux, gridSize);
    for (i = 0; i < gridSize; i++){
      rhs[i] = ( flux[i+1] - flux[i] ) / dr;
    }
    for (i = 1; i < (gridSize-1); i++){
       K4[i] = rhs[i] - 0.5 * ( axPhi[i+1] - 2*axPhi[i] + axPhi[i-1] ) / dr;
    }
    K4[0] = rhs[0] - 0.5 * ( axPhi[1] - 2*axPhi[0] + axPhi[gridSize-1] ) / dr;
    K4[gridSize-1] = rhs[gridSize-1]
        - 0.5 * ( axPhi[0] - 2*axPhi[gridSize-1] + axPhi[gridSize-2] ) / dr;



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

