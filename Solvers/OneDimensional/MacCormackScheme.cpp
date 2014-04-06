#include "MacCormackScheme.h"

double MacCormackScheme::Solve( const double r[], double Phi[]){

    int i;
    double dr = r[1] - r[0];
    double dt = dr/5;

    double *corr = new double[gridSize];

    // Evolve in time (here flux is axillary variable not actually a flux)
    for (i = 0; i < (gridSize-1); i++){
       corr[i] = Phi[i] - dt * ( Phi[i+1] - Phi[i] ) / dr;
    }
    corr[gridSize-1] = Phi[gridSize-1] 
                       - dt * ( Phi[0] - Phi[gridSize-1] ) / dr;

    for (i = 1; i < gridSize; i++){
       Phi[i] = 0.5 * ( Phi[i] + corr[i] ) 
                - 0.5 * dt * ( corr[i] - corr[i-1] ) / dr;
    }
    Phi[0] = 0.5 * ( Phi[0] + corr[0] ) 
             - 0.5 * dt * ( corr[0] - corr[gridSize-1] ) / dr;

    delete [] corr;

    return dt;
}

