#include "./Simulation2DClass.h"

Simulation2DClass::Simulation2DClass( ){
   cout << "SIMULATION CLASS CONSTRUCTED SUCCESSFULLY !" << endl;
   solver = new ForwardEulerScheme2D;
   actualTime = 0.0;
}


Simulation2DClass::~Simulation2DClass( ){
   delete solver;
}


bool Simulation2DClass::setMainSolver( string mainSolverSchemeName ){
   if ( mainSolverSchemeName == "LaxFriedrichs" ){
      cout << "LaxFriedrichs is picked" << endl;
      delete solver;
      solver = new LaxFriedrichsScheme2D;
      return true;
   }
   else if ( mainSolverSchemeName == "ForwardEuler" ){
      delete solver;
      solver = new ForwardEulerScheme2D;
      return true;
   }
   else if ( mainSolverSchemeName == "RK4" ){
      delete solver;
      solver = new RK4Scheme2D;
      return true;
   }
   else{
      delete solver;
      solver = new RK4Scheme2D;
      return false; 
   }
}

bool Simulation2DClass::setFluxSolver( string fluxSolverSchemeName ){
   return solver->setFluxSolver(fluxSolverSchemeName);
}

void Simulation2DClass::setupSimulation( string mainSolverSchemeName,
                                         string fluxSolverSchemeName ){

   actualTime = 0.0;

   cout << "XGrid size is : " << xGridSize << endl;
   cout << "YGrid size is : " << yGridSize << endl;

   setMainSolver(mainSolverSchemeName);

   solver->setGridSize(xGridSize, yGridSize);

   setFluxSolver(fluxSolverSchemeName);

   cout << "Simulation did setup correctly" << endl;
}


void Simulation2DClass::runSimulationOneTimeStep( void ){
   actualTime += solver->Solve(Phi,vx,vy);
}


bool Simulation2DClass::saveSnapShot( string fname ){ 
   return saveImageIntoFile(fname, Phi, xGridSize, yGridSize);
}


bool Simulation2DClass::saveSnapShotExactSolution( string fname ){ 

   double exactSolution[gridSize];

   for (int i = 0; i < xGridSize; i++){
      for (int j = 0; j < yGridSize; j++){
         exactSolution[i+j*xGridSize] = returnExactSolution(actualTime, i, j);
      }
   }

   return saveImageIntoFile(fname, exactSolution, xGridSize, yGridSize);

}


double Simulation2DClass::calcErrorNorm( void ){ 

   double err = 0.0;

   for (int i = 0; i < xGridSize; i++){
      for (int j = 0; j < yGridSize; j++){
         err += 
            pow(returnExactSolution(actualTime, i,j)-Phi[i+j*xGridSize] ,2);
      }
   }

   return sqrt(err) / (float)xGridSize / (float)yGridSize;

}
