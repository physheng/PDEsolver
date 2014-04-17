#include "LaxFriedrichsScheme2D.h"

double LaxFriedrichsScheme2D::Solve( double Phi[], double vx,  double vy ){


    int i, index;
    double dr = 1.0;
    double dt = dr/ 5.0 / (max(abs(vx),abs(vy)));

    double *flux = new double[yGridSize*(xGridSize+1)+xGridSize*(yGridSize+1)];
    double *rhs  = new double[gridSize];

    // Computing the flux 
    FluxSolver->calcFlux(Phi, flux, xGridSize, yGridSize, vx, vy);

    // Making the right hand side
    for (i = 0; i < gridSize; i++){
	  index = i+(xGridSize+1)*(i/xGridSize);
      rhs[i] = ( flux[index+2*xGridSize+1] - flux[index]
                 + flux[index+xGridSize+1] - flux[index+xGridSize] )
                  / dr ;
    }

    // Evolve in time (here flux is axillary variable not actually a flux)
    for (i = xGridSize; i < (gridSize-xGridSize); i++){
       flux[i] = 0.25 * ( Phi[i+1] + Phi[i-1] + Phi[i+xGridSize] + 
                          Phi[i-xGridSize] ) + dt * rhs[i];
    }

    // Lower bound
    for (i = 1; i < xGridSize-1; i++){
       flux[i] = 0.25 * ( Phi[i+1] + Phi[i-1] + Phi[i+xGridSize] + 
                          Phi[i+xGridSize*(yGridSize-1)] )
                 + dt * rhs[i];
    }

    // Upper bound
    for (i = (gridSize-xGridSize+1); i < gridSize-1; i++){
       flux[i] = 0.25 * ( Phi[i+1] + Phi[i-1] + Phi[i-xGridSize] + 
                          Phi[i-xGridSize*(yGridSize-1)] )
                 + dt * rhs[i];
    }

    // Right bound
    for (i = xGridSize-1; i < gridSize-1; i+=xGridSize){
       flux[i] = 0.25 * ( Phi[i-xGridSize+1] + Phi[i-1] + Phi[i+xGridSize] + 
                          Phi[i-xGridSize] )
                 + dt * rhs[i];
    }

    // Left bound
    for (i = xGridSize; i < gridSize-1; i+=xGridSize){
       flux[i] = 0.25 * ( Phi[i+1] + Phi[i+xGridSize-1] + Phi[i+xGridSize] + 
                          Phi[i-xGridSize] )
                 + dt * rhs[i];
    }

    // Corners
    
    flux[0] = 0.25 * ( Phi[1] + Phi[xGridSize] + Phi[xGridSize-1]
                       + Phi[xGridSize*(yGridSize-1)] ) + dt * rhs[0];

    flux[xGridSize-1] = 0.25 * ( Phi[0] + Phi[xGridSize-2] 
                       + Phi[2*xGridSize-1] + Phi[gridSize-1] ) + dt * rhs[0];

    flux[xGridSize*(yGridSize-1)] = 0.25 * ( Phi[0] + Phi[gridSize-1] 
                       + Phi[xGridSize*(yGridSize-1)+1]
                       + Phi[xGridSize*(yGridSize-2)] ) + dt * rhs[0];

    flux[gridSize-1] = 0.25 * ( Phi[xGridSize*(yGridSize-1)] + Phi[xGridSize-2] 
                       + Phi[xGridSize-1] + Phi[gridSize-xGridSize-1] )
                       + dt * rhs[0];

    for (i = 0; i < gridSize; i++){
       Phi[i] = flux[i];
    }

    delete [] flux;
    delete [] rhs;

    return dt;
}

