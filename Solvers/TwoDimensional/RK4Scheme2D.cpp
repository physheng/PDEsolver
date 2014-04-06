#include "RK4Scheme2D.h"

double RK4Scheme2D::Solve( double Phi[], double vx,  double vy ){

    int i, index;
    double dr = 1.0;
    double dt = max(vx,vy) * dr/10;

    double *axPhi = new double[gridSize];
    double *flux = new double[yGridSize*(xGridSize+1)+xGridSize*(yGridSize+1)];
    double *rhs = new double[gridSize];
    double *K1 = new double[gridSize];
    double *K2 = new double[gridSize];
    double *K3 = new double[gridSize];
    double *K4 = new double[gridSize];

    /// Computing K1 factor
    FluxSolver->calcFlux(Phi, flux, xGridSize, yGridSize, vx, vy);
    // Making the right hand side
    for (i = 0; i < gridSize; i++){
       index = i+(xGridSize+1)*(i/xGridSize);
       K1[i] = ( flux[index+2*xGridSize+1] - flux[index]
                 + flux[index+xGridSize+1] - flux[index+xGridSize] )
                  / dr ;
    }

    /// Computing K2 factor
    // Computing Phi + h/2 K1
    for (i = 0; i < gridSize; i++){
       axPhi[i] = Phi[i] + dt*K1[i]/2.;
    }
    FluxSolver->calcFlux(axPhi, flux, xGridSize, yGridSize, vx, vy);
    for (i = 0; i < gridSize; i++){
       index = i+(xGridSize+1)*(i/xGridSize);
       K2[i] = ( flux[index+2*xGridSize+1] - flux[index]
                 + flux[index+xGridSize+1] - flux[index+xGridSize] )
                  / dr ;
    }

    /// Computing K3 factor
    // Computing Phi + h/2 K2
    for (i = 0; i < gridSize; i++){
       axPhi[i] = Phi[i] + dt*K2[i]/2.;
    }
    FluxSolver->calcFlux(axPhi, flux, xGridSize, yGridSize, vx, vy);
    for (i = 0; i < gridSize; i++){
       index = i+(xGridSize+1)*(i/xGridSize);
       K3[i] = ( flux[index+2*xGridSize+1] - flux[index]
                 + flux[index+xGridSize+1] - flux[index+xGridSize] )
                  / dr ;
    }

    /// Computing K4 factor
    // Computing Phi + h K3
    for (i = 0; i < gridSize; i++){
       axPhi[i] = Phi[i] + dt*K3[i];
    }
    FluxSolver->calcFlux(axPhi, flux, xGridSize, yGridSize, vx, vy);
    for (i = 0; i < gridSize; i++){
       index = i+(xGridSize+1)*(i/xGridSize);
       K4[i] = ( flux[index+2*xGridSize+1] - flux[index]
                 + flux[index+xGridSize+1] - flux[index+xGridSize] )
                  / dr ;
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

