#include "./Simulation1DClass.h"

Simulation1DClass::Simulation1DClass( ){
   snapShotHeader = "# r, Phi";
   phaseSpaceHeader = " Phase Space Header is not Implimented";
   cout << "SIMULATION CLASS CONSTRUCTED SUCCESSFULLY !" << endl;
   solver = new RK4Scheme;
   solver->setGridSize(0);
   actualTime = 0.0;
}


Simulation1DClass::~Simulation1DClass( ){
   delete solver;
}


bool Simulation1DClass::setMainSolver( string mainSolverSchemeName ){
   if ( mainSolverSchemeName == "RK4KurganovTadmor2000" ){
      delete solver;
      solver = new RK4KurganovTadmor2000Scheme;
      return true;
   }
   else if ( mainSolverSchemeName == "KurganovTadmor2ndOrder2000" ){
      delete solver;
      solver = new KurganovTadmor2ndOrder2000Scheme;
      return true;
   }
   else if ( mainSolverSchemeName == "KurganovTadmor2000" ){
	  cout << "OK " << endl;
      delete solver;
      solver = new KurganovTadmor2000Scheme;
      return true;
   }
   else if ( mainSolverSchemeName == "LaxFriedrichs" ){
      delete solver;
      solver = new LaxFriedrichsScheme;
      return true;
   }
   else if ( mainSolverSchemeName == "MacCormack" ){
      delete solver;
      solver = new MacCormackScheme;
      return true;	   
   }
   else if ( mainSolverSchemeName == "ForwardEuler" ){
      delete solver;
      solver = new ForwardEulerScheme;
      return true;
   }
   else if ( mainSolverSchemeName == "RK4" ){
      delete solver;
      solver = new RK4Scheme;
      return true;
   }
   else{
      delete solver;
      solver = new RK4Scheme;
      return false; 
   }
}

bool Simulation1DClass::setFluxSolver( string fluxSolverSchemeName ){
   return solver->setFluxSolver(fluxSolverSchemeName);
}

void Simulation1DClass::setupSimulation( string mainSolverSchemeName,
                                         string fluxSolverSchemeName ){

   actualTime = 0.0;

   cout << "Grid size is : " << gridSize << endl;

   setMainSolver(mainSolverSchemeName);

   solver->setGridSize(gridSize);

   setFluxSolver(fluxSolverSchemeName);

   cout << "Simulation did setup correctly" << endl;

}


void Simulation1DClass::runSimulationOneTimeStep( void ){
    actualTime += solver->Solve(r, Phi);
}


bool Simulation1DClass::saveSnapShot( string fname ){ 
   return saveDataIntoFile(fname, snapShotHeader, r, Phi, gridSize);
}


bool Simulation1DClass::saveSnapShotExactSolution( string fname ){ 

   double exactSolution[gridSize];

   for (int i = 0; i < gridSize; i++){
	  exactSolution[i] = returnExactSolution(actualTime, i);   
   }

   return saveDataIntoFile(fname, snapShotHeader, r, exactSolution, gridSize);

}


double Simulation1DClass::calcErrorNorm( void ){

   double err = 0.0;

   for (int i = 0; i < gridSize; i++){
	  err += pow(returnExactSolution(actualTime, i)-Phi[i], 2);   
   }

   return sqrt(err) / (float)gridSize;

}
