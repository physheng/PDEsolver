#include "ForwardEulerScheme2D.h"

double ForwardEulerScheme2D::Solve(double Phi[], double vx,  double vy){

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

    // Evolve in time
    for (i = 0; i < gridSize; i++){
       Phi[i] = Phi[i] + dt * rhs[i];
    }

    delete [] flux;
    delete [] rhs;

    return dt;
}

